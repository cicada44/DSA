#include "../../libqueue/queue.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(queue_find_test, find_test)
{
    ASSERT_EQ(true, queue<int>({1, 2, 3, 4, 5}).find(3));
    ASSERT_EQ(true, queue<int>({1}).find(1));
    ASSERT_EQ(true, queue<int>({1, 1, 1}).find(1));
    ASSERT_EQ(true, queue<int>({3, 2, 1}).find(1));
    ASSERT_EQ(false, queue<int>({}).find(1));
    ASSERT_EQ(false, queue<int>({3, 2}).find(1));
    ASSERT_EQ(false, queue<int>({2, 2, 2}).find(1));
    ASSERT_EQ(false, queue<int>({0}).find(1));
}

TEST(queue_size_test, size_test)
{
    ASSERT_EQ(0, queue<int>({}).size());
    ASSERT_EQ(1, queue<int>({1}).size());
    ASSERT_EQ(2, queue<int>({1, 2}).size());

    ASSERT_EQ(false, queue<int>({1, 2}).is_empty());
    ASSERT_EQ(true, queue<int>().is_empty());
    ASSERT_EQ(true, queue<int>({}).is_empty());
    ASSERT_EQ(true, queue<int>(std::move(queue<int>())).is_empty());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
