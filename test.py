import os
import sys
import resource
import subprocess
import time
import re
import io
import zipfile
import urllib.error
import urllib.request

# test name -> (cses problem id, transformation of output lines before comparing)
CSES_TESTS = {
    "fenwick": (1739, None),
    "fft": (2111, None),
    "hash_string": (1753, None),
    "z_algorithm": (1753, None),
    "li_chao": (2085, None),
    "max_flow": (1694, None),
    "min_cost_flow": (2129, lambda lines: lines[:1]),
    "tarjan_bridge": (2076, lambda lines: lines[:1] + sorted(sorted(l) for l in lines[1:])),
    "convex_hull": (2195, lambda lines: lines[:1] + sorted(lines[1:])),
    "suffix_array": (2105, None),
}
CSES_DATA_DIR = os.path.join("tests", "cses")
CSES_TESTS_URL = "https://cses-tests.pages.dev/{}.zip"
TIME_LIMIT = 5
HEAD_PATH = os.path.join("tests", "head.h")
PERF_REPORT_PATH = "perf_report.txt"
# times above this are highlighted, as this is the time limit on cses
SLOW_TIME = 1

# live updating status line only works in a terminal, colors also work in github actions logs
LIVE = sys.stdout.isatty()
COLOR = "NO_COLOR" not in os.environ and (LIVE or os.environ.get("GITHUB_ACTIONS") == "true")
BOLD, DIM, RED, GREEN, YELLOW, CYAN = "1", "2", "31", "32", "33", "36"
VERDICT_COLORS = {"OK": GREEN, "WA": RED, "RTE": RED, "TLE": RED}

def style(text: str, *codes: str) -> str:
    if not COLOR:
        return text
    return f"\033[{';'.join(codes)}m{text}\033[0m"

# shows a temporary line that is replaced by the next status or print
def status(text: str):
    if LIVE:
        print(f"\r\033[K{text}", end="", flush=True)

def clear_status():
    status("")

def progress_bar(done: int, total: int, width: int = 24) -> str:
    filled = width * done // total
    return style("━" * filled, CYAN) + style("━" * (width - filled), DIM)

def format_time(t: float) -> str:
    text = f"{t:.2f}s"
    return style(text, YELLOW) if t > SLOW_TIME else text

def download_tests(problem_id: int, data_dir: str, label: str):
    status(f"  {style('↓', CYAN)} {label}  {style(f'downloading tests for cses problem {problem_id}', DIM)}")
    try:
        # default python user agent is blocked
        request = urllib.request.Request(CSES_TESTS_URL.format(problem_id), headers={"User-Agent": "CP-template"})
        with urllib.request.urlopen(request) as response:
            archive = response.read()
    except urllib.error.URLError as e:
        clear_status()
        print(f"  {style('✗', RED)} {label}  {style(f'downloading tests failed ({e})', RED)}")
        sys.exit(1)

    # extract into a temporary directory first so that an interrupted download is not mistaken for a complete one
    tmp_dir = data_dir + ".tmp"
    os.makedirs(tmp_dir, exist_ok=True)
    with zipfile.ZipFile(io.BytesIO(archive)) as zip_file:
        for file in zip_file.namelist():
            if re.fullmatch(r"\d+\.(in|out)", file):
                with open(os.path.join(tmp_dir, file), "wb") as test_file:
                    test_file.write(zip_file.read(file))
    os.rename(tmp_dir, data_dir)

# if file2 depends on file1 and file1 is newer than file2, then file2 needs to be updated
def does_file_need_updating(file1: str, file2: str) -> bool:
    if not os.path.isfile(file2):
        return True
    return os.path.getmtime(file1) > os.path.getmtime(file2)

