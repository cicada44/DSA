#ifndef __queue_H__
#define __queue_H__

#include "../liblist/list.hpp"

template <typename T>
class queue : private list<T> {
public:
    queue() = default;

    queue(const std::initializer_list<T>& init_list);

    size_t size() const;

    bool is_empty() const;

    void push(const T& x);

    void pop();

    bool find(const T& value);

    void print_queue(std::ostream& os) const;

private:
};

template <typename T>
queue<T>::queue(const std::initializer_list<T>& init_list)
{
    for (const auto& c : init_list) {
        this->list<T>::push_back(c);
    }
}

template <typename T>
void queue<T>::push(const T& value)
{
    this->push_front(value);
}

template <typename T>
void queue<T>::pop()
{
    return this->list<T>::pop_back();
}

template <typename T>
bool queue<T>::find(const T& value)
{
    return this->list<T>::find(value);
}

template <typename T>
size_t queue<T>::size() const
{
    return this->list<T>::size();
}

template <typename T>
bool queue<T>::is_empty() const
{
    return this->list<T>::is_empty();
}

template <typename T>
void queue<T>::print_queue(std::ostream& os) const
{
    this->list<T>::print_list(os);
}

#endif // __queue_H__