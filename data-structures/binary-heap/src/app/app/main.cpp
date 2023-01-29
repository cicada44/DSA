#include <iostream>

#include "../../Heap/Heap.hpp"

#include <string>

using std::string;

using std::cout;

int main()
{
    Heap<int, string> heap(10);

    heap.add_list(
            {{7, "a"},
             {5, "b"},
             {4, "c"},
             {2, "d"},
             {0, "e"},
             {1, "f"},
             {3, "g"},
             {-1, "h"}});

    cout << heap;

    return 0;
}
