#include <iostream>

#include <algorithm>

template <typename T>
class Vector {
    template <typename TYPE>
    friend std::ostream& operator<<(std::ostream& os, const Vector<TYPE>& v);

public:
    Vector() : dynamic_table(nullptr), size(0), capacity(0)
    {
    }

    Vector(const std::initializer_list<T>& init_list)
        : dynamic_table(new T[init_list.size()]),
          size(init_list.size()),
          capacity(init_list.size())
    {
        size_t vec_indexator = 0;

        for (const auto& c : init_list) {
            dynamic_table[vec_indexator] = c;
            ++vec_indexator;
        }
    }

    ~Vector()
    {
        delete[] dynamic_table;
    }

    size_t size_() const
    {
        return size;
    }

    size_t capacity_() const
    {
        return capacity;
    }

    const T& operator[](size_t ind) const
    {
        try {
            return dynamic_table[ind];
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    void push_back(const T& push_node)
    {
        if (size == capacity) {
            T* helper = new T[size];

            copy_helper(helper, dynamic_table, size);

            delete[] dynamic_table;

            dynamic_table = new T[size * 2];

            copy_helper(dynamic_table, helper, size);

            delete[] helper;

            capacity *= 2;

            // std::cout << "realloc arr size - " << *helper << "capa - "
            //   << capacity << '\n';
        }

        dynamic_table[size] = push_node;

        ++size;
    }

private:
    T* dynamic_table;

    size_t size;
    size_t capacity;

    void copy_helper(T*& t1, T*& t2, const size_t n);
};

template <typename T>
void Vector<T>::copy_helper(T*& t1, T*& t2, const size_t n)
{
    for (size_t x = 0; x != n; ++x) {
        t1[x] = t2[x];
    }
}

template <typename TYPE>
std::ostream& operator<<(std::ostream& os, const Vector<TYPE>& v)
{
    for (size_t x = 0; x != v.size_(); ++x) {
        os << v.dynamic_table[x] << ' ';
    }
    os << '\n';

    return os;
}
