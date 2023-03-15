#include <iostream>

#include <algorithm>

#include <string>

namespace mdt {

template <typename T>
class vector {
    template <typename Y>
    friend std::ostream& operator<<(std::ostream& os, const vector<Y>& v);

public:
    /* Constructors */
    vector();
    vector(const size_t capa);
    vector(const std::initializer_list<T>& init_list);
    vector(const T* const arr, const size_t s);

    /* RO5 */
    vector(const vector<T>& v_copy);
    vector(vector<T>&& v_copy);
    vector<T>& operator=(const vector<T>& vec);
    vector<T>& operator=(vector<T>&& vec);
    ~vector();

    /* Capacity */
    size_t size() const;
    size_t capacity() const;
    bool empty() const noexcept;
    void reserve(const size_t new_capa);
    void shrink_to_fit();

    /* Accessors to elements */
    T* begin() const;
    T* end() const;
    const T* cbegin() const;
    const T* cend() const;

    const T& operator[](size_t ind) const noexcept;
    T& operator[](size_t ind) noexcept;

    const T& at(const size_t pos) const;
    T& at(const size_t pos);
    T* data() const;
    size_t distance(const T* beg, const T* end) const;

    /* Modifiers */
    void push_back(const T& push_node);
    void insert(T* pos, const T& value);
    void insert(T* pos, const size_t count, const T& value);
    void insert(T* pos, const T* beg, const T* end);
    void insert(T* pos, const std::initializer_list<T>& il);

    T* remove_first(const T& node);
    T* remove(const T* node);
    T* remove(T* beg, const T* end);
    void clear() noexcept;
    void pop_back();

    /* Finders */
    bool contains_node(const T& node) const;
    T* find(const T& node) const;

private:
    T* dynamic_table;

    size_t size_;
    size_t capacity_;

    void copy_helper(T*& t1, const T* const& t2, const size_t n);
    void valid_idx(
            const size_t idx,
            const std::string& msg = std::string("index is out of size")) const;
    T* alloc_n_check(const size_t elems);
};

/* Standard constructor. */
template <typename T>
vector<T>::vector() : dynamic_table(nullptr), size_(0), capacity_(0)
{
}

/* Allocates memory of size capa to the actual vector. */
template <typename T>
vector<T>::vector(const size_t capa)
    : dynamic_table(new T[capa]), size_(0), capacity_(capa)
{
}

/* std::initializer_list constructor. */
template <typename T>
vector<T>::vector(const std::initializer_list<T>& init_list)
    : dynamic_table(new T[init_list.size()]),
      size_(init_list.size()),
      capacity_(init_list.size())
{
    size_t vec_indexator = 0;

    for (const auto& c : init_list) {
        dynamic_table[vec_indexator] = c;
        ++vec_indexator;
    }
}

/* Copies s elements from array arr to actual vector. */
template <typename T>
vector<T>::vector(const T* const arr, const size_t s) : vector(s)
{
}

/* Copy constructor. */
template <typename T>
vector<T>::vector(const vector<T>& v_copy)
{
    dynamic_table = new T[v_copy.capacity_];
    size_ = v_copy.size_;
    capacity_ = v_copy.capacity_;
    for (size_t i = 0; i != size_; ++i) {
        dynamic_table[i] = v_copy.dynamic_table[i];
    }
}

/* Move constructor. */
template <typename T>
vector<T>::vector(vector<T>&& v_copy)
    : size_(std::move(v_copy.size_)), capacity_(std::move(v_copy.capacity_))
{
    dynamic_table = std::move(v_copy.dynamic_table);

    v_copy.dynamic_table = nullptr;
    v_copy.size_ = 0;
    v_copy.capacity_ = 0;
}

/* Copy assignment operator. */
template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& vec)
{
    if (vec.dynamic_table == dynamic_table) {
        return *this;
    }

    clear();

    delete[] dynamic_table;
    dynamic_table = new T[vec.size_];

    size_ = vec.size_;

    copy_helper(dynamic_table, vec.dynamic_table, vec.size_);

    return *this;
}

/* Move assignment operator. */
template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& vec)
{
    if (vec.dynamic_table == dynamic_table) {
        return *this;
    }

    std::swap(dynamic_table, vec.dynamic_table);
    std::swap(size_, vec.size_);
    std::swap(capacity_, vec.capacity_);

    vec.dynamic_table = nullptr;
    vec.size_ = 0;
    vec.capacity_ = 0;

    return *this;
}

/* Destructor. */
template <typename T>
vector<T>::~vector()
{
    delete[] dynamic_table;
}

