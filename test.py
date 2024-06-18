import os
import subprocess

TEST_DIR = "./test_cases"
COMPILER = "./build/src/madcompiler"
OUTPUT_DIR = "./test_outputs"

os.makedirs(OUTPUT_DIR, exist_ok=True)
test_right_descriptions = {
    "test_case1.txt": "验证所有的有效等价类",
}
test_error_descriptions = {
    "test_case2.txt": "",
    "test_case3.txt": "",
    "test_case4.txt": "",
    "test_case5.txt": "",
    "test_case6.txt": "",
    "test_case7.txt": "",
    "test_case8.txt": "",
    "test_case9.txt": "",
    "test_case10.txt": "",
    "test_case11.txt": "",
    "test_case12.txt": "",
    "test_case13.txt": "",
}

def run_test(test_file):
    print(f"==============")
    print(f"运行黑盒测试: {test_file}")
    expected_output = 0
    if os.path.basename(test_file) in test_right_descriptions:
        test_descriptions = test_right_descriptions[os.path.basename(test_file)]
    else:
        expected_output = 1
        test_descriptions = test_error_descriptions[os.path.basename(test_file)]        
    print(test_descriptions)
    # print the test_file content
    with open(test_file, 'r') as f:
        print(f.read())
    output_file = os.path.join(OUTPUT_DIR, os.path.basename(test_file).replace(".txt", ".out"))
    command = [COMPILER, test_file, "-o", output_file]
    result = subprocess.run(command, capture_output=True, text=True)
    print(f"return code: {result.returncode}")
    if expected_output == 1:
        return (test_file, result.returncode != 0, result.stdout, result.stderr)
    else:  
        return (test_file, result.returncode == 0, result.stdout, result.stderr)

def main():
    test_files = [os.path.join(TEST_DIR, filename) for filename in os.listdir(TEST_DIR) if filename.endswith('.txt')]
    
    results = []
    
    for test_file in test_files:
        results.append(run_test(test_file))
    

    print("==============")
    print("黑盒测试结果:")
    for test_file, passed, stdout, stderr in results:
        print(f"测试 {test_file} {'通过' if passed else '失败'}。")
    
    print("所有测试完成。")

if __name__ == "__main__":
    main()
