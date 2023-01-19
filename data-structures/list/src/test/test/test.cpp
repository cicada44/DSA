#include "../../liblist/liblist/list.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(list_find_test, find_test)
{
    ASSERT_EQ(true, forward_list::list<int>({1, 2, 3, 4, 5}).find(3));
    ASSERT_EQ(true, forward_list::list<int>({1}).find(1));
    ASSERT_EQ(true, forward_list::list<int>({1, 1, 1}).find(1));
    ASSERT_EQ(true, forward_list::list<int>({3, 2, 1}).find(1));
    ASSERT_EQ(false, forward_list::list<int>({}).find(1));
    ASSERT_EQ(false, forward_list::list<int>({3, 2}).find(1));
    ASSERT_EQ(false, forward_list::list<int>({2, 2, 2}).find(1));
    ASSERT_EQ(false, forward_list::list<int>({0}).find(1));
}

TEST(list_size_test, size_test)
{
    ASSERT_EQ(0, forward_list::list<int>({}).size());
    ASSERT_EQ(1, forward_list::list<int>({1}).size());
    ASSERT_EQ(2, forward_list::list<int>({1, 2}).size());
}

TEST(list_push_test, push_test)
{
    forward_list::list<int> list_test_push_back = {};
    ASSERT_EQ(forward_list::list<int>({}), list_test_push_back);
    for (const auto& c : {1, 2, 3, 4, 5}) {
        list_test_push_back.push_back(c);
    }
    ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), list_test_push_back);

    forward_list::list<int> list_test_push_front = {};
    ASSERT_EQ(forward_list::list<int>({}), list_test_push_front);
    for (const auto& c : {5, 4, 3, 2, 1}) {
        list_test_push_front.push_front(c);
    }
    ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), list_test_push_front);
}

TEST(list_extract_test, extract_test)
{
    forward_list::list<int> extracted_list = {1, 2, 3, 4, 5};

    extracted_list.pop_back();
    ASSERT_EQ(extracted_list, forward_list::list<int>({1, 2, 3, 4}));
    extracted_list.pop_front();
    ASSERT_EQ(extracted_list, forward_list::list<int>({2, 3, 4}));
    extracted_list.pop_front();
    extracted_list.pop_front();
    extracted_list.pop_front();
    ASSERT_EQ(extracted_list, forward_list::list<int>({}));
}

TEST(list_remove_test, remove_test)
{
    forward_list::list<int> remove_members_list = {1, 2, 3, 4, 5};

    remove_members_list.remove(3);
    remove_members_list.remove(2);
    remove_members_list.remove(4);
    remove_members_list.remove(1);
    remove_members_list.remove(5);

    ASSERT_EQ(remove_members_list, forward_list::list<int>({}));
}

TEST(list_merge_test, merge_test)
{
    forward_list::list<int> list_to_merge = {4, 5};
    forward_list::list<int> mergarable_list = {1, 2, 3};

    mergarable_list.merge(list_to_merge);

    ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), mergarable_list);

    forward_list::list<int> list_to_move_merge = {4, 5};
    forward_list::list<int> mergarable_move_list = {1, 2, 3};

    mergarable_move_list.merge(std::move(list_to_move_merge));

    ASSERT_EQ(forward_list::list<int>({1, 2, 3, 4, 5}), mergarable_list);
}

TEST(list_copy_test, copy_test)
{
    forward_list::list<int> list_to_cpy = {1, 2, 3};
    forward_list::list<int> list1 = list_to_cpy;
    ASSERT_EQ(list1, list_to_cpy);

    forward_list::list<int> list_to_operator = {1, 2, 3};
    list1 = list_to_operator;
    ASSERT_EQ(list1, list_to_operator);

    forward_list::list<int> list_rval = {1, 2, 3};
    forward_list::list<int> list2(std::move(list_rval));
    ASSERT_EQ(list_rval, list2);

    forward_list::list<int> list_rval_operator = {1, 2, 3};
    forward_list::list<int> list3;
    list3 = std::move(list_rval);
    ASSERT_EQ(list_rval_operator, list3);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
