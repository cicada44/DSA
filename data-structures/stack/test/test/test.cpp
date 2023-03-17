#include "../../src/libstack/stack.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(Stack, Containing)
{
    ASSERT_EQ(true, stack::stack<int>({1, 2, 3, 4, 5}).contains(3));
    ASSERT_EQ(true, stack::stack<int>({1}).contains(1));
    ASSERT_EQ(true, stack::stack<int>({1, 1, 1}).contains(1));
    ASSERT_EQ(true, stack::stack<int>({3, 2, 1}).contains(1));
    ASSERT_EQ(false, stack::stack<int>({}).contains(1));
    ASSERT_EQ(false, stack::stack<int>({3, 2}).contains(1));
    ASSERT_EQ(false, stack::stack<int>({2, 2, 2}).contains(1));
    ASSERT_EQ(false, stack::stack<int>({0}).contains(1));
}

TEST(Stack, Size)
{
    ASSERT_EQ(0, stack::stack<int>({}).size());
    ASSERT_EQ(1, stack::stack<int>({1}).size());
    ASSERT_EQ(2, stack::stack<int>({1, 2}).size());
}

TEST(Stack, BeginEnd)
{
    // Normal
    {
        ASSERT_EQ(5, stack::stack<int>({1, 2, 3, 4, 5}).begin()->value);
        ASSERT_EQ(1, stack::stack<int>({1, 2, 3, 4, 5}).end()->value);
    }

    // Const
    {
        ASSERT_EQ(5, stack::stack<int>({1, 2, 3, 4, 5}).cbegin()->value);
        ASSERT_EQ(1, stack::stack<int>({1, 2, 3, 4, 5}).cend()->value);
    }
}

TEST(Stack, Count)
{
    stack::stack<int> l{1, 2, 2, 2, 2, 2, 4};

    ASSERT_EQ(5, l.count(2));
    ASSERT_EQ(1, l.count(1));
    ASSERT_EQ(0, l.count(3));
}

TEST(Stack, Addition)
{
    // Pushback
    {
        stack::stack<int> l;

        ASSERT_EQ(stack::stack<int>(), l);
        for (const auto& c : {1, 2, 3, 4, 5}) {
            l.push(c);
        }

        ASSERT_EQ(stack::stack<int>({1, 2, 3, 4, 5}), l);
    }
}

TEST(Stack, Removal)
{
    // pop
    {
        stack::stack<int> l = {1, 2, 3, 4, 5};
        l.pop();
        ASSERT_EQ(l, stack::stack<int>({1, 2, 3, 4}));
    }
}

TEST(Stack, RO5)
{
    // Copying=
    {
        stack::stack<int> l1 = {1, 2, 3};
        stack::stack<int> l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Copy =
    {
        stack::stack<int> l1 = {1, 2, 3}, l2;
        l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Moving
    {
        stack::stack<int> l1{1, 2, 3};
        stack::stack<int> l2(std::move(l1));
        ASSERT_EQ(stack::stack<int>({1, 2, 3}), l2);
    }

    // Moving =
    {
        stack::stack<int> l1 = {1, 2, 3};
        stack::stack<int> l2;
        l2 = std::move(l1);
        ASSERT_EQ(stack::stack<int>({1, 2, 3}), l2);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
