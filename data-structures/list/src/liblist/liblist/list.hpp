#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <new>
#include <utility>

template <typename T>
struct node {
    node(const T& val) : value(val), next(nullptr)
    {
    }

    T value;
    node<T>* next;
};

namespace forward_list {

template <typename T>
class list {
    template <typename U>
    friend void print_list(std::ostream& os, list<U>& l);

    template <typename LT>
    friend bool operator==(const list<LT>& lst1, const list<LT>& lst2);

public:
    list() : head(nullptr), tail(nullptr), size_(0)
    {
    }

    list(const std::initializer_list<T>& init)
    {
        for (const auto& c : init) {
            push_back(c);
        }
        size_ = init.size();
    }

    list(const list<T>& l)
    {
        copy(l);
    }

    list(list<T>&& l)
    {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
    }

    list<T>& operator=(list<T>& l)
    {
        clear();
        copy(l);

        return *this;
    }

    list<T>& operator=(list<T>&& l)
    {
        std::swap(head, l.head);
        std::swap(tail, l.tail);

        return *this;
    }

    ~list()
    {
        clear();
    }

    bool is_empty() const
    {
        return (head == nullptr);
    }

    size_t size() const
    {
        return size_;
    }

    void push_back(const T& value)
    {
        node<T>* new_node = nullptr;

        try {
            new_node = new node<T>(value);
        } catch (std::bad_alloc&) {
        }

        if (is_empty()) {
            tail = head = new_node;
            ++size_;
            return;
        }
        tail->next = new_node;
        tail = new_node;
        ++size_;
    }

    void pop_back()
    {
        if (is_empty()) {
            return;
        }

        node<T>* prev = nullptr;
        node<T>* deleted = head;

        while (deleted->next != nullptr) {
            prev = deleted;
            deleted = deleted->next;
        }

        if (prev == nullptr) {
            delete head;
            head = nullptr;
            return;
        }

        tail = prev;
        tail->next = nullptr;

        delete deleted;
        --size_;
    }

    void push_front(const T& value)
    {
        node<T>* new_front_val = nullptr;

        try {
            new_front_val = new node(value);
        } catch (std::bad_alloc&) {
        }

        node<T>* temp_head = head;

        if (is_empty()) {
            head = tail = new_front_val;
            return;
        }

        head = new_front_val;
        head->next = temp_head;

        ++size_;
    }

    void pop_front()
    {
        if (is_empty()) {
            return;
        }

        node<T>* remove = head;
        head = head->next;
        delete remove;
        --size_;
    }

    void remove(const T& v)
    {
        if (is_empty()) {
            return;
        }

        if (head->value == v) {
            pop_front();
            return;
        }

        node<T>* temp_head = head;

        while (temp_head->next->value != v) {
            temp_head = temp_head->next;
        }

        if (temp_head->next == nullptr) {
            return;
        }

        node<T>* rem = temp_head->next;
        temp_head->next = temp_head->next->next;

        delete rem;

        --size_;
    }

    bool find(const T& v) const
    {
        if (is_empty()) {
            return false;
        }

        node<T>* find = head;

        while (find != nullptr) {
            if (find->value == v) {
                return true;
            }
            find = find->next;
        }

        return false;
    }

    void clear()
    {
        while (head) {
            delete std::exchange(head, head->next);
        }
        tail = nullptr;
    }

    void copy(const list<T>& l)
    {
        if (l.head != nullptr) {
            node<T>* iter = l.head;

            while (iter != nullptr) {
                push_back(iter->value);
                iter = iter->next;
            }

            size_ = l.size_;
        }
    }

    void merge(const list<T>& l)
    {
        node<T>* iter = l.head;

        while (iter) {
            push_back(iter->value);
            iter = iter->next;
        }
    }

    void merge(list<T>&& l)
    {
        std::swap(tail->next, l.head);
        std::swap(tail, l.tail);
    }

private:
    node<T>* head = nullptr;
    node<T>* tail = nullptr;
    size_t size_ = 0;
};

template <typename T>
void print_list(std::ostream& os, forward_list::list<T>& l)
{
    node<T>* head_iter = l.head;
    while (head_iter != nullptr) {
        os << head_iter->value;
        if (head_iter->next != nullptr) {
            os << " --> ";
        }
        head_iter = head_iter->next;
    }
}

// just for testing
template <typename T>
bool operator==(const list<T>& lst1, const list<T>& lst2)
{
    for (auto cntr1 = lst1.head, cntr2 = lst2.head;
         cntr1 != nullptr && cntr2 != nullptr;
         cntr1 = cntr1->next, cntr2 = cntr2->next) {
        if (cntr1->value != cntr2->value) {
            return false;
        }
    }
    return true;
}

};

#endif // __LIST_H__
