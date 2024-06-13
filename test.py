import os
import subprocess

# 测试用例目录
TEST_DIR = "./test_cases"
# 编译器路径
COMPILER = "./build/src/madcompiler"
# 输出目录
OUTPUT_DIR = "./test_outputs"

# 创建输出目录
os.makedirs(OUTPUT_DIR, exist_ok=True)

# 测试内容描述
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
    """
    主函数，运行所有测试用例并打印结果
    """
    test_files = [os.path.join(TEST_DIR, filename) for filename in os.listdir(TEST_DIR) if filename.endswith('.txt')]
    
    # 运行所有测试用例
    results = []
    
    # 黑盒测试
    for test_file in test_files:
        results.append(run_test(test_file))
    

    # 打印测试结果
    print("==============")
    print("黑盒测试结果:")
    for test_file, passed, stdout, stderr in results:
        print(f"测试 {test_file} {'通过' if passed else '失败'}。")
    
    print("所有测试完成。")

if __name__ == "__main__":
    main()
