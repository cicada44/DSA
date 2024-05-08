#include <gtest/gtest.h>
#include <matrix_t.h>

using namespace matrix_t;

TEST(Matrix, Init) {
    // 5x5
    {
        matrix<int> m(5, 5);
        ASSERT_EQ(m.rows(), 5);
        ASSERT_EQ(m.cols(), 5);
        ASSERT_EQ(m.empty(), false);
        ASSERT_EQ(m.size(), 25);
        ASSERT_EQ(m.capacity(), 50);
        ASSERT_NO_THROW(m.at(4, 4));
    }

    // 2x10
    {
        matrix<int> m(2, 10);
        ASSERT_EQ(m.rows(), 2);
        ASSERT_EQ(m.cols(), 10);
        ASSERT_EQ(m.empty(), false);
        ASSERT_EQ(m.size(), 20);
        ASSERT_EQ(m.capacity(), 40);
        ASSERT_NO_THROW(m.at(1, 9));
    }

    // List 3x3
    {
        matrix<int> m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ASSERT_EQ(m.rows(), 3);
        ASSERT_EQ(m.cols(), 3);
        ASSERT_EQ(m.empty(), false);
        ASSERT_EQ(m.size(), 9);
        ASSERT_EQ(m.capacity(), 18);
        ASSERT_NO_THROW(m.at(2, 2));
    }

    // Invalid List 3x3
    { ASSERT_ANY_THROW(matrix<int>({{1, 2, 3, 4}, {4, 5, 6}, {7, 8, 9}})); }
}

