#include <iostream>

#include <algorithm>

#include <string>

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

    Vector(const T* const arr, const size_t s) : Vector(s)
    {
        for (size_t i = 0; i != s; ++i) {
            push_back(arr[i]);
        }
    }

    Vector(Vector<T>& v_copy) : Vector(v_copy.dynamic_table, v_copy.size)
    {
    }

    Vector<T>& operator=(const Vector<T>& vec)
    {
        clear();

        for (size_t i = 0; i != vec.size_(); ++i) {
            push_back(vec[i]);
        }

        return *this;
    }

    ~Vector();

    size_t size_() const;
    size_t capacity_() const;
    bool empty() const noexcept;

    void reserve(const size_t new_capa);
    void shrink_to_fit();

    T* begin() const;
    T* end() const;
    const T* cbegin() const;
    const T* cend() const;

    const T& operator[](size_t ind) const noexcept;
    T& operator[](size_t ind) noexcept;

    const T& at(const size_t pos) const;
    T& at(const size_t pos);

    T* data() const;

    void push_back(const T& push_node);

    void insert(T* pos, const T& value);
    void insert(T* pos, size_t count, const T& value);
    void insert(T* pos, T* beg, T* end);

    bool contains_node(const T& node) const;
    T* find(const T& node);

    T* remove(const T& node);
    void clear() noexcept;
    void pop_back();

private:
    T* dynamic_table;

    size_t size;
    size_t capacity;

    void copy_helper(T*& t1, const T* const& t2, const size_t n);
    void valid_idx(
            const size_t idx,
            const std::string& msg = std::string("index is out of size")) const;
};

template <typename T>
Vector<T>::~Vector()
{
    delete[] dynamic_table;
}

/* Returns size of actual vector. */
template <typename T>
size_t Vector<T>::size_() const
{
    return size;
}

/* Returns capacity of actual vector. */
template <typename T>
size_t Vector<T>::capacity_() const
{
    return capacity;
}

/* Returns 1 if vector is empty, 0 - if doesn't. */
template <typename T>
bool Vector<T>::empty() const noexcept
{
    return (size == 0);
}

