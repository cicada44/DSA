set(target_name dll)

add_executable(${target_name})

target_sources(
    ${target_name}
    PRIVATE
        main.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/dll
)
