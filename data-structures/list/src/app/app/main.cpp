#include "../../liblist/liblist/list.hpp"

#include <iostream>

#include <string>

#include <vector>

int main()
{
    forward_list::list<std::string> lst1 = {"one", "template"};

    lst1.push_back("in");
    lst1.push_back("my");
    lst1.push_back("life");

    lst1.push_front("no");

    lst1.remove("no");

    print_list(std::cout, lst1);
    std::cout << '\n';

    return 0;
}
