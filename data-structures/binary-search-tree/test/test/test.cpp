#include "../../src/libtree/BSTree.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(bst_insert_test, insert_test)
{
    Tree<int, bool>* t1 = new Tree<int, bool>(0, 0);
    Tree<int, bool>* t2 = new Tree<int, bool>(1, 0);
    ASSERT_EQ(same(t1, t2), true);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}