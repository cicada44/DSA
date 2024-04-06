#pragma once

#include <cassert>
#include <initializer_list>
#include <memory>
#include <utility>

#include <iostream>

namespace dll {

template <typename T>
class list {
private:
    struct node {
        node* right_ = nullptr;
        node* left_ = nullptr;
        T item_;
        node(T item, node* right = nullptr, node* left = nullptr) noexcept
            : right_(right), left_(left), item_{std::move(item)} {}
    };

    node* head_ = nullptr;
    node* tail_ = nullptr;
    node* end_node = nullptr;

public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    template <typename U, bool R = false>
    class list_iter {
    private:
        friend class list;

        explicit list_iter(node* n) noexcept : current_(n) {}

    public:
        using value_type = list::value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::bidirectional_iterator_tag;

        reference operator*() const noexcept {
            assert(current_ != nullptr);
            return current_->item_;
        }

        list_iter& operator++() noexcept {
            assert(current_ != nullptr);
            (R == false) ? current_ = current_->right_ : current_ = current_->left_;
            return *this;
        }

        list_iter& operator--() noexcept {
            assert(current_ != nullptr);
            (R == false) ? current_ = current_->left_ : current_ = current_->right_;
            return *this;
        }

        list_iter operator++(int) noexcept {
            assert(current_ != nullptr);
            auto prev = *this;
            (R == false) ? current_ = current_->right_ : current_ = current_->left_;
            return prev;
        }

        list_iter operator--(int) noexcept {
            assert(current_ != nullptr);
            auto next = *this;
            (R == false) ? current_ = current_->left_ : current_ = current_->right_;
            return next;
        }

        bool operator==(list_iter iter) noexcept { return iter.current_ == current_; }

        bool operator!=(list_iter iter) noexcept { return !(*this == iter); }

    protected:
        const node* Get() const noexcept { return current_; }
        node* current_;
    };

    using base_iterator = list_iter<T>;
    using const_iterator = list_iter<const T>;
    using reverse_iterator = list_iter<T, true>;
    using const_reverse_iterator = list_iter<const T, true>;

    list() = default;
    list(const_iterator begin, const_iterator end) {
        for (auto i = begin; i != end; ++i) push_back(*i);
    }
    list(const std::initializer_list<T> il) {
        for (const auto& item : il) push_back(item);
    }
    list(const list& l) : list(l.cbegin(), l.cend()) {}
    list& operator=(const list& l) {
        list copy(l);
        std::swap(head_, l.head_);
        std::swap(tail_, l.tail_);
        return *this;
    }
    list(list&& l) {
        std::swap(head_, l.head_);
        std::swap(tail_, l.tail_);
        delete end_node;
        std::swap(end_node, l.end_node);
        l.head_ = l.tail_ = nullptr;
    }
    list& operator=(list&& l) {
        clear();
        for (const auto& item : l) push_back(item->item_);
        l.head_ = l.tail_ = nullptr;
        return *this;
    }
    ~list() { clear(); }

    T& front() const { return head_->item_; }
    T& back() const { return tail_->item_; }
    bool empty() const { return tail_ == nullptr; }
    size_type size() const {
        size_type s = 0;
        for (auto i = const_iterator{head_}; i != const_iterator{tail_->right_}; ++s, ++i)
            ;
        return s;
    }
    void clear() {
        // delete end_node;
        // end_node = nullptr;
        while (head_) delete std::exchange(head_, head_->right_);
        tail_ = nullptr;
    }

    void push_back(value_type item) {
        auto newnode = new node{std::move(item)};
        if (tail_ != nullptr) {
            tail_->right_ = newnode;
            newnode->left_ = tail_;
            tail_ = newnode;
        } else {
            head_ = tail_ = newnode;
        }
        if (end_node == nullptr) end_node = new node(0);
        tail_->right_ = end_node;
        end_node->left_ = tail_;
    }

    void push_front(value_type item) {
        auto newnode = new node{std::move(item)};
        if (tail_ != nullptr) {
            head_->left_ = newnode;
            newnode->right_ = head_;
            head_ = newnode;
        } else {
            head_ = tail_ = newnode;
            if (end_node == nullptr) end_node = new node(0);
            tail_->right_ = end_node;
            end_node->left_ = tail_;
        }
    }

    const_iterator cbegin() const { return const_iterator{head_}; }
    const_iterator cend() const { return const_iterator{tail_->right_}; }
    base_iterator begin() const { return base_iterator{head_}; }
    base_iterator end() const { return base_iterator{tail_->right_}; }
    reverse_iterator rbegin() const { return reverse_iterator{tail_}; }
    reverse_iterator rend() const { return reverse_iterator{head_->left_}; }
    const_reverse_iterator crbegin() const { return const_reverse_iterator{tail_}; }
    const_reverse_iterator crend() const { return const_reverse_iterator{head_->left_}; }
};

}  // namespace dll
