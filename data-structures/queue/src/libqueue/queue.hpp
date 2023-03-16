#pragma once

#include "../liblist/list.hpp"

namespace queue {

template <typename T>
class queue : private list::list<T> {
    template <typename U>
    friend bool operator==(const queue<U>& lst1, const queue<U>& lst2);

public:
    queue() = default;
    queue(const std::initializer_list<T>& init_list);
    queue(const queue<T>& q) = default;
    queue(queue<T>&& q) = default;
    queue& operator=(const queue<T>& q);
    queue& operator=(const queue<T>&& q);
    ~queue() = default;

    size_t size() const;
    bool is_empty() const;

    node<T>* begin() const;
    node<T>* end() const;

    const node<T>* cbegin() const;
    const node<T>* cend() const;

    void push(const T& x);
    void pop();

    bool contains(const T& v) const;
    size_t count(const T& v) const;

    node<T>& operator[](const size_t idx);
    const node<T>& operator[](const size_t idx) const;

    void clear();
    void copy(const queue<T>& l);

    void merge(const queue<T>& l);
    void merge(queue<T>&& l);

    void print_queue(std::ostream& os) const;
};

/* Copy assignment operator. */
template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& q)
{
    clear();
    copy(q);

    return *this;
}

/* Move assingment operator. */
template <typename T>
queue<T>& queue<T>::operator=(const queue<T>&& q)
{
    return this->operator=(q);
}

/* std::initializer_list constructor. */
template <typename T>
queue<T>::queue(const std::initializer_list<T>& init_list) : queue()
{
    for (const auto& c : init_list) {
        this->push_back(c);
    }
}

/* Add element to the end of the queue. */
template <typename T>
void queue<T>::push(const T& value)
{
    this->push_front(value);
}

/* Removes element from the end of the queue.
 * Returns void. */
template <typename T>
void queue<T>::pop()
{
    return this->pop_back();
}

/* Returns pointer to the first element in the queue. */
template <typename T>
node<T>* queue<T>::begin() const
{
    return this->list::list<T>::begin();
}

/* Returns pointer to the last element in the queue. */
template <typename T>
node<T>* queue<T>::end() const
{
    return this->list::list<T>::end();
}

/* Returns constant pointer to first element in the queue. */
template <typename T>
const node<T>* queue<T>::cbegin() const
{
    return this->list::list<T>::cbegin();
}

/* Returns constant pointer to first element in the queue. */
template <typename T>
const node<T>* queue<T>::cend() const
{
    return this->list::list<T>::cend();
}

/* Checks if an element is in the queue.
 * Returns 1 if element's containing. */
template <typename T>
bool queue<T>::contains(const T& v) const
{
    return this->list::list<T>::contains(v);
}

/* Return number of elements with value v in queue. */
template <typename T>
size_t queue<T>::count(const T& v) const
{
    return this->list::list<T>::count(v);
}

/* Returns number of elements in the queue. */
template <typename T>
size_t queue<T>::size() const
{
    return this->list::list<T>::size();
}

/* Returns true if queue is empty. */
template <typename T>
bool queue<T>::is_empty() const
{
    return this->list::list<T>::is_empty();
}

/* Return reference to element in queue[idx]. */
template <typename T>
node<T>& queue<T>::operator[](const size_t idx)
{
    return this->list::list<T>::operator[](idx);
}

/* Return const reference to element in queue[idx]. */
template <typename T>
const node<T>& queue<T>::operator[](const size_t idx) const
{
    return this->list::list<T>::operator[](idx);
}

/* Similar to ~queue(). */
template <typename T>
void queue<T>::clear()
{
    return this->list::list<T>::clear();
}

/* Copies l to the current queue. */
template <typename T>
void queue<T>::copy(const queue<T>& l)
{
    return this->list::list<T>::copy(l);
}

/* Add l to the end of the current queue. */
template <typename T>
void queue<T>::merge(const queue<T>& l)
{
    return this->list::list<T>::merge(l);
}

/* Add l to the end of the current queue. */
template <typename T>
void queue<T>::merge(queue<T>&& l)
{
    return this->list::list<T>::merge(l);
}

// Just for testing.
template <typename U>
bool operator==(const queue<U>& lst1, const queue<U>& lst2)
{
    return list::operator==(lst1, lst2);
}

} // namespace queue