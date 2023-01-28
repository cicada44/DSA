#include <iostream>

#include <vector>

#include <map>

template <typename K, typename V>
class Heap {
    template <typename KT, typename VT>
    friend std::ostream& operator<<(std::ostream& os, const Heap<KT, VT>& heap);

    template <typename KT, typename VT>
    friend std::ostream& print_recursive(std::ostream& os, size_t lvl);

public:
    Heap() = delete;

    explicit Heap(const size_t capa)
        : arr(new std::pair<K, V>[capa]), size(0), capacity(capa)
    {
    }

    ~Heap()
    {
        delete[] arr;
    }

    void add_list(const std::vector<std::pair<K, V>>& init_vec);

    std::pair<K, V> max() const noexcept;

    void insert(const K& key_ins, const V& val_ins);
    void increase_key(const K& key, const K& newkey);

    std::pair<K, V> extract_max();

private:
    size_t find_index(const K& key) const;
    void heapify_up(const size_t index);
    void heapify_down(const size_t index);

    std::pair<K, V>* const arr;
    size_t size;
    size_t capacity;
};

template <typename K, typename V>
size_t Heap<K, V>::find_index(const K& key) const
{
    size_t i = 0;
    for (; i < size; ++i) {
        if (key == arr[i].first) {
            break;
        }
    }
    return i;
}

template <typename K, typename V>
void Heap<K, V>::heapify_up(const size_t index)
{
    for (size_t i = index; i > 0 && arr[(i - 1) / 2] < arr[i];
         i = (i - 1) / 2) {
        std::cout << "swapped: " << arr[i].first << ' '
                  << arr[(i - 1) / 2].first << '\n';
        std::swap(arr[i], arr[(i - 1) / 2]);
    }
}

template <typename K, typename V>
void Heap<K, V>::heapify_down(const size_t index)
{
    for (size_t i = index; i < size && arr[i * 2 + 2] > arr[i]; i = i * 2 + 2) {
        std::swap(arr[i], arr[i * 2 + 2]);
    }
}

template <typename K, typename V>
void Heap<K, V>::add_list(const std::vector<std::pair<K, V>>& init_vec)
{
    for (const auto& c : init_vec) {
        insert(c.first, c.second);
        std::cout << *this << '\n' << '\n';
    }
}

template <typename K, typename V>
std::pair<K, V> Heap<K, V>::max() const noexcept
{
    return arr[0];
}

template <typename K, typename V>
void Heap<K, V>::insert(const K& key_ins, const V& val_ins)
{
    if (size >= capacity) {
        return;
    }

    arr[size] = {key_ins, val_ins};

    // std::cout << "insert index - " << size << '\n';

    heapify_up(size);

    ++size;
}

template <typename K, typename V>
void Heap<K, V>::increase_key(const K& key, const K& newkey)
{
    if (key > newkey) {
        return;
    }

    size_t index = find_index(key);

    arr[index].first = newkey;

    heapify_up(index);
}

template <typename K, typename V>
std::pair<K, V> Heap<K, V>::extract_max()
{
    if (size < 1) {
        return {};
    }

    std::pair<K, V> extracted_max = arr[0];

    arr[0] = arr[--size];

    heapify_down(0);

    return extracted_max;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Heap<K, V>& heap)
{
    os << "size - " << heap.size << '\n';
    for (size_t c = 0; c != heap.size; ++c) {
        os << heap.arr[c].first << ' ' << heap.arr[c].second << '\n';
    }
    return os;
}

// template <typename K, typename V>
// std::ostream& print_recursive(std::ostream& os, const Heap<K, V>& h, size_t
// lvl)
// {
//     return os;
// }
