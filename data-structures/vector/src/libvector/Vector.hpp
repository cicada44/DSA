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

    Vector(const size_t capa)
        : dynamic_table(new T[capa]), size(0), capacity(capa)
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

    Vector(const T* const arr, size_t s) : Vector(s)
    {
        for (size_t i = 0; i != s; ++i) {
            push_back(arr[i]);
        }
    }

    Vector(Vector<T>& v_copy) : Vector(v_copy.dynamic_table, v_copy.size)
    {
    }

    ~Vector();

    size_t size_() const;
    size_t capacity_() const;

    T* begin() const;
    T* end() const;
    const T* cbegin() const;
    const T* cend() const;

    const T& operator[](size_t ind) const;
    T& operator[](size_t ind);

    void push_back(const T& push_node);
    void pop_back();

    bool contains_node(const T& node) const;
    T* find(const T& node);

    T* remove(const T& node);

private:
    T* dynamic_table;

    size_t size;
    size_t capacity;

    void copy_helper(T*& t1, T*& t2, const size_t n);
};

template <typename T>
Vector<T>::~Vector()
{
    delete[] dynamic_table;
}

template <typename T>
size_t Vector<T>::size_() const
{
    return size;
}

template <typename T>
size_t Vector<T>::capacity_() const
{
    return capacity;
}

template <typename T>
T* Vector<T>::begin() const
{
    return dynamic_table;
}

template <typename T>
T* Vector<T>::end() const
{
    return (dynamic_table + size);
}

template <typename T>
const T* Vector<T>::cbegin() const
{
    return dynamic_table;
}

template <typename T>
const T* Vector<T>::cend() const
{
    return (dynamic_table + size);
}

template <typename T>
const T& Vector<T>::operator[](size_t ind) const
{
    try {
        return dynamic_table[ind];
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

template <typename T>
T& Vector<T>::operator[](size_t ind)
{
    try {
        return dynamic_table[ind];
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

template <typename T>
void Vector<T>::push_back(const T& push_node)
{
    if (size == capacity) {
        T* helper = new T[size];

        copy_helper(helper, dynamic_table, size);

        delete[] dynamic_table;

        dynamic_table = new T[size * 2];

        copy_helper(dynamic_table, helper, size);

        delete[] helper;

        capacity *= 2;
    }

    dynamic_table[size] = push_node;

    ++size;
}

template <typename T>
void Vector<T>::pop_back()
{
    --size;
}

template <typename T>
bool Vector<T>::contains_node(const T& node) const
{
    for (int x = 0; x != size; ++x) {
        if (node == dynamic_table[x]) {
            return 1;
        }
    }

    return 0;
}

template <typename T>
T* Vector<T>::find(const T& node)
{
    for (size_t x = 0; x != size; ++x) {
        if (dynamic_table[x] == node) {
            return &dynamic_table[x];
        }
    }

    return &dynamic_table[size];
}

template <typename T>
T* Vector<T>::remove(const T& node)
{
    T* elem = find(node);

    if (elem == end()) {
        return end();
    }

    for (auto i = elem; i != end(); ++i) {
        std::swap(*i, *(i + 1));
    }

    return ++elem;
}

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
