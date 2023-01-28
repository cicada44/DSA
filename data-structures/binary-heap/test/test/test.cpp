#include <gtest/gtest.h>

#include <vector>

#include "../../src/Heap/Heap.hpp"

TEST(heap_init_test, init_test)
{
    Heap<int, int> h1(10), h2(10);

    h1.add_list({{1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}});
    for (const auto& c : {1, 2, 3, 4, 5}) {
        h2.insert(c, c - 1);
    }

    EXPECT_TRUE(h1 == h2);
}

TEST(heap_insert_test, insert_test)
{
    Heap<int, int> h1(1000), h2(1000);

    for (int x = 10; x < 100; ++x) {
        h1.insert(x, x - 1);
        h2.insert(x, x - 1);
        EXPECT_TRUE(h1 == h2);
    }
}

TEST(heap_max_test, max_test)
{
    Heap<int, int> h1(1000);

    for (int x = 0; x < 1000; x++) {
        h1.insert(x, x - 1);
        EXPECT_TRUE(h1.max().first == x);
    }
}

TEST(heap_extract_max_test, extract_max_test)
{
    Heap<int, int> h1(1000);

    for (int x = 0; x < 1000; x++) {
        h1.insert(x, x - 1);
        EXPECT_TRUE(h1.extract_max().first == x);
    }
}

TEST(heap_increase_test, increase_test)
{
    Heap<int, int> h1(1000);

    for (int x = 0; x < 1000; x++) {
        h1.insert(x, x - 1);
        h1.increase_key(x, x + 1);
    }

    EXPECT_TRUE(h1.max().first == 1000);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}