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

namespace list {

template <typename T>
class list {
    template <typename U>
    friend std::ostream& print_list(std::ostream& os, list<U>& l);

    template <typename LT>
    friend bool operator==(const list<LT>& lst1, const list<LT>& lst2);

public:
    list() : head(nullptr), tail(nullptr), size_(0) {}

    inline list(const std::initializer_list<T>& init) {
        for (const auto& c : init) {
            push_back(c);
        }
        size_ = init.size();
    }

    list(const list<T>& l) { copy(l); }

    list(list<T>&& l) {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(size_, l.size_);
    }

    list<T>& operator=(list<T>& l) {
        clear();
        copy(l);

        return *this;
    }

    list<T>& operator=(list<T>&& l) {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(size_, l.size_);

        return *this;
    }

    ~list() { clear(); }

    bool is_empty() const;
    size_t size() const;

    node<T>* begin() const;
    node<T>* end() const;

    const node<T>* cbegin() const;
    const node<T>* cend() const;

    void push_back(const T& value);
    void push_front(const T& value);

    void pop_back();
    void pop_front();

    list<T>& erase(const size_t idx);
    list<T>& erase_first(const T& v);
    list<T>& erase_last(const T& v);

    list<T>& unique();

    bool contains(const T& v) const;
    size_t count(const T& v) const;

    node<T>& operator[](const size_t idx);
    const node<T>& operator[](const size_t idx) const;

    void clear();
    void copy(const list<T>& l);

    void merge(const list<T>& l);
    void merge(list<T>&& l);

private:
    node<T>* head = nullptr;
    node<T>* tail = nullptr;
    size_t size_ = 0;
};

/* Returns true if list is empty. */
template <typename T>
bool list<T>::is_empty() const {
    return (head == nullptr);
}

/* Returns number of elements in the list. */
template <typename T>
size_t list<T>::size() const {
    return size_;
}

/* Returns pointer to first element in the list. */
template <typename T>
node<T>* list<T>::begin() const {
    return head;
}

/* Returns pointer to first element in the list. */
template <typename T>
node<T>* list<T>::end() const {
    return tail;
}

/* Returns constant pointer on first element in the list. */
template <typename T>
const node<T>* list<T>::cbegin() const {
    return const_cast<const node<T>* const>(head);
}

/* Returns constant pointer on first element in the list. */
template <typename T>
const node<T>* list<T>::cend() const {
    return const_cast<const node<T>* const>(tail);
}

/* Add element to the end of the list. */
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

/* Removes element from the end of the list.
   Returns void. */
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

/* Adds element to the front of the list.
   Returns void. */
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
        ++size_;
        head = tail = new_front_val;
        return;
    }

    head = new_front_val;
    head->next = temp_head;

    ++size_;
}

/* Removes element from the front of the list.
   Returns void. */
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

/* Removes the first encountered elements with value v.
   Returns reference to the current list. */
template <typename T>
list<T>& list<T>::erase(const size_t idx) {
    if (is_empty()) {
        return *this;
    }

    if (idx == 0) {
        pop_front();
        return *this;
    }

    node<T>* temp_head = &(*this)[idx - 1];

    if (temp_head->next == nullptr) {
        return *this;
    }

    node<T>* rem = temp_head->next;
    temp_head->next = temp_head->next->next;

    delete rem;

    --size_;

    return *this;
}

/* Removes the first encountered elements with value v.
   Returns reference to the current list. */
template <typename T>
list<T>& list<T>::erase_first(const T& v) {
    if (is_empty()) {
        return *this;
    }

    if (head->value == v) {
        pop_front();
        return *this;
    }

    node<T>* temp_head = head;

    while (temp_head->next->value != v) {
        temp_head = temp_head->next;
    }

    if (temp_head->next == nullptr) {
        return *this;
    }

    node<T>* rem = temp_head->next;
    temp_head->next = temp_head->next->next;

    delete rem;

    --size_;

    return *this;
}

/* Removes the last encountered elements with value v.
   Returns reference to the current list. */
template <typename T>
list<T>& list<T>::erase_last(const T& v) {
    if (is_empty()) {
        return *this;
    }

    if ((head->value == v && count(v) == 1)) {
        pop_front();
        return *this;
    }

    node<T>* temp_head = head;
    node<T>* nbeforedeleted = nullptr;

    while (temp_head->next != nullptr) {
        if (temp_head->next->value == v) {
            nbeforedeleted = temp_head;
        }
        temp_head = temp_head->next;
    }

    if (nbeforedeleted == nullptr) {
        return *this;
    }

    node<T>* rem = nbeforedeleted->next;
    nbeforedeleted->next = nbeforedeleted->next->next;

    delete rem;

    --size_;

    return *this;
}

/* Removes all consecutive duplicate elements from the container.
   Returns reference to the current list. */
template <typename T>
list<T>& list<T>::unique() {
    node<T>* temp_head = head;

    size_t idx_counter = 0;

    while (temp_head->next != nullptr) {
        if (temp_head->value == temp_head->next->value) {
            erase(idx_counter + 1);
            continue;
        }
        ++idx_counter;
        temp_head = temp_head->next;
    }

    return *this;
}

/* Checks if an element is in the list.
   Returns 1 if element's containing. */
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

/* Return number of elements with value v in list. */
template <typename T>
size_t list<T>::count(const T& v) const {
    size_t count = 0;

    node<T>* temp_head = head;

    while (temp_head != nullptr) {
        if (temp_head->value == v) {
            ++count;
        }
        temp_head = temp_head->next;
    }

    return count;
}

/* Return reference to element in list[idx]. */
template <typename T>
node<T>& list<T>::operator[](const size_t idx) {
    node<T>* temp_head = head;
    size_t beg = 0;

    while (beg != idx && temp_head != nullptr) {
        temp_head = temp_head->next;
        ++beg;
    }

    return *temp_head;
}

/* Return const reference to element in list[idx]. */
template <typename T>
const node<T>& list<T>::operator[](const size_t idx) const {
    node<T>* temp_head = head;
    size_t beg = 0;

    while (beg != idx && temp_head != nullptr) {
        temp_head = temp_head->next;
        ++beg;
    }

    return *temp_head;
}

/* Similar to ~list(). */
template <typename T>
void list<T>::clear() {
    while (head) {
        delete std::exchange(head, head->next);
    }
    tail = nullptr;
}

/* Copies l to the current list. */
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

/* Add l to the end of the current list. */
template <typename T>
void list<T>::merge(const list<T>& l) {
    node<T>* iter = l.head;

    while (iter) {
        push_back(iter->value);
        iter = iter->next;
    }
}

/* Add l to the end of the current list. */
template <typename T>
void list<T>::merge(list<T>&& l) {
    std::swap(tail->next, l.head);
    std::swap(tail, l.tail);
    size_ += l.size_;
}

template <typename T>
std::ostream& print_list(std::ostream& os, list<T>& l) {
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
    if (lst1.size() != lst2.size()) {
        return false;
    }

    for (auto cntr1 = lst1.head, cntr2 = lst2.head;
         cntr1 != nullptr && cntr2 != nullptr;
         cntr1 = cntr1->next, cntr2 = cntr2->next) {
        if (cntr1->value != cntr2->value) {
            return false;
        }
    }

    return true;
}

};    // namespace list