def setup_cpp(cpp_path: str, algo_path: str, res_path: str):
    if not any(does_file_need_updating(path, res_path) for path in (cpp_path, algo_path, HEAD_PATH)):
        return

    cpp_code: str
    with open(cpp_path, "r") as cpp_file:
        cpp_code = cpp_file.read()

    algo_code: str
    with open(algo_path, "r") as algo_file:
        algo_code = algo_file.read()

    head_code: str
    with open(HEAD_PATH, "r") as head_file:
        head_code = head_file.read()

    cpp_code = cpp_code.replace("// ALGO", algo_code)
    cpp_code = cpp_code.replace("// HEAD", head_code)

    with open(res_path, "w") as res_file:
        res_file.write(cpp_code)

# returns whether compilation succeeded and compiler errors
def compile_cpp(cpp_path: str, res_path: str, label: str) -> (bool, str):
    if not does_file_need_updating(cpp_path, res_path):
        return True, ""
    status(f"  {style('⚙', CYAN)} {label}  {style('compiling', DIM)}")
    # on macOS the stack size of the main thread can only be raised at link time, elsewhere it is raised with setrlimit before running
    stack_flags = ["-Wl,-stack_size,0x20000000"] if sys.platform == "darwin" else []
    result = subprocess.run(["g++", f"-o{res_path}", cpp_path, "-O2", "-std=c++17", *stack_flags], capture_output=True, text=True)
    return result.returncode == 0, result.stderr

def raise_stack_limit():
    if sys.platform != "darwin":
        _, hard = resource.getrlimit(resource.RLIMIT_STACK)
        resource.setrlimit(resource.RLIMIT_STACK, (hard, hard))

def compare(s1: str, s2: str, transform) -> bool:
    lines1 = [l.split() for l in s1.strip().split("\n")]
    lines2 = [l.split() for l in s2.strip().split("\n")]
    if transform is not None:
        lines1, lines2 = transform(lines1), transform(lines2)
    return lines1 == lines2


def run_testcase(exec_path: str, testcase_in_path: str, testcase_out_path, transform) -> (bool, str, float):
    inp = open(testcase_in_path, "r")

    start_time = time.time()
    try:
        result = subprocess.run([exec_path], stdout=subprocess.PIPE, stdin=inp, timeout=TIME_LIMIT, preexec_fn=raise_stack_limit)
    except subprocess.TimeoutExpired:
        inp.close()
        return False, "TLE", TIME_LIMIT
    end_time = time.time()
    elapsed_time = end_time - start_time

    inp.close()

    if result.returncode != 0:
        return False, "RTE", elapsed_time

    out = open(testcase_out_path, "r")
    expected = out.read()
    out.close()

    if compare(expected, result.stdout.decode("utf-8"), transform):
        return True, "OK", elapsed_time
    else:
        return False, "WA", elapsed_time

