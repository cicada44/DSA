#pragma once

#include <utility>

#include <new>

#include <iostream>

template <typename T>
struct node {
    node(const T& val) : value(val), next(nullptr) {}

    T value;
    node<T>* next;
};

namespace forward_list {

template <typename T>
class list {
    template <typename U>
    friend std::ostream& print_list(std::ostream& os, list<U>& l);

    template <typename LT>
    friend bool operator==(const list<LT>& lst1, const list<LT>& lst2);

public:
    list() : head(nullptr), tail(nullptr), size_(0) {}

    list(const std::initializer_list<T>& init) {
        for (const auto& c : init) {
            push_back(c);
        }
        size_ = init.size();
    }

    list(const list<T>& l) { copy(l); }

    list(list<T>&& l) {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
    }

    list<T>& operator=(list<T>& l) {
        clear();
        copy(l);

        return *this;
    }

    list<T>& operator=(list<T>&& l) {
        std::swap(head, l.head);
        std::swap(tail, l.tail);

        return *this;
    }

    ~list() { clear(); }

    bool is_empty() const;
    size_t size() const;

    node<T>* begin() const;
    node<T>* end() const;

    void push_back(const T& value);
    void push_front(const T& value);

    void pop_back();
    void pop_front();
    void remove_first(const T& v);

    bool contains(const T& v) const;

    void clear();
    void copy(const list<T>& l);

    void merge(const list<T>& l);
    void merge(list<T>&& l);

private:
    node<T>* head = nullptr;
    node<T>* tail = nullptr;
    size_t size_ = 0;
};

// Returns true if list is empty.
template <typename T>
bool list<T>::is_empty() const {
    return (head == nullptr);
}

// Returns number of elements in the list.
template <typename T>
size_t list<T>::size() const {
    return size_;
}

// Returns pointer to first element in the list.
template <typename T>
node<T>* list<T>::begin() const {
    return head;
}

// Returns pointer to first element in the list.
template <typename T>
node<T>* list<T>::end() const {
    return tail;
}

// Add element to the end of the list.
template <typename T>
void list<T>::push_back(const T& value) {
    node<T>* new_node = nullptr;

    try {
        new_node = new node<T>(value);
    } catch (const std::bad_alloc& ba) {
        std::cout << ba.what() << '\n';
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

// Removes element from the end of the list.
// Returns void.
template <typename T>
void list<T>::pop_back() {
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

// Adds element to the front of the list.
// Returns void.
template <typename T>
void list<T>::push_front(const T& value) {
    node<T>* new_front_val = nullptr;

    try {
        new_front_val = new node(value);
    } catch (std::bad_alloc& ba) {
        std::cout << ba.what() << '\n';
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

// Removes element from the front of the list.
// Returns void.
template <typename T>
void list<T>::pop_front() {
    if (is_empty()) {
        return;
    }

    node<T>* remove = head;
    head = head->next;
    delete remove;
    --size_;
}

// Removes the first encountered elements with value v.
// Returns void.
template <typename T>
void list<T>::remove_first(const T& v) {
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

// Checks if an element is in the list.
// Returns 1 if element's containing.
template <typename T>
bool list<T>::contains(const T& v) const {
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

// Similar to ~list().
template <typename T>
void list<T>::clear() {
    while (head) {
        delete std::exchange(head, head->next);
    }
    tail = nullptr;
}

// Copies l to the actual list.
template <typename T>
void list<T>::copy(const list<T>& l) {
    if (l.head != nullptr) {
        node<T>* iter = l.head;

        while (iter != nullptr) {
            push_back(iter->value);
            iter = iter->next;
        }

        size_ = l.size_;
    }
}

// Add l to the end of the actual list.
template <typename T>
void list<T>::merge(const list<T>& l) {
    node<T>* iter = l.head;

    while (iter) {
        push_back(iter->value);
        iter = iter->next;
    }
}

// Add l to the end of the actual list.
template <typename T>
void list<T>::merge(list<T>&& l) {
    std::swap(tail->next, l.head);
    std::swap(tail, l.tail);
}

template <typename T>
std::ostream& print_list(std::ostream& os, forward_list::list<T>& l) {
    node<T>* head_iter = l.head;
    while (head_iter != nullptr) {
        os << head_iter->value;
        if (head_iter->next != nullptr) {
            os << " --> ";
        }
        head_iter = head_iter->next;
    }

    return os;
}

// Just for testing.
template <typename T>
bool operator==(const list<T>& lst1, const list<T>& lst2) {
    for (auto cntr1 = lst1.head, cntr2 = lst2.head;
         cntr1 != nullptr && cntr2 != nullptr;
         cntr1 = cntr1->next, cntr2 = cntr2->next) {
        if (cntr1->value != cntr2->value) {
            return false;
        }
    }
    return true;
}

};    // namespace forward_list
