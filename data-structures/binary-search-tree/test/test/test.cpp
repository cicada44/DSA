#include "../../src/libtree/BSTree.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(bst_insert_test, insert_test)
{
    Tree<int, bool>* t1 = new Tree<int, bool>(0, 0);
    Tree<int, bool>* t2 = new Tree<int, bool>(0, 0);
    ASSERT_EQ(same(t1, t2), true);
    t1->insert_list({{5, 0}, {2, 0}, {6, 0}, {3, 0}});
    t2->insert_list({{5, 0}, {2, 0}, {6, 0}, {3, 0}});
    ASSERT_EQ(same(t1, t2), true);

    delete t1;
    delete t2;
}

TEST(bst_delete_test, delete_test)
{
    Tree<int, bool>* t1 = new Tree<int, bool>(0, 0);
    Tree<int, bool>* t2 = new Tree<int, bool>(0, 0);
    t1->insert_list({{5, 0}, {2, 0}, {6, 0}, {3, 0}});
    t2->insert_list({{5, 0}, {2, 0}, {6, 0}, {3, 0}});
    t1->remove(5);
    t2->remove(5);
    ASSERT_EQ(same(t1, t2), true);
    t1->remove(2);
    t2->remove(2);

    delete t1;
    delete t2;
}

TEST(bst_lookup_test, lookup_test)
{
    Tree<int, bool>* t1 = new Tree<int, bool>(0, 0);
    t1->insert_list({{5, 0}, {2, 1}, {6, 0}, {3, 0}});
    ASSERT_EQ(t1->find(2).second, true);

    delete t1;
}

TEST(bst_minmax_test, minmax_test)
{
    Tree<int, bool>* t1 = new Tree<int, bool>(0, 0);
    t1->insert_list({{5, 0}, {2, 0}, {6, 1}, {3, 0}});
    ASSERT_EQ(t1->min().second, false);
    ASSERT_EQ(t1->max().second, true);

    delete t1;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}