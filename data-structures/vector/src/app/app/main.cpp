#include <iostream>

#include "../../libvector/Vector.hpp"

int main()
{
    Vector<int> vec{1, 2, 3, 4, 5};

    std::cout << "size - " << vec.size_() << '\n';
    std::cout << "capacity - " << vec.capacity_() << '\n';
    std::cout << vec;

    vec.push_back(6);
    std::cout << vec;
    std::cout << "size - " << vec.size_() << '\n';
    std::cout << "capacity - " << vec.capacity_() << '\n';
}