#include <iostream>

#include "../../libvector/Vector.hpp"

int main()
{
    Vector<int> vec{1, 2, 3, 4, 5};
    Vector<int> cpy_vec;
    cpy_vec = vec;

    // std::cout << "size - " << cpy_vec.size_() << '\n';

    // for (size_t x = 0; x != cpy_vec.size_(); ++x) {
    // std::cout << cpy_vec[x] << ' ';
    // }

    // std::cout << cpy_vec;
}