# returns number of passed and failed tests, perf report line and whether compilation succeeded
def test_file(name: str, verbose: bool, width: int) -> (int, int, str, bool):
    label = name.ljust(width)
    directory = os.path.join("tests", name)
    if not os.path.isdir(directory):
        print(f"  {style('-', DIM)} {style(label, DIM)}  {style('no tests', DIM)}")
        return 0, 0, "", True

    build_dir = os.path.join(directory, "build")
    if not os.path.isdir(build_dir):
        os.mkdir(build_dir)

    cpp_path = os.path.join(directory, "code.cpp")
    algo_path = os.path.join("algos", name + ".cpp")
    res_path = os.path.join(build_dir, "res.cpp")
    setup_cpp(cpp_path, algo_path, res_path)
    exec_path = os.path.join(build_dir, "exec")
    compiled, errors = compile_cpp(res_path, exec_path, label)
    clear_status()
    if not compiled:
        print(f"  {style('✗', RED)} {style(label, BOLD)}  {style('compilation failed', RED, BOLD)}")
        print("".join(f"      {line}\n" for line in errors.splitlines()))
        return 0, 0, "", False

    data_dir = directory
    transform = None
    if name in CSES_TESTS:
        problem_id, transform = CSES_TESTS[name]
        data_dir = os.path.join(CSES_DATA_DIR, str(problem_id))
        if not os.path.isdir(data_dir):
            download_tests(problem_id, data_dir, label)

    test_files = []
    for file in os.listdir(data_dir):
        if file.endswith(".in"):
            input_path = os.path.join(data_dir, file)
            output_path = os.path.join(data_dir, file[:-3] + ".out")
            test_files.append((input_path, output_path, file[:-3]))

    # sort test files by number
    test_files.sort(key=lambda x: int(x[2]))

    avgs, maxs = 0, 0
    results = []
    for i, (input_path, output_path, test_num) in enumerate(test_files):
        status(f"  {style('…', CYAN)} {label}  {progress_bar(i, len(test_files))} {style(f'{i}/{len(test_files)}', DIM)}")
        (res, verd, elapsed) = run_testcase(exec_path, input_path, output_path, transform)
        maxs = max(maxs, elapsed)
        avgs += elapsed / len(test_files)
        results.append((test_num, verd, elapsed))
    clear_status()

    success = sum(verd == "OK" for _, verd, _ in results)
    fail = len(results) - success

    mark = style("✓", GREEN) if fail == 0 else style("✗", RED)
    counts = style(f"{success}/{len(results)}".rjust(7), GREEN if fail == 0 else RED)
    line = f"  {mark} {style(label, BOLD)}  {counts}   avg {format_time(avgs)}   max {format_time(maxs)}"
    # list failed tests grouped by verdict
    for verdict in ("WA", "RTE", "TLE"):
        failed = [test_num for test_num, verd, _ in results if verd == verdict]
        if failed:
            line += f"   {style(verdict, VERDICT_COLORS[verdict], BOLD)} {' '.join(failed)}"
    print(line)

    if verbose:
        for test_num, verd, elapsed in results:
            print(f"      {style(test_num.rjust(4), DIM)}  {style(verd.ljust(3), VERDICT_COLORS[verd])}  {format_time(elapsed)}")
        print()

    report = f"test {name}: avg: {avgs:.2f}s, max: {maxs:.2f}s\n"
    return success, fail, report, True


if __name__ == "__main__":
    success = 0
    fail = 0
    compile_fail = 0
    allowed = set()
    verbose = False
    write_report = False
    for i, x in enumerate(sys.argv):
        if i == 0:
            continue
        if x == "--verbose":
            verbose = True
            continue
        if x == "--report":
            write_report = True
            continue
        allowed.add(x)

    # keep reports of tests that are not run this time
    reports = {}
    if os.path.isfile(PERF_REPORT_PATH):
        with open(PERF_REPORT_PATH, "r") as report_file:
            for line in report_file:
                reports[line.split(":")[0]] = line

    # remove the .cpp extension
    names = sorted(file[:-4] for file in os.listdir("algos") if file.endswith(".cpp"))
    names = [name for name in names if len(allowed) == 0 or name in allowed]
    width = max((len(name) for name in names), default=0)

    print()
    tested = sum(os.path.isdir(os.path.join("tests", name)) for name in names)
    print(f"  {style(f'Testing {tested} algorithms', BOLD)}")
    print()

    start_time = time.time()
    for name in names:
        succ, fal, report, compiled = test_file(name, verbose, width)
        if report:
            reports[f"test {name}"] = report
        success += succ
        fail += fal
        compile_fail += not compiled

    if write_report:
        with open(PERF_REPORT_PATH, "w") as report_file:
            report_file.writelines(reports.values())

    summary = [style(f"{success} passed", GREEN, BOLD)]
    if fail > 0:
        summary.append(style(f"{fail} failed", RED, BOLD))
    if compile_fail > 0:
        summary.append(style(f"{compile_fail} failed to compile", RED, BOLD))
    summary.append(style(f"{time.time() - start_time:.1f}s", DIM))
    if not verbose:
        print()
    print("  " + style(" · ", DIM).join(summary))
    print()
    if fail > 0 or compile_fail > 0:
        sys.exit(1)
