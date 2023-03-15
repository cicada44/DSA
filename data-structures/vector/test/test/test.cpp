#include "../../src/libvector/Vector.hpp"

#include <gtest/gtest.h>

#include <iostream>

using namespace mdt;

TEST(Vector, RO5)
{
    // Copy constructor
    {
        vector<int> vec{1, 2, 3, 4, 5};
        vector<int> cpy_vec(vec);

        ASSERT_EQ(vec, cpy_vec);

        vector<int> vec_mt;
        vector<int> cpy_vec_mt(vec_mt);

        ASSERT_EQ(vec_mt, cpy_vec_mt);
    }

    // Move constructor
    {
        vector<int> vec{1, 2, 3, 4, 5};
        vector<int> cpy_vec(std::move(vec));

        ASSERT_EQ(cpy_vec, vector<int>({1, 2, 3, 4, 5}));

        vector<int> vec_mt;
        vector<int> cpy_vec_mt(std::move(vec_mt));

        ASSERT_EQ(vec_mt, cpy_vec_mt);
    }

    // Operator =
    {
        vector<int> vec{1, 2, 3, 4, 5};
        vector<int> cpy_vec;
        cpy_vec = vec;

        ASSERT_EQ(vec, cpy_vec);

        vector<int> vec_mt;
        vector<int> cpy_vec_mt;
        cpy_vec_mt = vec_mt;

        ASSERT_EQ(vec_mt, cpy_vec_mt);
    }

    // Move operator =
    {
        vector<int> vec{1, 2, 3, 4, 5};
        vector<int> cpy_vec;
        cpy_vec = std::move(vec);

        ASSERT_EQ(cpy_vec, vector<int>({1, 2, 3, 4, 5}));

        vector<int> vec_mt;
        vector<int> cpy_vec_mt;
        cpy_vec_mt = std::move(vec_mt);

        ASSERT_EQ(cpy_vec_mt, vector<int>());
    }
}

TEST(Vector, ElementAccess)
{
    // At
    {
        vector<int> v{0, 1, 2, 3, 4};

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
        vector<int> v{0, 1, 2, 3, 4};

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
        const vector<int> v{0, 1, 2, 3, 4};

        *(v.begin()) = *(v.end() - 1) = 5;

        ASSERT_EQ(v, vector<int>({5, 1, 2, 3, 5}));

        *(v.begin()) = *(v.end() - 1) = *(v.end() - 2) = *(v.end() - 3)
                = *(v.end() - 4) = 0;

        for (auto i = v.begin(); i != v.end(); ++i) {
            ASSERT_EQ(*i, 0);
        }
    }

    // data
    {
        const vector<int> v{0, 1, 2, 3, 4};

        size_t cnter = 0;
        for (auto i = v.data(); i != v.data() + v.size(); ++i) {
            ASSERT_EQ(*i, cnter);
            ++cnter;
        }
    }

    // distance
    {
        vector<int> v{0, 1, 2, 3, 4, 5};

        ASSERT_EQ(v.distance(v.begin(), v.end()), 6);
        ASSERT_EQ(v.distance(&v[1], &v[3]), 2);
    }
}

TEST(Vector, Capacity)
{
    // Empty
    {
        ASSERT_EQ(vector<int>({0, 1, 2, 3, 4}).empty(), false);
        ASSERT_EQ(vector<int>().empty(), true);
    }

    // Size
    {
        ASSERT_EQ(vector<int>({0, 1, 2, 3, 4}).size(), 5);
        ASSERT_EQ(vector<int>({0}).size(), 1);
        ASSERT_EQ(vector<int>().size(), 0);
    }

    // Reserve & capacity
    {
        vector<int> v{0, 1, 2, 3, 4};

        ASSERT_EQ(v, vector<int>({0, 1, 2, 3, 4}));
        v.reserve(30);
        ASSERT_EQ(v.capacity(), 30);

        v.reserve(5);
        ASSERT_EQ(v.capacity(), 30);
    }

    // Capacity
    {
        ASSERT_LE(vector<int>({0, 1, 2, 3, 4}).capacity(), 30);
        ASSERT_EQ(vector<int>({0}).capacity(), 1);
        ASSERT_EQ(vector<int>().capacity(), 0);
    }

    // Shrink_to_fit
    {
        vector<int> v{0, 1, 2, 3, 4};

        v.shrink_to_fit();
        ASSERT_EQ(v.capacity(), 5);

        v.push_back(5);
        v.shrink_to_fit();
        ASSERT_EQ(v.capacity(), 6);
    }
}