/* Function-helper. Allocates memory and throws the exception if std::bad_alloc
 * happenes. Returns pointer to new allocated memory. */
template <typename T>
T* vector<T>::alloc_n_check(const size_t elems)
{
    T* pointer = nullptr;
    try {
        pointer = new T[elems];
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return pointer;
}

/* Returns size of actual vector. */
template <typename T>
size_t vector<T>::size() const
{
    return size_;
}

/* Returns capacity of actual vector. */
template <typename T>
size_t vector<T>::capacity() const
{
    return capacity_;
}

/* Returns 1 if vector is empty (size() == 0), 0 - if doesn't. */
template <typename T>
bool vector<T>::empty() const noexcept
{
    return (size_ == 0);
}

/* Reserves memory for vector if new_capa > capa. */
template <typename T>
void vector<T>::reserve(const size_t new_capa)
{
    if (new_capa > capacity_) [[likely]] {
        T* temp = alloc_n_check(size_);

        copy_helper(temp, dynamic_table, size_);

        delete[] dynamic_table;

        dynamic_table = alloc_n_check(new_capa);

        copy_helper(dynamic_table, temp, size_);
        delete[] temp;

        capacity_ = new_capa;
    }
}

/* Requests the removal of unused capacity. */
template <typename T>
void vector<T>::shrink_to_fit()
{
    T* temp = alloc_n_check(size_);
    copy_helper(temp, dynamic_table, size_);
    delete[] dynamic_table;

    dynamic_table = alloc_n_check(size_);
    copy_helper(dynamic_table, temp, size_);
    delete[] temp;

    capacity_ = size_;
}

/* Returns pointer to begin of the actual vector. */
template <typename T>
T* vector<T>::begin() const
{
    return dynamic_table;
}

/* Returns pointer to end of the actual vector. */
template <typename T>
T* vector<T>::end() const
{
    return (dynamic_table + size_);
}

/* Returns constant pointer to begin of the actual vector. */
template <typename T>
const T* vector<T>::cbegin() const
{
    return dynamic_table;
}

/* Returns constant pointer to end of the actual vector. */
template <typename T>
const T* vector<T>::cend() const
{
    return (dynamic_table + size);
}

/* Return constant reference to the element at index idx. */
template <typename T>
const T& vector<T>::operator[](const size_t idx) const noexcept
{
    return dynamic_table[idx];
}

/* Return reference to the element at index idx. */
template <typename T>
T& vector<T>::operator[](const size_t idx) noexcept
{
    return dynamic_table[idx];
}

/* Returns a constant reference to the element at position pos.
 * Throw out_of_range if pos >= size of the actual container. */
template <typename T>
const T& vector<T>::at(const size_t pos) const
{
    valid_idx(pos);
    return dynamic_table[pos];
}

/* Returns a reference to the element at position pos.
 * Throw out_of_range if pos >= size of the actual container. */
template <typename T>
T& vector<T>::at(const size_t pos)
{
    valid_idx(pos);
    return dynamic_table[pos];
}

/* Returns count of elements between beg and end. Beg and end must be the
 * pointers to elements in the actual container */
template <typename T>
size_t vector<T>::distance(const T* beg, const T* end) const
{
    size_t dist = 0;

    while (beg++ != end && ++dist)
        ;

    return dist;
}

/* Returns pointer to the containing array. */
template <typename T>
T* vector<T>::data() const
{
    return dynamic_table;
}

/* Inserts element to the end of the container. */
template <typename T>
void vector<T>::push_back(const T& push_node)
{
    if (size_ == capacity_) [[unlikely]] {
        T* helper = alloc_n_check(size_);
        copy_helper(helper, dynamic_table, size_);
        delete[] dynamic_table;

        dynamic_table = alloc_n_check(size_ * 2 + 1);
        copy_helper(dynamic_table, helper, size_);
        delete[] helper;

        capacity_ *= 2;
    }

    dynamic_table[size_] = push_node;

    ++size_;
}

/* Insert value before pos. Pos must be the pointer to
 * one element of the vector. */
template <typename T>
void vector<T>::insert(T* pos, const T& value)
{
    size_t idx = 0;
    for (auto i = begin(); i != pos; ++i) {
        ++idx;
    }

    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }

    for (auto i = size_; i != idx; --i) {
        dynamic_table[i] = dynamic_table[i - 1];
    }

    dynamic_table[idx] = value;

    ++size_;
}

/* Insert count values before pos. Pos must be the pointer to
 * one element of the vector. */
