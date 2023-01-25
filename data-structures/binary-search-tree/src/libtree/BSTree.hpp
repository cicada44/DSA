#include <iostream>
#include <map>

// class Tree;

// class node {
//     friend class Tree;

// public:
//     node() : left(nullptr), right(nullptr)
//     {
//     }

//     // BSTree* insert(BSTree* root, int k);

// private:
// };

template <typename KEYTYPE, typename VALTYPE>
class Tree {
public:
    Tree() : left(nullptr), right(nullptr)
    {
    }

    Tree(const KEYTYPE& key, const VALTYPE& val)
        : key(key), value(val), left(nullptr), right(nullptr)
    {
    }

    ~Tree()
    {
        delete_dfs();
    }

    void insert(const KEYTYPE& k, const VALTYPE& v);
    std::pair<KEYTYPE, VALTYPE> find(const KEYTYPE& k);
    void remove(const KEYTYPE& key);

    std::ostream& print(std::ostream& os);

    void delete_dfs();

private:
    KEYTYPE key;
    VALTYPE value;
    Tree<KEYTYPE, VALTYPE>* left;
    Tree<KEYTYPE, VALTYPE>* right;
};

template <typename KEYTYPE, typename VALTYPE>
void Tree<KEYTYPE, VALTYPE>::insert(const KEYTYPE& k, const VALTYPE& v)
{
    Tree<KEYTYPE, VALTYPE>* node_insert = new Tree<KEYTYPE, VALTYPE>(k, v);

    Tree<KEYTYPE, VALTYPE>* iter = this;

    while (1) {
        if (k < iter->key) {
            if (iter->left == nullptr) {
                iter->left = node_insert;
                break;
            }
            iter = iter->left;
        } else if (k > iter->key) {
            if (iter->right == nullptr) {
                iter->right = node_insert;
                break;
            }
            iter = iter->right;
        } else {
            return;
        }
    }
}

template <typename KEYTYPE, typename VALTYPE>
std::pair<KEYTYPE, VALTYPE> Tree<KEYTYPE, VALTYPE>::find(const KEYTYPE& k)
{
    Tree<KEYTYPE, VALTYPE>* iter = this;

    while (iter->key != k) {
        if (iter->key > k) {
            iter = iter->left;
        } else if (iter->key < k) {
            iter = iter->right;
        } else {
            return {};
        }
    }

    return {iter->key, iter->value};
}

template <typename KEYTYPE, typename VALTYPE>
void Tree<KEYTYPE, VALTYPE>::remove(const KEYTYPE& k)
{
    Tree<KEYTYPE, VALTYPE>* node_for_deletion = this;
    Tree<KEYTYPE, VALTYPE>* parent = this;

    while (node_for_deletion->key != k) {
        if (node_for_deletion->key > k) {
            parent = node_for_deletion;
            node_for_deletion = node_for_deletion->left;
        } else if (node_for_deletion->key < k) {
            parent = node_for_deletion;
            node_for_deletion = node_for_deletion->right;
        } else {
            return;
        }
    }

    if (node_for_deletion->left == nullptr
        && node_for_deletion->left == nullptr) {
        if (parent->left == node_for_deletion)
            parent->left = nullptr;
        if (parent->right == node_for_deletion)
            parent->right = nullptr;
        delete node_for_deletion;
    }

    if (node_for_deletion->left != nullptr
        && node_for_deletion->right == nullptr) {
        node_for_deletion->key = node_for_deletion->left->key;
        node_for_deletion->value = node_for_deletion->left->value;
        delete node_for_deletion->left;
        node_for_deletion->left = nullptr;
    }

    if (node_for_deletion->right != nullptr
        && node_for_deletion->left == nullptr) {
        node_for_deletion->key = node_for_deletion->right->key;
        node_for_deletion->value = node_for_deletion->right->value;
        delete node_for_deletion->right;
        node_for_deletion->right = nullptr;
    }
}

template <typename KEYTYPE, typename VALTYPE>
void Tree<KEYTYPE, VALTYPE>::delete_dfs()
{
    delete left;
    delete right;
}

template <typename KEYTYPE, typename VALTYPE>
std::ostream& Tree<KEYTYPE, VALTYPE>::print(std::ostream& os)
{
    os << key << '\t' << value << '\n';
    if (left != nullptr)
        left->print(os);
    if (right != nullptr)
        right->print(os);
    return os;
}
