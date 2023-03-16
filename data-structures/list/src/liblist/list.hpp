#pragma once

#include <memory>
#include <new>
#include <utility>

#include <iostream>

template <typename T>
struct node {
    node() : next(nullptr) {}
    node(const T& val) : value(val), next(nullptr) {}

    T value;
    node<T>* next;
};

namespace list {

template <typename T, typename allocator = std::allocator<node<T>>>
class list {
    template <typename LT>
    friend bool operator==(const list<LT>& lst1, const list<LT>& lst2);

public:
    list();
    list(list<T>&& l);
    list<T>& operator=(list<T>& l);
    list<T>& operator=(list<T>&& l);
    virtual ~list();

    list(const std::initializer_list<T>& init);
    list(const list<T>& l);

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

    std::allocator<node<T>> allctr;

    inline node<T>* alloc_node(const T& value) {
        node<T>* newnode = allctr.allocate(1);
        new (newnode) node<T>(value);
        return newnode;
    }
};

/* Standard constructor. */
template <typename T, typename allocator>
list<T, allocator>::list() : head(nullptr), tail(nullptr), size_(0) {}

/* std::initializer_list constructor. */
template <typename T, typename allocator>
list<T, allocator>::list(const std::initializer_list<T>& init)
    : head(nullptr), tail(nullptr), size_(init.size()) {
    if (init.size() != 0) {
        node<T>* new_node = new node<T>(*init.begin());

        head = tail = new_node;

        for (auto c = init.begin() + 1; c != init.end(); ++c) {
            new_node = new node<T>(*c);
            tail->next = new_node;
            tail = new_node;
        }
    }
}

/* Copy constructor. */
template <typename T, typename allocator>
list<T, allocator>::list(const list<T>& l) {
    copy(l);
}

/* Move constructor. */
template <typename T, typename allocator>
list<T, allocator>::list(list<T>&& l) {
    std::swap(head, l.head);
    std::swap(tail, l.tail);
    std::swap(size_, l.size_);

    l.tail = l.head = nullptr;
    l.size_ = 0;
}

/* Copy assignment operator. */
template <typename T, typename allocator>
list<T>& list<T, allocator>::operator=(list<T>& l) {
    clear();
    copy(l);

    return *this;
}

/* Move assingment operator. */
template <typename T, typename allocator>
list<T>& list<T, allocator>::operator=(list<T>&& l) {
    std::swap(head, l.head);
    std::swap(tail, l.tail);
    std::swap(size_, l.size_);

    return *this;
}

/* Destructor. */
template <typename T, typename allocator>
list<T, allocator>::~list() {
    clear();
}

/* Returns true if list is empty. */
template <typename T, typename allocator>
bool list<T, allocator>::is_empty() const {
    return (size_ == 0);
}

/* Returns number of elements in the list. */
template <typename T, typename allocator>
size_t list<T, allocator>::size() const {
    return size_;
}

/* Returns pointer to the first element in the list. */
template <typename T, typename allocator>
node<T>* list<T, allocator>::begin() const {
    return head;
}

/* Returns pointer to the last element in the list. */
template <typename T, typename allocator>
node<T>* list<T, allocator>::end() const {
    return tail;
}

/* Returns constant pointer to the first element in the list. */
template <typename T, typename allocator>
const node<T>* list<T, allocator>::cbegin() const {
    return const_cast<const node<T>* const>(head);
}

/* Returns constant pointer to the last element in the list. */
template <typename T, typename allocator>
const node<T>* list<T, allocator>::cend() const {
    return const_cast<const node<T>* const>(tail);
}

/* Add element to the end of the list. */
template <typename T, typename allocator>
void list<T, allocator>::push_back(const T& value) {
    node<T>* new_node = alloc_node(value);

    if (is_empty()) [[unlikely]] {
        tail = head = new_node;
        ++size_;
        return;
    }

    tail->next = new_node;
    tail = new_node;
    ++size_;
}

/* Removes element from the end of the list.
 * Returns void. */
template <typename T, typename allocator>
void list<T, allocator>::pop_back() {
    if (is_empty()) {
        return;
    }

    node<T>* prev = nullptr;
    node<T>* deletable = head;

    while (deletable != nullptr) {
        prev = deletable;
        deletable = deletable->next;
    }

    if (prev == nullptr) {
        allctr.deallocate(head, sizeof(*head));
        head = nullptr;
        return;
    }

    tail = prev;
    tail->next = nullptr;

    allctr.deallocate(deletable, sizeof(*deletable));

    --size_;
}

/* Adds element to the front of the list.
 * Returns void. */
template <typename T, typename allocator>
void list<T, allocator>::push_front(const T& value) {
    node<T>* new_front_val = alloc_node(value);

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
 * Returns void. */
template <typename T, typename allocator>
void list<T, allocator>::pop_front() {
    if (is_empty()) {
        return;
    }

    node<T>* deletable = head;
    head = head->next;
    allctr.deallocate(deletable, sizeof(*deletable));

    --size_;
}

/* Removes the first encountered elements with value v.
 * Returns reference to the current list. */
template <typename T, typename allocator>
list<T>& list<T, allocator>::erase(const size_t idx) {
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

    node<T>* deletable = temp_head->next;
    temp_head->next = temp_head->next->next;

    allctr.deallocate(deletable, sizeof(*deletable));

    --size_;

    return *this;
}

/* Removes the first encountered elements with value v.
 * Returns reference to the current list. */
template <typename T, typename allocator>
list<T>& list<T, allocator>::erase_first(const T& v) {
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

    node<T>* deletable = temp_head->next;
    temp_head->next = temp_head->next->next;

    allctr.deallocate(deletable, sizeof(*deletable));

    --size_;

    return *this;
}

/* Removes the last encountered elements with value v.
 * Returns reference to the current list. */
template <typename T, typename allocator>
list<T>& list<T, allocator>::erase_last(const T& v) {
    if (is_empty()) {
        return *this;
    }

    if ((head->value == v && count(v) == 1)) {
        pop_front();
        return *this;
    }

    node<T>* temp_head = head;
    node<T>* nbeforedeletable = nullptr;

    while (temp_head->next != nullptr) {
        if (temp_head->next->value == v) {
            nbeforedeletable = temp_head;
        }
        temp_head = temp_head->next;
    }

    if (nbeforedeletable == nullptr) {
        return *this;
    }

    node<T>* deletable = nbeforedeletable->next;
    nbeforedeletable->next = nbeforedeletable->next->next;

    allctr.deallocate(deletable, sizeof(*deletable));

    --size_;

    return *this;
}

/* Removes all consecutive duplicate elements from the container.
 * Returns reference to the current list. */
template <typename T, typename allocator>
list<T>& list<T, allocator>::unique() {
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
 * Returns 1 if element's containing. */
template <typename T, typename allocator>
bool list<T, allocator>::contains(const T& v) const {
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
template <typename T, typename allocator>
size_t list<T, allocator>::count(const T& v) const {
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
template <typename T, typename allocator>
node<T>& list<T, allocator>::operator[](const size_t idx) {
    node<T>* temp_head = head;
    size_t beg = 0;

    while (beg != idx && temp_head != nullptr) {
        temp_head = temp_head->next;
        ++beg;
    }

    return *temp_head;
}

/* Return const reference to element in list[idx]. */
template <typename T, typename allocator>
const node<T>& list<T, allocator>::operator[](const size_t idx) const {
    node<T>* temp_head = head;
    size_t beg = 0;

    while (beg != idx && temp_head != nullptr) {
        temp_head = temp_head->next;
        ++beg;
    }

    return *temp_head;
}

/* Similar to ~list(). */
template <typename T, typename allocator>
void list<T, allocator>::clear() {
    while (head != nullptr) {
        node<T>* deletable = std::exchange(head, head->next);
        allctr.deallocate(deletable, sizeof(*deletable));
    }
}

/* Copies l to the current list. */
template <typename T, typename allocator>
void list<T, allocator>::copy(const list<T>& l) {
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
template <typename T, typename allocator>
void list<T, allocator>::merge(const list<T>& l) {
    node<T>* iter = l.head;

    while (iter) {
        push_back(iter->value);
        iter = iter->next;
    }
}

/* Add l to the end of the current list. */
template <typename T, typename allocator>
void list<T, allocator>::merge(list<T>&& l) {
    std::swap(tail->next, l.head);
    std::swap(tail, l.tail);
    size_ += l.size_;

    l.head = l.tail = nullptr;
    l.size_ = 0;
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
