#include <iostream>

#include "../../libvector/Vector.hpp"

void remove()
{
    Vector<int> vec{1, 2, 3, 4, 5};

    // vec.remove(90);

    std::cout << vec << '\n' << (vec.end() == vec.remove(90)) << '\n';
}

void copy_constructor()
{
    Vector<int> vec{1, 2, 3, 4, 5};

    Vector<int> v_cpy(vec);

    std::cout << v_cpy;
}

int main()
{
    // remove();
    copy_constructor();
}
