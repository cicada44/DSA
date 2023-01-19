#ifndef __STACK_H__
#define __STACK_H__

#include "../liblist/list.hpp"

template <typename T>
class stack : private list<T> {
public:
    stack() : list<T>()
    {
    }

    stack(const std::initializer_list<T>& init_list);

    size_t size() const;

    bool is_empty() const;

    void push(const T& x);

    void pop();

    bool find(const T& value);

    void print_stack(std::ostream& os) const;

private:
};

template <typename T>
stack<T>::stack(const std::initializer_list<T>& init_list)
{
    for (const auto& c : init_list) {
        this->list<T>::push_front(c);
    }
}

template <typename T>
void stack<T>::push(const T& value)
{
    this->push_front(value);
}

template <typename T>
void stack<T>::pop()
{
    return this->list<T>::pop_front();
}

template <typename T>
bool stack<T>::find(const T& value)
{
    return this->list<T>::find(value);
}

template <typename T>
size_t stack<T>::size() const
{
    return this->list<T>::size();
}

template <typename T>
bool stack<T>::is_empty() const
{
    return this->list<T>::is_empty();
}

template <typename T>
void stack<T>::print_stack(std::ostream& os) const
{
    this->list<T>::print_list(os);
}

#endif // __STACK_H__