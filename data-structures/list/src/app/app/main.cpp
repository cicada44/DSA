#include "../../liblist/list.hpp"

#include <iostream>

int main() {
    forward_list::list<int> l1 = {1, 2, 3};
    forward_list::list<int> l2;
    l2 = std::move(l1);

    forward_list::print_list(std::cout, l1);
    std::cout << '\n';

    forward_list::print_list(std::cout, l2);
    std::cout << '\n';
    std::cout << l2.size() << '\n';
}
