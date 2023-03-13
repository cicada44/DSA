#include "../../src/libvector/Vector.hpp"

#include <gtest/gtest.h>

#include <iostream>

// TEST(Vector, RO5)
// {
//     // Copy constructor
//     {
//         Vector<int> vec{1, 2, 3, 4, 5};
//         Vector<int> cpy_vec(vec);

//         ASSERT_EQ(vec, cpy_vec);

//         Vector<int> vec_mt;
//         Vector<int> cpy_vec_mt(vec_mt);

//         ASSERT_EQ(vec_mt, cpy_vec_mt);
//     }

//     // Operator =
//     {
//         Vector<int> vec{1, 2, 3, 4, 5};
//         Vector<int> cpy_vec;
//         cpy_vec = vec;

//         // ASSERT_EQ(vec, cpy_vec);

//         // Vector<int> vec_mt;
//         // Vector<int> cpy_vec_mt;
//         // cpy_vec_mt = vec_mt;

//         // ASSERT_EQ(vec_mt, cpy_vec_mt);
//     }
// }

TEST(Vector, ElementAccess)
{
    // At
    {
        Vector<int> v{0, 1, 2, 3, 4};

        for (size_t i = 0; i != 5; ++i) {
            ASSERT_NO_THROW(v.at(i));
            ASSERT_EQ(i, v.at(i));
        }

        for (size_t i = 5; i != 10; ++i) {
            ASSERT_THROW(v.at(i), std::out_of_range);
        }
    }

    // []
    {
        Vector<int> v{0, 1, 2, 3, 4};

        for (size_t i = 0; i != 5; ++i) {
            ASSERT_NO_THROW(v[i]);
            ASSERT_EQ(i, v[i]);
        }

        for (size_t i = 5; i != 10; ++i) {
            ASSERT_NO_THROW(v[i]);
        }
    }

    // begin & end
    {
        const Vector<int> v{0, 1, 2, 3, 4};

        *(v.begin()) = *(v.end() - 1) = 5;

        ASSERT_EQ(v, Vector<int>({5, 1, 2, 3, 5}));

        *(v.begin()) = *(v.end() - 1) = *(v.end() - 2) = *(v.end() - 3)
                = *(v.end() - 4) = 0;

        for (auto i = v.begin(); i != v.end(); ++i) {
            ASSERT_EQ(*i, 0);
        }
    }

    // data
    {
        const Vector<int> v{0, 1, 2, 3, 4};

        size_t cnter = 0;
        for (auto i = v.data(); i != v.data() + v.size_(); ++i) {
            ASSERT_EQ(*i, cnter);
            ++cnter;
        }
    }
}

TEST(Vector, Capacity)
{
    // Empty
    {
        ASSERT_EQ(Vector<int>({0, 1, 2, 3, 4}).empty(), false);
        ASSERT_EQ(Vector<int>().empty(), true);
    }

    // Size
    {
        ASSERT_EQ(Vector<int>({0, 1, 2, 3, 4}).size_(), 5);
        ASSERT_EQ(Vector<int>({0}).size_(), 1);
        ASSERT_EQ(Vector<int>().size_(), 0);
    }

    // Reserve & capacity
    {
        Vector<int> v{0, 1, 2, 3, 4};

        ASSERT_EQ(v, Vector<int>({0, 1, 2, 3, 4}));
        v.reserve(30);
        ASSERT_EQ(v.capacity_(), 30);

        v.reserve(5);
        ASSERT_EQ(v.capacity_(), 30);
    }

    // Capacity
    {
        ASSERT_LE(Vector<int>({0, 1, 2, 3, 4}).capacity_(), 30);
        ASSERT_EQ(Vector<int>({0}).capacity_(), 1);
        ASSERT_EQ(Vector<int>().capacity_(), 0);
    }

    // Shrink_to_fit
    {
        Vector<int> v{0, 1, 2, 3, 4};

        v.shrink_to_fit();
        ASSERT_EQ(v.capacity_(), 5);

        v.push_back(5);
        v.shrink_to_fit();
        ASSERT_EQ(v.capacity_(), 6);
    }
}

TEST(Vector, Modifiers)
{
    // Clear
    {
        Vector<int> v{0, 1, 2, 3, 4};

        v.clear();
        ASSERT_EQ(v, Vector<int>());
        ASSERT_EQ(v.capacity_(), 5);
    }

    // Insert(pointer, value)
    {
        Vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.begin() + 2, 0);
        ASSERT_EQ(v, Vector<int>({0, 1, 0, 2, 3, 4}));

        v.insert(v.begin(), 0);
        ASSERT_EQ(v, Vector<int>({0, 0, 1, 0, 2, 3, 4}));

        v.insert(v.end(), 0);
        ASSERT_EQ(v, Vector<int>({0, 0, 1, 0, 2, 3, 4, 0}));
    }

    // Insert(pointer, count, value)
    {
        Vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.begin() + 2, 3, 0);
        ASSERT_EQ(v, Vector<int>({0, 1, 0, 0, 0, 2, 3, 4}));

        v.insert(v.begin(), 2, 0);
        ASSERT_EQ(v, Vector<int>({0, 0, 0, 1, 0, 0, 0, 2, 3, 4}));

        v.insert(v.end(), 1, 0);
        ASSERT_EQ(v, Vector<int>({0, 0, 0, 1, 0, 0, 0, 2, 3, 4, 0}));
    }

    // Insert(pointer, p_beg, p_end)
    {
        Vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.begin(), v.begin(), v.begin() + 2);
        ASSERT_EQ(v, Vector<int>({0, 1, 0, 1, 2, 3, 4}));

        v.insert(v.begin() + 2, v.begin() + 3, v.begin() + 6);
        ASSERT_EQ(v, Vector<int>({0, 1, 1, 2, 3, 0, 1, 2, 3, 4}));

        v.insert(v.end(), v.begin(), v.end());
        ASSERT_EQ(v, Vector<int>({0, 1, 1, 2, 3, 0, 1, 2, 3, 4,
                                  0, 1, 1, 2, 3, 0, 1, 2, 3, 4}));

        Vector<int> v2(10);

        v2.insert(v2.begin(), v.begin(), v.end());
        ASSERT_EQ(v2, Vector<int>({0, 1, 1, 2, 3, 0, 1, 2, 3, 4,
                                   0, 1, 1, 2, 3, 0, 1, 2, 3, 4}));
    }

    // Insert(pointer, init_list)
    {
        Vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.end(), {5, 6});
        ASSERT_EQ(v, Vector<int>({0, 1, 2, 3, 4, 5, 6}));

        v.insert(v.begin() + 3, {0, 0, 0});
        ASSERT_EQ(v, Vector<int>({0, 1, 2, 0, 0, 0, 3, 4, 5, 6}));
    }
}

TEST(Vector, Finders) {
    // Contains_node
    {
        
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
