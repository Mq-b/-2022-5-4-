``` CMAKE
project(SortMake)
aux_source_directory(src SRC_SUB)
aux_source_directory(. SRC_CUR)
add_executable(sort ${SRC_SUB} ${SRC_CUR})
include_directories(include)

```
project() ：设置项目名称，参数可以随意指定
aux_source_directory(dir VAR): 搜索 dir 目录下所有的源文件，并将结果列表存储在变量 VAR 中
add_executable(target src): 指定使用源文件 src，生成可执行程序 target , ${变量名} 是取变量的值
include_directories(headDir): 设置包含的头文件目录
