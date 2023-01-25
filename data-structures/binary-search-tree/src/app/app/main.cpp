#include "../../libtree/BSTree.hpp"

#include <iostream>

#include <string>

using std::string;

using std::cout;

int main()
{
    Tree<string, int> tree("vika", 17);

    tree.insert("ilya", 18);
    tree.insert("vlad", 20);
    tree.insert("danil", 21);
    tree.insert("mom", 43);
    tree.insert("z", 1);
    tree.insert("y", 1);

    tree.print(std::cout);

    // auto found = tree.find("mom");

    // cout << "found - " << found.first << '\t' << found.second << '\n';

    cout << '\n';

    tree.remove("z");

    tree.print(std::cout);

    return 0;
}