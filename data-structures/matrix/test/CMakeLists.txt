set(target_name test_matrix_t)

add_executable(${target_name})

target_sources(
    ${target_name}
    PRIVATE
        test.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
    ${target_name}
    PRIVATE
        gtest_main
)

target_include_directories(
    ${target_name}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/
)

include(GoogleTest)
gtest_discover_tests(${target_name})
