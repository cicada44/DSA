#include "../../liblist/list.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(List, Containing) {
    ASSERT_EQ(true, forward_list::list<int>({1, 2, 3, 4, 5}).contains(3));
    ASSERT_EQ(true, forward_list::list<int>({1}).contains(1));
    ASSERT_EQ(true, forward_list::list<int>({1, 1, 1}).contains(1));
    ASSERT_EQ(true, forward_list::list<int>({3, 2, 1}).contains(1));
    ASSERT_EQ(false, forward_list::list<int>({}).contains(1));
    ASSERT_EQ(false, forward_list::list<int>({3, 2}).contains(1));
    ASSERT_EQ(false, forward_list::list<int>({2, 2, 2}).contains(1));
    ASSERT_EQ(false, forward_list::list<int>({0}).contains(1));
}

TEST(List, Size) {
    ASSERT_EQ(0, forward_list::list<int>({}).size());
    ASSERT_EQ(1, forward_list::list<int>({1}).size());
    ASSERT_EQ(2, forward_list::list<int>({1, 2}).size());
}

TEST(List, BeginEnd) {
    ASSERT_EQ(1, forward_list::list<int>({1, 2, 3, 4, 5}).begin()->value);
    ASSERT_EQ(5, forward_list::list<int>({1, 2, 3, 4, 5}).end()->value);
}

TEST(List, Addition) {
    // Pushback
    {
        forward_list::list<int> l = {};

        ASSERT_EQ(forward_list::list<int>({}), l);
        for (const auto& c : {1, 2, 3, 4, 5}) {
            l.push_back(c);
        }

        ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), l);
    }

    // Pushfront
    {
        forward_list::list<int> l = {};

        ASSERT_EQ(forward_list::list<int>({}), l);
        for (const auto& c : {5, 4, 3, 2, 1}) {
            l.push_front(c);
        }
        ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), l);
    }
}

TEST(List, Removal) {
    // Popback
    {
        forward_list::list<int> l = {1, 2, 3, 4, 5};

        l.pop_back();

        ASSERT_EQ(l, forward_list::list<int>({1, 2, 3, 4}));
    }

    // Popfront
    {
        forward_list::list<int> l = {1, 2, 3, 4};

        l.pop_front();

        ASSERT_EQ(l, forward_list::list<int>({2, 3, 4}));

        l.pop_front();
        l.pop_front();
        l.pop_front();

        ASSERT_EQ(l, forward_list::list<int>({}));
    }

    // Removefirst
    {
        forward_list::list<int> l = {1, 2, 3, 4, 5};

        l.remove_first(3);
        l.remove_first(2);
        l.remove_first(4);
        l.remove_first(1);
        l.remove_first(5);

        ASSERT_EQ(l, forward_list::list<int>({}));
    }
}

TEST(List, Merger) {
    // Merge lval
    {
        forward_list::list<int> l1 = {4, 5};
        forward_list::list<int> l2 = {1, 2, 3};

        l2.merge(l1);

        ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), l2);
    }

    // Merge rval
    {
        forward_list::list<int> l1 = {4, 5};
        forward_list::list<int> l2 = {1, 2, 3};

        l2.merge(std::move(l1));

        ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), l2);
    }
}

TEST(List, RO5) {
    // Copying
    {
        forward_list::list<int> l1 = {1, 2, 3};
        forward_list::list<int> l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Copy =
    {
        forward_list::list<int> l1 = {1, 2, 3}, l2;
        l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Moving
    {
        forward_list::list<int> l1 = {1, 2, 3};
        forward_list::list<int> l2(std::move(l1));
        ASSERT_EQ(l1, l2);
    }

    // Moving =
    {
        forward_list::list<int> l1 = {1, 2, 3};
        forward_list::list<int> l2;
        l2 = std::move(l1);
        ASSERT_EQ(l1, l2);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
