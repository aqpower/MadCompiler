import os
import subprocess

# 测试用例目录
TEST_DIR = "./test_cases"
# 编译器路径
COMPILER = "./build/src/compiler"
# 输出目录
OUTPUT_DIR = "./test_outputs"

# 创建输出目录
os.makedirs(OUTPUT_DIR, exist_ok=True)

# 测试内容描述
test_right_descriptions = {
    "test_case1.txt": "测试基本赋值",
    "test_case2.txt": "测试 if-else 语句",
    "test_case3.txt": "测试 while 循环",
    "test_case4.txt": "测试嵌套块",
    "test_case5.txt": "测试复杂算术表达式",
    "test_case6.txt": "测试变量声明和赋值",
    "test_case7.txt": "测试混合运算符",
    "test_case8.txt": "测试 if 和 while 复合语句",
}

test_error_descriptions = {
    "test_case9.txt": "测试没有分号",
    "test_case10.txt": "测试没有右大括号",
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
