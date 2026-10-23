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

def download_tests(problem_id: int, data_dir: str):
    print(f"Downloading tests for CSES problem {problem_id}...")
    try:
        # default python user agent is blocked
        request = urllib.request.Request(CSES_TESTS_URL.format(problem_id), headers={"User-Agent": "CP-template"})
        with urllib.request.urlopen(request) as response:
            archive = response.read()
    except urllib.error.URLError as e:
        print(f"Downloading tests failed ({e}), exiting")
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

def compile_cpp(cpp_path: str, res_path: str):
    if does_file_need_updating(cpp_path, res_path):
        print(f"Compiling {cpp_path}...")
        # on macOS the stack size of the main thread can only be raised at link time, elsewhere it is raised with setrlimit before running
        stack_flag = " -Wl,-stack_size,0x20000000" if sys.platform == "darwin" else ""
        ret_val = os.system(f"g++ -o{res_path} {cpp_path} -O2 -std=c++17{stack_flag}")
        if ret_val != 0:
            print("Compilation failed, exiting")
            sys.exit(1)

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

def test_file(name: str, verbose: bool) -> (int, int, str):
    directory = os.path.join("tests", name)
    if not os.path.isdir(directory):
        print(f"> Skipping {name} (no tests found)")
        print()
        return 0, 0, ""

    print(f"> Testing {name}...")
    build_dir = os.path.join(directory, "build")
    if not os.path.isdir(build_dir):
        os.mkdir(build_dir)

    cpp_path = os.path.join(directory, "code.cpp")
    algo_path = os.path.join("algos", name + ".cpp")
    res_path = os.path.join(build_dir, "res.cpp")
    setup_cpp(cpp_path, algo_path, res_path)
    exec_path = os.path.join(build_dir, "exec")
    compile_cpp(res_path, exec_path)

    data_dir = directory
    transform = None
    if name in CSES_TESTS:
        problem_id, transform = CSES_TESTS[name]
        data_dir = os.path.join(CSES_DATA_DIR, str(problem_id))
        if not os.path.isdir(data_dir):
            download_tests(problem_id, data_dir)

    success = 0
    fail = 0

    test_files = []
    for file in os.listdir(data_dir):
        if file.find("in") != -1:
            input_path = os.path.join(data_dir, file)
            output_path = os.path.join(data_dir, file.replace("in", "out"))
            test_files.append((input_path, output_path, file))

    # sort test files lexicographically
    test_files.sort(key=lambda x: int(x[0].split("/")[-1].split(".")[0]))

    avgs, maxs = 0, 0 

    for input_path, output_path, file in test_files:
        (res, verd, elapsed) = run_testcase(exec_path, input_path, output_path, transform)
        maxs = max(maxs, elapsed)
        avgs += elapsed / len(test_files)
        l = " " * (20 - len(file))
        test_num = file.split(".")[0]
        if verbose:
            print(f"Test {test_num} {l} {verd} {elapsed:.3f}s")
        else:
            print(f"{test_num}: {verd}", end="   ")

        if res:
            success += 1
        else:
            fail += 1

    report = f"test {name}: avg: {avgs:.2f}s, max: {maxs:.2f}s\n"
    print()
    print(report)

    return success, fail, report


if __name__ == "__main__":
    success = 0
    fail = 0
    req = None
    allowed = set()
    verbose = False
    for i, x in enumerate(sys.argv):
        if i == 0:
            continue
        if x == "--verbose":
            verbose = True
            continue
        allowed.add(x)

    # keep reports of tests that are not run this time
    reports = {}
    if os.path.isfile(PERF_REPORT_PATH):
        with open(PERF_REPORT_PATH, "r") as report_file:
            for line in report_file:
                reports[line.split(":")[0]] = line

    for file in os.listdir("algos"):
        if file.endswith(".cpp") and (len(allowed) == 0 or file[:-4] in allowed):
            # remove the .cpp extension
            name = file[:-4]
            succ, fal, report = test_file(name, verbose)
            if report:
                reports[f"test {name}"] = report
            success += succ
            fail += fal

    with open(PERF_REPORT_PATH, "w") as report_file:
        report_file.writelines(reports.values())

    print(f"Success: {success}")
    print(f"Fail: {fail}")
    if fail > 0:
        print("FAIL")
        sys.exit(1)
    else:
        print("OK")
