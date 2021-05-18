cmake_minimum_required(VERSION 2.8)

project(code)

#set(CMAKE_CXX_STANDARD 11)
add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/packages/include/)
#指定头文件

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/packages/lib/)
#指定库文件

aux_source_directory(./src DIP_SRCS)
## 查找./src目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/code)
#存放可执行软件的目录

link_libraries(json)
link_libraries(log4cplus)
link_libraries(pthread)
link_libraries(inifile)
link_libraries(curl)
link_libraries(pthread)
link_libraries(crypto)
link_libraries(ssl)
link_libraries(sqlite3)
link_libraries(dl)
link_libraries(rt)
link_libraries(stdc++)

add_executable(code ${DIP_SRCS})

#target_link_libraries(code inifile sqlite3 dl curl json ssl rt crypto pthread log4cplus)