TEST(Matrix, RO5) {
    // Copy constructor
    {
        const matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        const matrix<int> m2(m);
        ASSERT_EQ(m2, matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    }

    // Move constructor
    {
        matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        const matrix<int> m2(std::move(m));
        ASSERT_EQ(m2, matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    }

    // Copy assignment
    {
        const matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        matrix<int> m2({{1}});
        m2 = m;
        ASSERT_EQ(m2, matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    }

    // Copy assignment
    {
        matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        matrix<int> m2({{1}});
        m2 = std::move(m);
        ASSERT_EQ(m2, matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    }
}

TEST(Matrix, ElemsChanging) {
    // 5x5
    {
        matrix<int> m(5, 5);
        for (int i = 0; i != 5; ++i)
            for (int j = 0; j != 5; ++j) m.at(i, j) = i * 5 + j;
        for (int i = 0; i != 5; ++i)
            for (int j = 0; j != 5; ++j) ASSERT_EQ(m.at(i, j), i * 5 + j);
    }

    // 1x1
    {
        matrix<int> m(1, 1);
        m.at(0, 0) = -1;
        ASSERT_EQ(m.at(0, 0), -1);
    }
}

TEST(Matrix, ResizeRow) {
    // Decreasing
    {
        matrix<int> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        m.resize_row(2);

        ASSERT_EQ(m.rows(), 2);
        ASSERT_EQ(m, matrix<int>({{1, 2, 3, 4}, {5, 6, 7, 8}}));
    }

    // Increasing
    {
        matrix<int> m = {{1, 2, 3, 4}, {5, 6, 7, 8}};
        m.resize_row(3);

        ASSERT_EQ(m.rows(), 3);
        ASSERT_EQ(m, matrix<int>({{1, 2, 3, 4}, {5, 6, 7, 8}, {0, 0, 0, 0}}));
    }

    // Still
    {
        matrix<int> m = {{1, 2, 3, 4}, {5, 6, 7, 8}};
        m.resize_row(2);

        ASSERT_EQ(m.rows(), 2);
        ASSERT_EQ(m, matrix<int>({{1, 2, 3, 4}, {5, 6, 7, 8}}));
    }
}

TEST(Matrix, ResizeCol) {
    // 0
    {
        matrix<int> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        m.resize_col(0);

        ASSERT_EQ(m.cols(), 4);
        ASSERT_EQ(m, matrix<int>({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}));
    }

    // 1
    {
        matrix<int> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        m.resize_col(5);

        ASSERT_EQ(m.cols(), 5);
        ASSERT_EQ(m, matrix<int>({{1, 2, 3, 4, 0}, {5, 6, 7, 8, 0}, {9, 10, 11, 12, 0}}));
    }

    // 2
    {
        matrix<int> m = {{1}, {2}, {3}};
        m.resize_col(10);

        ASSERT_EQ(m.cols(), 10);
        ASSERT_EQ(
            m, matrix<int>(
                   {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {2, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {3, 0, 0, 0, 0, 0, 0, 0, 0, 0}}));
    }

    // 3
    {
        matrix<int> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        m.resize_col(2);

        ASSERT_EQ(m.cols(), 2);
        ASSERT_EQ(m, matrix<int>({{1, 2}, {5, 6}, {9, 10}}));
    }
}

TEST(Matrix, Reserve) {
    // Random N1
    {
        matrix<int> m{{1}, {2}, {3}};
        ASSERT_EQ(m.capacity(), 6);
        m.reserve(5);
        ASSERT_EQ(m.capacity(), 6);
        ASSERT_EQ(m, matrix<int>({{1}, {2}, {3}}));
    }

    // Random N2
    {
        matrix<int> m{{1, 2, 3}};
        ASSERT_EQ(m.capacity(), 6);
        m.reserve(10);
        ASSERT_EQ(m.capacity(), 10);
        ASSERT_EQ(m, matrix<int>({{1, 2, 3}}));
    }

    // Random N3
    {
        matrix<int> m{{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
        ASSERT_EQ(m.capacity(), 18);
        m.reserve(15);
        ASSERT_EQ(m.capacity(), 18);
        ASSERT_EQ(m, matrix<int>({{1, 2, 3}, {2, 3, 4}, {3, 4, 5}}));
    }
}

TEST(Matrix, ShrinkToFit) {
    // 0
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ASSERT_EQ(m.capacity(), 18);
        m.shrink_to_fit();
        ASSERT_EQ(m.capacity(), 9);
    }

    // 1
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ASSERT_EQ(m.capacity(), 18);
        m.shrink_to_fit();
        ASSERT_EQ(m.capacity(), 9);
        m.shrink_to_fit();
        ASSERT_EQ(m.capacity(), 9);
    }

    // 2
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.shrink_to_fit();
        ASSERT_EQ(m.capacity(), 9);
        m.resize_row(4);
        ASSERT_EQ(m.capacity(), 21);
    }
}

TEST(Matrix, Iterators) {
    // Normal
    {
        const matrix<int> m{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        int c = 1;
        for (const auto& i : m) ASSERT_EQ(i, c++);
    }

    // Const
    {
        const matrix<int> m{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        int c = 1;
        for (const auto& i : m) ASSERT_EQ(i, c++);
    }
}

TEST(Matrix, InsertRow) {
    // 0
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.insert_row(2, {1, 1, 1});
        ASSERT_EQ(m, matrix<int>({{1, 2, 3}, {4, 5, 6}, {1, 1, 1}, {7, 8, 9}}));
    }

    // 1
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.insert_row(0, {1, 1, 1});
        ASSERT_EQ(m, matrix<int>({{1, 1, 1}, {1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    }

    // 2
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.insert_row(3, {1, 1, 1});
        ASSERT_EQ(m, matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 1, 1}}));
    }

    // invalid pos for inserting
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ASSERT_THROW(m.insert_row(5, {1, 1, 1}), std::out_of_range);
    }

    // invalid size of inserting row
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ASSERT_THROW(m.insert_row(1, {1, 1, 1, 1}), std::runtime_error);
    }
}

TEST(Matrix, InsertCol) {
    // 0
    {
        matrix<int> m = {{1, 2}, {4, 5}, {7, 8}};
        m.insert_col(2, {3, 6, 9});
        ASSERT_EQ(m, matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    }

    // 1
    {
        matrix<int> m = {{1, 2, 3, 5}, {4, 5, 6, 8}, {7, 8, 9, 11}};
        m.insert_col(3, {4, 7, 10});
        ASSERT_EQ(m, matrix<int>({{1, 2, 3, 4, 5}, {4, 5, 6, 7, 8}, {7, 8, 9, 10, 11}}));
    }

    // 2
    {
        matrix<int> m = {{1}, {1}, {1}};
        m.insert_col(1, {2, 2, 2});
        m.insert_col(2, {3, 3, 3});
        m.insert_col(3, {4, 4, 4});
        ASSERT_EQ(m, matrix<int>({{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}}));
    }

    // invalid pos for inserting
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ASSERT_THROW(m.insert_col(5, {1, 1, 1}), std::out_of_range);
    }

    // invalid size of inserting col
    {
        matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        ASSERT_THROW(m.insert_col(1, {1, 1, 1, 1}), std::runtime_error);
    }
}

TEST(Matrix, Erase) {
    // 0
    {
        matrix<int> m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.erase(1, 1);
        ASSERT_EQ(m, matrix<int>({{1, 3}, {7, 9}}));
    }

    // 1
    {
        matrix<int> m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.erase(1, 1);
        m.erase(1, 1);
        ASSERT_EQ(m, matrix<int>({{1}}));
    }

    // 0
    {
        matrix<int> m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        m.erase(1, 1);
        m.erase(1, 1);
        ASSERT_THROW(m.erase(1, 1), std::out_of_range);
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
