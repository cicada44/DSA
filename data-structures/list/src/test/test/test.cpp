#include "../../liblist/list.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(List, Containing) {
    ASSERT_EQ(true, list::list<int>({1, 2, 3, 4, 5}).contains(3));
    ASSERT_EQ(true, list::list<int>({1}).contains(1));
    ASSERT_EQ(true, list::list<int>({1, 1, 1}).contains(1));
    ASSERT_EQ(true, list::list<int>({3, 2, 1}).contains(1));
    ASSERT_EQ(false, list::list<int>({}).contains(1));
    ASSERT_EQ(false, list::list<int>({3, 2}).contains(1));
    ASSERT_EQ(false, list::list<int>({2, 2, 2}).contains(1));
    ASSERT_EQ(false, list::list<int>({0}).contains(1));
}

TEST(List, Size) {
    ASSERT_EQ(0, list::list<int>({}).size());
    ASSERT_EQ(1, list::list<int>({1}).size());
    ASSERT_EQ(2, list::list<int>({1, 2}).size());
}

TEST(List, BeginEnd) {
    // Normal
    {
        ASSERT_EQ(1, list::list<int>({1, 2, 3, 4, 5}).begin()->value);
        ASSERT_EQ(5, list::list<int>({1, 2, 3, 4, 5}).end()->value);
    }

    // Const
    {
        ASSERT_EQ(1, list::list<int>({1, 2, 3, 4, 5}).cbegin()->value);
        ASSERT_EQ(5, list::list<int>({1, 2, 3, 4, 5}).cend()->value);
    }
}

TEST(List, Count) {
    list::list<int> l{1, 2, 2, 2, 2, 2, 4};

    ASSERT_EQ(5, l.count(2));
    ASSERT_EQ(1, l.count(1));
    ASSERT_EQ(0, l.count(3));
}

TEST(List, IdxOperator) {
    list::list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    ASSERT_EQ(1, l[0].value);
    ASSERT_EQ(3, l[2].value);
    ASSERT_EQ(5, l[4].value);
    ASSERT_EQ(7, l[6].value);
    ASSERT_EQ(9, l[8].value);
}

TEST(List, Addition) {
    // Pushback
    {
        list::list<int> l;

        ASSERT_EQ(list::list<int>(), l);
        for (const auto& c : {1, 2, 3, 4, 5}) {
            l.push_back(c);
        }

        ASSERT_EQ(list::list<int>({1, 2, 3, 4, 5}), l);
    }

    // Pushfront
    {
        list::list<int> l;

        ASSERT_EQ(list::list<int>(), l);
        for (const auto& c : {5, 4, 3, 2, 1}) {
            l.push_front(c);
        }

        ASSERT_EQ(list::list<int>({1, 2, 3, 4, 5}), l);
    }
}

TEST(List, Removal) {
    // Popback
    {
        list::list<int> l = {1, 2, 3, 4, 5};

        l.pop_back();

        ASSERT_EQ(l, list::list<int>({1, 2, 3, 4}));
    }

    // Popfront
    {
        list::list<int> l = {1, 2, 3, 4};

        l.pop_front();

        ASSERT_EQ(l, list::list<int>({2, 3, 4}));

        l.pop_front();
        l.pop_front();
        l.pop_front();

        ASSERT_EQ(l, list::list<int>({}));
    }

    // EraseFirst
    {
        list::list<int> l = {1, 2, 3, 4, 5};

        l.erase_first(3);
        ASSERT_EQ(l, list::list<int>({1, 2, 4, 5}));

        l.erase_first(2);
        ASSERT_EQ(l, list::list<int>({1, 4, 5}));

        l.erase_first(4).erase_first(1).erase_first(5);
        ASSERT_EQ(l, list::list<int>({}));
    }

    // EraseLast
    {
        list::list<int> l = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

        l.erase_last(1);
        l.erase_last(2);
        l.erase_last(3);
        l.erase_last(4);
        l.erase_last(5);

        ASSERT_EQ(l, list::list<int>({1, 2, 3, 4, 5}));

        l.erase_last(1).erase_last(2).erase_last(3).erase_last(4).erase_last(5);
        ASSERT_EQ(l, list::list<int>());
    }

    // Erase
    {
        list::list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

        l.erase(1);
        l.erase(1);
        l.erase(1);
        l.erase(1);
        l.erase(1);

        ASSERT_EQ(l, list::list<int>({1, 7, 8, 9, 0}));

        l.erase(0).erase(0).erase(0).erase(0);

        ASSERT_EQ(l, list::list<int>({0}));
    }
}

TEST(List, Unique) {
    list::list<int> l1{1, 2, 3, 4, 5, 6, 7, 8};

    l1.unique();
    ASSERT_EQ(l1, l1);

    list::list<int> l2{1, 1, 1, 1, 2, 2, 2, 2, 2, 3};

    l2.unique();
    ASSERT_EQ(l2, list::list<int>({1, 2, 3}));
}

TEST(List, Merger) {
    // Merge lval
    {
        list::list<int> l1 = {4, 5};
        list::list<int> l2 = {1, 2, 3};

        l2.merge(l1);

        ASSERT_EQ(list::list<int>({1, 2, 3, 4, 5}), l2);
    }

    // Merge rval
    {
        list::list<int> l1 = {4, 5};
        list::list<int> l2 = {1, 2, 3};

        l2.merge(std::move(l1));

        ASSERT_EQ(list::list<int>({1, 2, 3, 4, 5}), l2);
    }
}

TEST(List, RO5) {
    // Copying
    {
        list::list<int> l1 = {1, 2, 3};
        list::list<int> l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Copy =
    {
        list::list<int> l1 = {1, 2, 3}, l2;
        l2 = l1;
        ASSERT_EQ(l2, l1);
    }

    // Moving
    {
        list::list<int> l1{1, 2, 3};
        list::list<int> l2(std::move(l1));
        ASSERT_EQ(list::list<int>({1, 2, 3}), l2);
    }

    // Moving =
    {
        list::list<int> l1 = {1, 2, 3};
        list::list<int> l2;
        l2 = std::move(l1);
        ASSERT_EQ(list::list<int>({1, 2, 3}), l2);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
