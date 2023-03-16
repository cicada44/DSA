#include "../../libqueue/queue.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(queue, Containing)
{
    ASSERT_EQ(true, queue::queue<int>({1, 2, 3, 4, 5}).contains(3));
    ASSERT_EQ(true, queue::queue<int>({1}).contains(1));
    ASSERT_EQ(true, queue::queue<int>({1, 1, 1}).contains(1));
    ASSERT_EQ(true, queue::queue<int>({3, 2, 1}).contains(1));
    ASSERT_EQ(false, queue::queue<int>({}).contains(1));
    ASSERT_EQ(false, queue::queue<int>({3, 2}).contains(1));
    ASSERT_EQ(false, queue::queue<int>({2, 2, 2}).contains(1));
    ASSERT_EQ(false, queue::queue<int>({0}).contains(1));
}

TEST(queue, Size)
{
    ASSERT_EQ(0, queue::queue<int>({}).size());
    ASSERT_EQ(1, queue::queue<int>({1}).size());
    ASSERT_EQ(2, queue::queue<int>({1, 2}).size());
}

TEST(queue, BeginEnd)
{
    // Normal
    {
        ASSERT_EQ(1, queue::queue<int>({1, 2, 3, 4, 5}).begin()->value);
        ASSERT_EQ(5, queue::queue<int>({1, 2, 3, 4, 5}).end()->value);
    }

    // Const
    {
        ASSERT_EQ(1, queue::queue<int>({1, 2, 3, 4, 5}).cbegin()->value);
        ASSERT_EQ(5, queue::queue<int>({1, 2, 3, 4, 5}).cend()->value);
    }
}

TEST(queue, Count)
{
    queue::queue<int> l{1, 2, 2, 2, 2, 2, 4};

    ASSERT_EQ(5, l.count(2));
    ASSERT_EQ(1, l.count(1));
    ASSERT_EQ(0, l.count(3));
}

TEST(queue, IdxOperator)
{
    queue::queue<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    ASSERT_EQ(1, l[0].value);
    ASSERT_EQ(3, l[2].value);
    ASSERT_EQ(5, l[4].value);
    ASSERT_EQ(7, l[6].value);
    ASSERT_EQ(9, l[8].value);
}

TEST(queue, Addition)
{
    // push
    {
        queue::queue<int> l;

        ASSERT_EQ(queue::queue<int>(), l);
        for (const auto& c : {1, 2, 3, 4, 5}) {
            l.push(c);
        }

        ASSERT_EQ(queue::queue<int>({5, 4, 3, 2, 1}), l);
    }
}

TEST(queue, Removal)
{
    // Pop
    {
        queue::queue<int> l = {1, 2, 3, 4};

        l.pop();

        ASSERT_EQ(l, queue::queue<int>({1, 2, 3}));

        l.pop();

        ASSERT_EQ(l, queue::queue<int>({1, 2}));

        l.pop();

        ASSERT_EQ(l, queue::queue<int>({1}));

        l.pop();

        ASSERT_EQ(l, queue::queue<int>());
    }
}

TEST(queue, Merger)
{
    // Merge lval
    {
        queue::queue<int> l1 = {4, 5};
        queue::queue<int> l2 = {1, 2, 3};

        l2.merge(l1);

        ASSERT_EQ(queue::queue<int>({1, 2, 3, 4, 5}), l2);
    }

    // Merge rval
    {
        queue::queue<int> l1 = {4, 5};
        queue::queue<int> l2 = {1, 2, 3};

        l2.merge(std::move(l1));

        ASSERT_EQ(queue::queue<int>({1, 2, 3, 4, 5}), l2);
    }
}

TEST(queue, RO5)
{
    // Copying
    {
        queue::queue<int> l1 = {1, 2, 3};
        queue::queue<int> l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Copy =
    {
        queue::queue<int> l1 = {1, 2, 3}, l2;
        l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Moving
    {
        queue::queue<int> l1{1, 2, 3};
        queue::queue<int> l2(std::move(l1));
        ASSERT_EQ(queue::queue<int>({1, 2, 3}), l2);
    }

    // Moving =
    {
        queue::queue<int> l1 = {1, 2, 3};
        queue::queue<int> l2;
        l2 = std::move(l1);
        ASSERT_EQ(queue::queue<int>({1, 2, 3}), l2);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
