#pragma once

#include "../liblist/list.hpp"

namespace stack {

template <typename T>
class stack : private list::list<T> {
    template <typename U>
    friend bool operator==(const stack<U>& lst1, const stack<U>& lst2);

public:
    stack() = default;
    stack(const stack<T>& s) = default;
    stack(stack<T>&& s) = default;
    stack& operator=(const stack<T>& s);
    stack& operator=(stack<T>&& s);
    ~stack() = default;

    stack(const std::initializer_list<T>& init_list);

    size_t size() const;
    bool is_empty() const;

    node<T>* begin() const;
    node<T>* end() const;

    const node<T>* cbegin() const;
    const node<T>* cend() const;

    void push(const T& x);
    void pop();

    bool contains(const T& value) const;
    size_t count(const T& v) const;

    void print_stack(std::ostream& os) const;
};

/* std::initializer_list constructor. */
template <typename T>
stack<T>::stack(const std::initializer_list<T>& init_list)
{
    for (const auto& c : init_list) {
        list::list<T>::push_front(c);
    }
}

/* Copy assignment operator. */
template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& s)
{
    this->clear();
    this->copy(s);

    return *this;
}

/* Move assingment operator. */
template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& s)
{
    return this->operator=(s);
}

/* Returns pointer to the first element in the stack. */
template <typename T>
node<T>* stack<T>::begin() const
{
    return list::list<T>::begin();
}

/* Returns pointer to the last element in the stack. */
template <typename T>
node<T>* stack<T>::end() const
{
    return list::list<T>::end();
}

/* Returns constant pointer to the first element in the stack. */
template <typename T>
const node<T>* stack<T>::cbegin() const
{
    return list::list<T>::cbegin();
}

/* Returns constant pointer to the last element in the stack. */
template <typename T>
const node<T>* stack<T>::cend() const
{
    return list::list<T>::cend();
}

/* Add element to the stack. */
template <typename T>
void stack<T>::push(const T& value)
{
    list::list<T>::push_front(value);
}

/* Removes element from stack. */
template <typename T>
void stack<T>::pop()
{
    list::list<T>::pop_front();
}

/* Checks if an element is in the stack.
 * Returns 1 if element's containing. */
template <typename T>
bool stack<T>::contains(const T& value) const
{
    return list::list<T>::contains(value);
}

/* Return number of elements with value v in stack. */
template <typename T>
size_t stack<T>::count(const T& v) const
{
    return list::list<T>::count(v);
}

/* Returns number of elements in the stack. */
template <typename T>
size_t stack<T>::size() const
{
    return this->list::list<T>::size();
}

/* Returns true if stack is empty. */
template <typename T>
bool stack<T>::is_empty() const
{
    return this->list::list<T>::is_empty();
}

// Just for testing.
template <typename T>
bool operator==(const stack<T>& lst1, const stack<T>& lst2)
{
    return list::operator==(lst1, lst2);
}

} // namespace stack
