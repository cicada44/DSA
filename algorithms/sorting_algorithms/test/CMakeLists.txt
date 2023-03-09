set(target_name test)

add_executable(${target_name})

add_compile_options(-Wall -Werror -Wextra -pedantic)

target_sources(
    ${target_name}
    PRIVATE
        test/test.cpp
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(
    ${target_name}
    ${GTEST_LIBRARIES}
    pthread
)