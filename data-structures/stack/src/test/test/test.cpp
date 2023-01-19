#include "../../libstack/stack.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(stack_find_test, find_test)
{
    ASSERT_EQ(true, stack<int>({1, 2, 3, 4, 5}).find(3));
    ASSERT_EQ(true, stack<int>({1}).find(1));
    ASSERT_EQ(true, stack<int>({1, 1, 1}).find(1));
    ASSERT_EQ(true, stack<int>({3, 2, 1}).find(1));
    ASSERT_EQ(false, stack<int>({}).find(1));
    ASSERT_EQ(false, stack<int>({3, 2}).find(1));
    ASSERT_EQ(false, stack<int>({2, 2, 2}).find(1));
    ASSERT_EQ(false, stack<int>({0}).find(1));
}

TEST(stack_size_test, size_test)
{
    ASSERT_EQ(0, stack<int>({}).size());
    ASSERT_EQ(1, stack<int>({1}).size());
    ASSERT_EQ(2, stack<int>({1, 2}).size());

    ASSERT_EQ(false, stack<int>({1, 2}).is_empty());
    ASSERT_EQ(true, stack<int>().is_empty());
    ASSERT_EQ(true, stack<int>({}).is_empty());
    ASSERT_EQ(true, stack<int>(std::move(stack<int>())).is_empty());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
