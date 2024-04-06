#include <gtest/gtest.h>
#include <list.h>

using namespace dll;

// Test case for the empty list
TEST(ListTest, IsEmpty) {
    list<int> lst;
    ASSERT_TRUE(lst.empty());
}

// Test case for the size of the list
TEST(ListTest, Size) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    ASSERT_EQ(lst.size(), 3);
}

// Test case for the front element of the list
TEST(ListTest, Front) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    ASSERT_EQ(lst.front(), 1);
}

// Test case for the back element of the list
TEST(ListTest, Back) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    ASSERT_EQ(lst.back(), 3);
}

// Test case for inserting elements at the beginning of the list
TEST(ListTest, PushFront) {
    list<int> lst;
    lst.push_front(1);
    lst.push_front(0);
    lst.push_front(-1);
    ASSERT_EQ(lst.front(), -1);
}

// Test case for inserting elements at the end of the list
TEST(ListTest, PushBack) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    ASSERT_EQ(lst.back(), 3);
}

// // Test case for iterating through the list
TEST(ListTest, Iteration) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    int sum = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        sum += *it;
    }
    ASSERT_EQ(sum, 6);
}

// // Test case for clearing the list
TEST(ListTest, Clear) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.clear();
    ASSERT_TRUE(lst.empty());
}

// // Test case for copying the list
TEST(ListTest, Copy) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    list<int> lst_copy(lst);
    ASSERT_EQ(lst_copy.size(), 3);
}

// // Test case for moving the list
TEST(ListTest, Move) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    list<int> lst_moved(std::move(lst));
    ASSERT_EQ(lst_moved.size(), 3);
}

// // Test case for the destructor
TEST(ListTest, Destructor) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.clear();
    ASSERT_TRUE(lst.empty());
}

// // Test case for iterator increment
TEST(ListTest, IteratorIncrement) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto it = lst.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
}

// Test case for iterator decrement
TEST(ListTest, IteratorDecrement) {
    list<int> lst;
    lst.push_back(3);
    lst.push_back(2);
    lst.push_back(1);
    auto it = lst.rbegin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
}

// // Test case for iterator equality
TEST(ListTest, IteratorEquality) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto it1 = lst.begin();
    auto it2 = lst.begin();
    auto it3 = lst.end();
    ASSERT_TRUE(it1 == it2);
    ASSERT_FALSE(it1 == it3);
}

// // Test case for iterator inequality
TEST(ListTest, IteratorInequality) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto it1 = lst.begin();
    auto it2 = lst.end();
    ASSERT_TRUE(it1 != it2);
}

// // Test case for iterator access to the end
TEST(ListTest, IteratorAccessToEnd) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto it = lst.end();
    ASSERT_TRUE(it == lst.end());
    // ASSERT_THROW(++it, std::out_of_range);
}

// // Test case for const_iterator increment
TEST(ListTest, ConstIteratorIncrement) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto it = lst.cbegin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
}

// // Test case for const_iterator decrement
TEST(ListTest, ConstIteratorDecrement) {
    list<int> lst;
    lst.push_back(3);
    lst.push_back(2);
    lst.push_back(1);
    auto it = lst.crbegin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
}

// Test case for const_iterator equality
TEST(ListTest, ConstIteratorEquality) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto it1 = lst.cbegin();
    auto it2 = lst.cbegin();
    auto it3 = lst.cend();
    ASSERT_TRUE(it1 == it2);
    ASSERT_FALSE(it1 == it3);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