/* Reserves memory for vector if new_capa > capa. */
template <typename T>
void Vector<T>::reserve(const size_t new_capa)
{
    if (new_capa > capacity) {
        T* temp = new T[size];
        copy_helper(temp, dynamic_table, size);

        delete[] dynamic_table;

        try {
            dynamic_table = new T[new_capa];
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        copy_helper(dynamic_table, temp, size);
        delete[] temp;

        capacity = new_capa;
    }
}

/* Requests the removal of unused capacity. */
template <typename T>
void Vector<T>::shrink_to_fit()
{
    T* temp = new T[size];
    copy_helper(temp, dynamic_table, size);

    delete[] dynamic_table;

    try {
        dynamic_table = new T[size];
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    copy_helper(dynamic_table, temp, size);
    delete[] temp;

    capacity = size;
}

/* Returns pointer to begin of the actual vector. */
template <typename T>
T* Vector<T>::begin() const
{
    return dynamic_table;
}

/* Returns pointer to end of the actual vector. */
template <typename T>
T* Vector<T>::end() const
{
    return (dynamic_table + size);
}

/* Returns constant pointer to begin of the actual vector. */
template <typename T>
const T* Vector<T>::cbegin() const
{
    return dynamic_table;
}

/* Returns constant pointer to end of the actual vector. */
template <typename T>
const T* Vector<T>::cend() const
{
    return (dynamic_table + size);
}

/* Return constant reference to the element at index idx. */
template <typename T>
const T& Vector<T>::operator[](const size_t idx) const noexcept
{
    return dynamic_table[idx];
}

/* Return reference to the element at index idx. */
template <typename T>
T& Vector<T>::operator[](const size_t idx) noexcept
{
    return dynamic_table[idx];
}

/* Returns a constant reference to the element at position pos.
   Throw out_of_range if pos >= size of thge container. */
template <typename T>
const T& Vector<T>::at(const size_t pos) const
{
    valid_idx(pos);
    return dynamic_table[pos];
}

/* Returns a reference to the element at position pos.
   Throw out_of_range if pos >= size of thge container. */
template <typename T>
T& Vector<T>::at(const size_t pos)
{
    valid_idx(pos);
    return dynamic_table[pos];
}

/* Returns pointer to the underlying array. */
template <typename T>
T* Vector<T>::data() const
{
    return dynamic_table;
}

template <typename T>
void Vector<T>::push_back(const T& push_node)
{
    if (size == capacity) {
        T* helper = new T[size];

        copy_helper(helper, dynamic_table, size);

        delete[] dynamic_table;

        dynamic_table = new T[size * 2 + 1];

        copy_helper(dynamic_table, helper, size);

        delete[] helper;

        capacity *= 2;
    }

    dynamic_table[size] = push_node;

    ++size;
}

/* Insert value before pos. Pos must be the pointer to
   one element of the vector. */
template <typename T>
void Vector<T>::insert(T* pos, const T& value)
{
    size_t idx = 0;
    for (auto i = begin(); i != pos; ++i) {
        ++idx;
    }

    if (size == capacity) {
        reserve(capacity * 2);
    }

    for (auto i = size; i != idx; --i) {
        dynamic_table[i] = dynamic_table[i - 1];
    }

    dynamic_table[idx] = value;

    ++size;
}

/* Insert count values before pos. Pos must be the pointer to
   one element of the vector. */
template <typename T>
void Vector<T>::insert(T* pos, size_t count, const T& value)
{
    if (count == 0) {
        return;
    }

    size_t idx = 0;
    for (auto i = begin(); i != pos; ++i) {
        ++idx;
    }

    for (size_t i = 0; i != count; ++i) {
        auto current_pos = begin();
        for (size_t i = 0; i != idx; ++i) {
            ++current_pos;
        }
        insert(current_pos, value);
    }
}

/* Insert values in range(beg, end) before pos. Pos, beg, end must be the
   pointers to one element of the vector. */
template <typename T>
void Vector<T>::insert(T* pos, T* beg, T* end)
{
    if (beg == end) {
        return;
    }

    size_t count = 0;
    T* tmp_beg = beg;
    while (tmp_beg != end) {
        ++tmp_beg;
        ++count;
    }

    T* insertable_arr = new T[count];
    for (size_t i = 0; i != count; ++i) {
        insertable_arr[i] = *beg;
        ++beg;
    }

    size_t idx = 0;
    for (auto i = begin(); i != pos; ++i) {
        ++idx;
    }

    for (int i = count - 1; i >= 0; --i) {
        auto current_pos = begin();
        for (size_t j = 0; j != idx; ++j) {
            ++current_pos;
        }
        insert(current_pos, insertable_arr[i]);
    }

    delete[] insertable_arr;
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

/* Removes node */
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

/* Erases all elements in the containter.
   After clear method size_() returns 0. */
template <typename T>
void Vector<T>::clear() noexcept
{
    // delete[] dynamic_table;

    // dynamic_table = new T[capacity];

    size = 0;
}

/* Copyes n elements from vector t2 to vector t1. */
template <typename T>
void Vector<T>::copy_helper(T*& t1, const T* const& t2, const size_t n)
{
    for (size_t x = 0; x != n; ++x) {
        t1[x] = t2[x];
    }
}

/* Validates the index of the vector. */
template <typename T>
void Vector<T>::valid_idx(const size_t idx, const std::string& msg) const
{
    if (idx >= size) {
        throw std::out_of_range(msg);
    }
}

template <typename TYPE>
std::ostream& operator<<(std::ostream& os, const Vector<TYPE>& v)
{
    for (size_t x = 0; x != v.size_(); ++x) {
        os << v[x] << ' ';
    }
    os << '\n';

    return os;
}

template <typename TYPE>
bool operator==(const Vector<TYPE>& v1, const Vector<TYPE>& v2)
{
    if (v1.size_() != v2.size_()) {
        return 0;
    }

    for (auto i1 = v1.begin(), i2 = v2.begin();
         i1 != v1.end() && i2 != v2.end();
         ++i1, ++i2) {
        if (*i1 != *i2) {
            return 0;
        }
    }

    return 1;
}
