#include <iostream>

#include "../../Heap/Heap.hpp"

#include <string>

using std::string;

using std::cout;

int main()
{
    Heap<int, string> heap(10);

    heap.add_list({{1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {5, "e"}});

    cout << heap;

    heap.increase_key(2, 8);

    cout << heap;

    heap.extract_max();

    cout << heap;

    return 0;
}
