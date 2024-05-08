cmake_minimum_required(VERSION 3.22)

project(
    matrix_t
    LANGUAGES CXX
    VERSION 1.0
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(CompileOptions)
add_executable(${PROJECT_NAME} src/main.cpp src/matrix_t.h)
set_compile_options(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE src/)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
if (NOT CLANG_TIDY_EXE)
  message(WARNING "clang-tidy not found")
else()
  execute_process(
    COMMAND ${CLANG_TIDY_EXE} --version
    OUTPUT_VARIABLE CLANG_TIDY_VERSION)
  message("clang-tidy found:\n" ${CLANG_TIDY_VERSION})
endif()


enable_testing()
add_subdirectory(external)
add_subdirectory(test)
