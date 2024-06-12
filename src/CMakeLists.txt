# # for each "src/x.cpp", generate target "x"
# file(GLOB_RECURSE all_srcs CONFIGURE_DEPENDS *.cpp)
# foreach(v ${all_srcs})
#     string(REGEX MATCH "src/.*" relative_path ${v})
#     # message(${relative_path})
#     string(REGEX REPLACE "src/" "" target_name ${relative_path})
#     string(REGEX REPLACE ".cpp" "" target_name ${target_name})

#     add_executable(${target_name} ${v})
# endforeach()

# 查找所有源文件
file(GLOB LIB_SOURCES "token.cpp" "lexer.cpp" "parser.cpp")

# 创建静态库
add_library(lexer_lib ${LIB_SOURCES})

add_executable(compiler compiler.cpp)

target_link_libraries(compiler lexer_lib)