template <typename T>
void vector<T>::insert(T* pos, const size_t count, const T& value)
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

/* Insert values in range [beg, end) before pos. Pos must be the
 * pointer to the element of the vector. */
template <typename T>
void vector<T>::insert(T* pos, const T* beg, const T* end)
{
    if (beg == end) {
        return;
    }

    size_t count = 0;
    const T* tmp_beg = beg;
    while (tmp_beg != end) {
        ++tmp_beg;
        ++count;
    }

    T* insertable_arr = alloc_n_check(count);
    for (size_t i = 0; i != count; ++i) {
        insertable_arr[i] = *beg;
        ++beg;
    }

    size_t idx = 0;
    for (auto i = cbegin(); i != pos; ++i) {
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

/* Insert values in il before pos. Pos must be the
 * pointer to the element of the vector. */
template <typename T>
void vector<T>::insert(T* pos, const std::initializer_list<T>& il)
{
    size_t idx = 0;
    for (auto i = begin(); i != pos; ++i) {
        ++idx;
    }

    for (auto i = il.end() - 1; i >= il.begin(); --i) {
        auto current_pos = begin();
        for (size_t i = 0; i != idx; ++i) {
            ++current_pos;
        }
        insert(current_pos, *i);
    }
}

/* Removes the last element from the vector. */
template <typename T>
void vector<T>::pop_back()
{
    --size_; // :)
}

/* Returns 1 if node is in the vector, 0 - if not. */
template <typename T>
bool vector<T>::contains_node(const T& node) const
{
    for (size_t x = 0; x != size_; ++x) {
        if (node == dynamic_table[x]) {
            return 1;
        }
    }

    return 0;
}

/* Finds element node in the vector.
 * Returns pointer to element. If element isn't in containter return
 * end(). */
template <typename T>
T* vector<T>::find(const T& node) const
{
    for (size_t x = 0; x != size_; ++x) {
        if (dynamic_table[x] == node) {
            return &dynamic_table[x];
        }
    }

    return end();
}

/* Removes first found element with value val.
 * Returns end() if there is not element with value val.
 * Otherwise - returns pointer to the element next to deleted. */
template <typename T>
T* vector<T>::remove_first(const T& val)
{
    T* elem = find(val);

    if (elem == end()) {
        return end();
    }

    for (auto i = elem; i != end() - 1; ++i) {
        std::swap(*i, *(i + 1));
    }

    --size_;

    return ++elem;
}

/* Removes node from container, node must be the pointer to the element in
 * container. Returns end() if there is not element with value val.
 * Otherwise - returns pointer to the element next to deleted. */
template <typename T>
T* vector<T>::remove(const T* node)
{
    T* deletable = begin();

    while (deletable != node) {
        ++deletable;
    }

    if (deletable == end()) {
        return end();
    }

    for (auto i = deletable; i != end() - 1; ++i) {
        std::swap(*i, *(i + 1));
    }

    --size_;

    return ++deletable;
}

/* Removes elements in range [beg, end). Beg and range must be the pointers to
 * the actual container. Returns end() if there is not element with value val.
 * Otherwise - returns pointer to the element next to last deleted. */
template <typename T>
T* vector<T>::remove(T* beg, const T* end)
{
    T* deletable = beg;

    while (deletable != end) {
        remove(beg);
        ++deletable;
    }

    return ++deletable;
}

/* Erases (literally???) all elements in the containter.
 * After clear method size() returns 0. */
template <typename T>
void vector<T>::clear() noexcept
{
    size_ = 0;
}

/* Copyes n elements from vector t2 to vector t1. */
template <typename T>
void vector<T>::copy_helper(T*& t1, const T* const& t2, const size_t n)
{
    for (size_t x = 0; x != n; ++x) {
        t1[x] = t2[x];
    }
}

/* Validates the index of the vector. If idx >= size -- throws the exception
 * std::out_of_range. */
template <typename T>
void vector<T>::valid_idx(const size_t idx, const std::string& msg) const
{
    if (idx >= size_) {
        throw std::out_of_range(msg);
    }
}

/* Prints the vector to os. */
template <typename Y>
std::ostream& operator<<(std::ostream& os, const vector<Y>& v)
{
    for (size_t x = 0; x != v.size(); ++x) {
        os << v[x] << ' ';
    }
    os << '\n';

    return os;
}

/* Returns true if all elements in vector are the same. Otherwise returns false.
 */
template <typename TYPE>
bool operator==(const vector<TYPE>& v1, const vector<TYPE>& v2)
{
    if (v1.size() != v2.size()) {
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

} // namespace mdt
