#include <iostream>

#include <vector>

#include <map>

template <typename K, typename V>
class Heap {
    template <typename KT, typename VT>
    friend std::ostream& operator<<(std::ostream& os, const Heap<KT, VT>& heap);

    template <typename KT, typename VT>
    friend bool operator==(const Heap<KT, VT>& h1, const Heap<KT, VT>& h2);

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
    void heapify_down(size_t index);

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
        std::swap(arr[i], arr[(i - 1) / 2]);
    }
}

template <typename K, typename V>
void Heap<K, V>::heapify_down(size_t index)
{
    while (1) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;
        if (left <= size && arr[left].first > arr[largest].first)
            largest = left;
        if (right <= size && arr[right].first > arr[largest].first)
            largest = right;
        if (largest == index)
            break;
        std::swap(arr[index], arr[largest]);
        index = largest;
    }
}

template <typename K, typename V>
void Heap<K, V>::add_list(const std::vector<std::pair<K, V>>& init_vec)
{
    for (const auto& c : init_vec) {
        insert(c.first, c.second);
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

    arr[0] = arr[size - 1];

    --size;

    heapify_down(0);

    return extracted_max;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Heap<K, V>& heap)
{
    for (size_t c = 0; c != heap.size; ++c) {
        os << heap.arr[c].first << ' ' << heap.arr[c].second << '\n';
    }
    return os;
}

template <typename KT, typename VT>
bool operator==(const Heap<KT, VT>& h1, const Heap<KT, VT>& h2)
{
    if (h1.size != h2.size) {
        return 0;
    }
    for (size_t c1 = 0, c2 = 0; c1 < h1.size && c2 < h2.size; ++c1, ++c2) {
        if (h1.arr[c1] != h2.arr[c2]) {
            return 0;
        }
    }

    return 1;
}
