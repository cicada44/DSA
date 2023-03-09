#include <iostream>

#include "../../libvector/Vector.hpp"

void remove()
{
    Vector<int> vec{1, 2, 3, 4, 5};

    vec.remove(90);

    std::cout << vec << '\n' << (vec.end() == vec.remove(90)) << '\n';
}

void copy_constructor()
{
    Vector<int> vec{1, 2, 3, 4, 5};

    Vector<int> v_cpy(vec);

    std::cout << v_cpy;
}

void iters()
{
    Vector<int> vec{1, 2, 3, 4, 5};

    Vector<int> v_cpy(vec);

    v_cpy.push_back(6);

    for (auto c = v_cpy.begin(); c != v_cpy.end(); ++c) {
        std::cout << *c << '\n';
    }

    std::cout << v_cpy.capacity_() << '\n';

    v_cpy[1000] = 10;

    std::cout << v_cpy[1000] << '\n';
}

int main()
{
    // remove();
    // copy_constructor();
    iters();
}
