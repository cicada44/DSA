#include "../../liblist/list.hpp"

#include "../../libqueue/queue.hpp"

#include <iostream>

#include <string>

#include <vector>

int main()
{
    queue<int> s2 = {1, 2, 3, 4, 5};

    queue<int> s(s2);

    s.push(6);

    s.print_queue(std::cout);
    std::cout << '\n';

    s.pop();

    s.print_queue(std::cout);
    std::cout << '\n';

    s.push(7);

    s.print_queue(std::cout);
    std::cout << '\n';

    std::cout << "Size of queue - " << s.size() << '\n';

    return 0;
}
