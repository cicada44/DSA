enable_testing()

add_executable(
  test
  test/test.cpp
)

target_link_libraries(
  test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test)
