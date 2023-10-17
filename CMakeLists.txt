cmake_minimum_required(VERSION 3.26)
project(OpenGL_Homework)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL_Homework src/glad.c homework2_1.cpp)

INCLUDE_DIRECTORIES(include)
link_directories(lib)
target_link_libraries(OpenGL_Homework ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
