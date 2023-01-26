#include "../../libtree/BSTree.hpp"

#include <iostream>

#include <string>

#include <vector>

using std::string;

using std::cout;

int main()
{
    Tree<int, bool> tree(5, 0);

    tree.insert_list({{3, 0}, {4, 0}, {2, 0}, {7, 0}, {6, 0}});

    tree.print_preorder(cout);

    cout << "DELETING\n";
    tree.remove(3);
    tree.remove(5);
    tree.print_preorder(cout);

    cout << "FINDING 3 - " << tree.find(3).first << '\n';

    cout << '\n';
    cout << "MAX - " << tree.max().first << '\n';
    cout << "MIN - " << tree.min().first << '\n';

    Tree<int, bool> newtree(tree);

    return 0;
}