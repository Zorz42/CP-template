import os
import subprocess
import string
import time

# if file2 depends on file1 and file1 is newer than file2, then file2 needs to be updated
def does_file_need_updating(file1: str, file2: str) -> bool:
    if not os.path.isfile(file2):
        return True
    return os.path.getmtime(file1) > os.path.getmtime(file2)

def setup_cpp(cpp_path: str, algo_path: str, res_path: str):
    if not does_file_need_updating(cpp_path, res_path) and not does_file_need_updating(algo_path, res_path):
        return

    cpp_code: str
    with open(cpp_path, "r") as cpp_file:
        cpp_code = cpp_file.read()

    algo_code: str
    with open(algo_path, "r") as algo_file:
        algo_code = algo_file.read()

    cpp_code = cpp_code.replace("// ALGO", algo_code)

    with open(res_path, "w") as res_file:
        res_file.write(cpp_code)

def compile_cpp(cpp_path: str, res_path: str):
    if does_file_need_updating(cpp_path, res_path):
        print(f"Compiling {cpp_path}...")
        os.system(f"g++ -o{res_path} {cpp_path} -O2 -std=c++17")

def compare(s1: str, s2: str) -> bool:
    remove = string.whitespace
    return s1.translate(remove) == s2.translate(remove)


def run_testcase(exec_path: str, testcase_in_path: str, testcase_out_path) -> (bool, str, float):
    inp = open(testcase_in_path, "r")

    start_time = time.time()
    result = subprocess.run([exec_path], stdout=subprocess.PIPE, stdin=inp)
    end_time = time.time()
    elapsed_time = end_time - start_time

    inp.close()

    if result.returncode != 0:
        return False, "RTE", elapsed_time

    out = open(testcase_out_path, "r")
    expected = out.read()
    out.close()

    if compare(expected, result.stdout.decode("utf-8")):
        return True, "OK", elapsed_time
    else:
        return False, "WA", elapsed_time

def test_file(name: str) -> (int, int):
    directory = name
    if not os.path.isdir(directory):
        print(f"> Skipping {name} (no tests found)")
        return 0, 0

    print(f"> Testing {name}...")
    build_dir = os.path.join(directory, "build")
    if not os.path.isdir(build_dir):
        os.mkdir(build_dir)

    cpp_path = os.path.join(directory, "code.cpp")
    algo_path = name + ".cpp"
    res_path = os.path.join(build_dir, "res.cpp")
    setup_cpp(cpp_path, algo_path, res_path)
    exec_path = os.path.join(build_dir, "exec")
    compile_cpp(res_path, exec_path)

    success = 0
    fail = 0

    test_files = []
    for file in os.listdir(directory):
        if file.find("input") != -1:
            input_path = os.path.join(directory, file)
            output_path = os.path.join(directory, file.replace("input", "output"))
            test_files.append((input_path, output_path, file))

    # sort test files lexicographically
    test_files.sort(key=lambda x: x[0])

    for input_path, output_path, file in test_files:
        (res, verd, elapsed) = run_testcase(exec_path, input_path, output_path)
        l = " " * (20 - len(file))
        print(f"Test {file} {l} {verd} {elapsed:.3f}s")
        if res:
            success += 1
        else:
            fail += 1

    return success, fail


if __name__ == "__main__":
    success = 0
    fail = 0
    for file in os.listdir("."):
        if file.endswith(".cpp"):
            # remove the .cpp extension
            succ, fal = test_file(file[:-4])
            success += succ
            fail += fal
    print(f"Success: {success}")
    print(f"Fail: {fail}")
    if fail > 0:
        print("FAIL")
    else:
        print("OK")