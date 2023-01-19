#include "../../liblist/list.hpp"

#include "../../libstack/stack.hpp"

#include <iostream>

#include <string>

#include <vector>

int main()
{
    stack<int> s = {1, 2, 3, 4};

    s.push(6);

    s.print_stack(std::cout);

    std::cout << '\n';

    std::cout << "Size of stack - " << s.size() << '\n';

    return 0;
}