TEST(Vector, Modifiers)
{
    // Clear
    {
        vector<int> v{0, 1, 2, 3, 4};

        v.clear();
        ASSERT_EQ(v, vector<int>());
        ASSERT_EQ(v.capacity(), 5);
    }

    // push_back
    {
        vector<int> v{1, 2};

        v.push_back(3);
        ASSERT_EQ(v, vector<int>({1, 2, 3}));

        vector<int> v_mt;

        v_mt.push_back(1);
        ASSERT_EQ(v_mt, vector<int>({1}));
    }

    // Insert(pointer, value)
    {
        vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.begin() + 2, 0);
        ASSERT_EQ(v, vector<int>({0, 1, 0, 2, 3, 4}));

        v.insert(v.begin(), 0);
        ASSERT_EQ(v, vector<int>({0, 0, 1, 0, 2, 3, 4}));

        v.insert(v.end(), 0);
        ASSERT_EQ(v, vector<int>({0, 0, 1, 0, 2, 3, 4, 0}));
    }

    // Insert(pointer, count, value)
    {
        vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.begin() + 2, 3, 0);
        ASSERT_EQ(v, vector<int>({0, 1, 0, 0, 0, 2, 3, 4}));

        v.insert(v.begin(), 2, 0);
        ASSERT_EQ(v, vector<int>({0, 0, 0, 1, 0, 0, 0, 2, 3, 4}));

        v.insert(v.end(), 1, 0);
        ASSERT_EQ(v, vector<int>({0, 0, 0, 1, 0, 0, 0, 2, 3, 4, 0}));
    }

    // Insert(pointer, p_beg, p_end)
    {
        vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.begin(), v.begin(), v.begin() + 2);
        ASSERT_EQ(v, vector<int>({0, 1, 0, 1, 2, 3, 4}));

        v.insert(v.begin() + 2, v.begin() + 3, v.begin() + 6);
        ASSERT_EQ(v, vector<int>({0, 1, 1, 2, 3, 0, 1, 2, 3, 4}));

        v.insert(v.end(), v.begin(), v.end());
        ASSERT_EQ(v, vector<int>({0, 1, 1, 2, 3, 0, 1, 2, 3, 4,
                                  0, 1, 1, 2, 3, 0, 1, 2, 3, 4}));

        vector<int> v2(10);

        v2.insert(v2.begin(), v.begin(), v.end());
        ASSERT_EQ(v2, vector<int>({0, 1, 1, 2, 3, 0, 1, 2, 3, 4,
                                   0, 1, 1, 2, 3, 0, 1, 2, 3, 4}));
    }

    // Insert(pointer, init_list)
    {
        vector<int> v{0, 1, 2, 3, 4};

        v.insert(v.end(), {5, 6});
        ASSERT_EQ(v, vector<int>({0, 1, 2, 3, 4, 5, 6}));

        v.insert(v.begin() + 3, {0, 0, 0});
        ASSERT_EQ(v, vector<int>({0, 1, 2, 0, 0, 0, 3, 4, 5, 6}));
    }
}

TEST(Vector, Finders)
{
    // Contains_node
    {
        vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

        ASSERT_EQ(v.contains_node(1), true);
        ASSERT_EQ(v.contains_node(10), false);
    }

    // Find(node)
    {
        vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

        ASSERT_EQ(v.find(1) != v.end(), true);
        ASSERT_EQ(v.find(10) == v.end(), true);
    }
}

TEST(Vector, Remove)
{
    // Remove(node)
    {
        vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

        for (size_t i = 0; i != 5; ++i) {
            v.remove_first(i);
        }

        ASSERT_EQ(v, vector<int>({5, 6, 7, 8, 9}));

        for (size_t i = 5; i != 10; ++i) {
            v.remove_first(i);
        }

        ASSERT_EQ(v, vector<int>());
    }

    // Remove(pointer)
    {
        vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

        v.remove(v.begin());
        v.remove(v.begin() + 3);

        ASSERT_EQ(v, vector<int>({2, 3, 4, 6, 7, 8, 9, 0}));

        for (size_t i = 0; i != 7; ++i) {
            ASSERT_NE(v.remove(&v[0]), v.end());
        }

        ASSERT_EQ(v, vector<int>({0}));
    }

    // Remove(beg, end)
    {
        vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

        v.remove(v.begin(), v.begin() + 3);

        ASSERT_EQ(v, vector<int>({4, 5, 6, 7, 8, 9, 0}));

        v.remove(v.begin(), v.end());

        ASSERT_EQ(v, vector<int>());
    }

    // pop_back()
    {
        vector<int> v{1, 2, 3};

        v.pop_back();
        ASSERT_EQ(v, vector<int>({1, 2}));

        v.pop_back();
        v.pop_back();
        ASSERT_EQ(v, vector<int>());
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
