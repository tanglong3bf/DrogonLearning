cmake_minimum_required(VERSION 3.5)
project(pluginDemo CXX)

include(CheckIncludeFileCXX)

# 用到了 C++20 的协程语法
add_compile_options(-std=c++2a)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

# ##############################################################################

message(STATUS "use c++20")

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)

target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC})
