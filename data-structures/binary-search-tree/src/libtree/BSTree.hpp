#include <iostream>

#include <map>

#include <vector>

template <typename KEYTYPE, typename VALTYPE>
class Tree {
    template <typename K, typename V>
    friend bool same(Tree<K, V>*& tree1, Tree<K, V>*& tree2);

public:
    Tree() = delete;

    Tree(const KEYTYPE& key, const VALTYPE& val)
        : key(key), value(val), left(nullptr), right(nullptr)
    {
    }

    ~Tree()
    {
        delete_dfs();
    }

    void insert(const KEYTYPE& k, const VALTYPE& v);
    void insert_list(const std::vector<std::pair<KEYTYPE, VALTYPE>>& init_list);
    std::pair<KEYTYPE, VALTYPE> find(const KEYTYPE& k);
    void remove(const KEYTYPE& key);

    std::pair<KEYTYPE, VALTYPE> min();
    std::pair<KEYTYPE, VALTYPE> max();

    std::ostream& print_preorder(std::ostream& os) const;

    void delete_dfs();

private:
    KEYTYPE key;
    VALTYPE value;
    Tree<KEYTYPE, VALTYPE>* left;
    Tree<KEYTYPE, VALTYPE>* right;
};

template <typename KEYTYPE, typename VALTYPE>
void Tree<KEYTYPE, VALTYPE>::insert_list(
        const std::vector<std::pair<KEYTYPE, VALTYPE>>& init_list)
{
    for (const auto& c : init_list) {
        insert(c.first, c.second);
    }
}

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

    while (iter != nullptr) {
        if (k == iter->key) {
            return {iter->key, iter->value};
        } else if (k < iter->key) {
            iter = iter->left;
        } else {
            iter = iter->right;
        }
    }

    return {};
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
    } else if (
            node_for_deletion->left != nullptr
            && node_for_deletion->right == nullptr) {
        node_for_deletion->key = node_for_deletion->left->key;
        node_for_deletion->value = node_for_deletion->left->value;
        delete node_for_deletion->left;
        node_for_deletion->left = nullptr;
    } else if (
            node_for_deletion->right != nullptr
            && node_for_deletion->left == nullptr) {
        node_for_deletion->key = node_for_deletion->right->key;
        node_for_deletion->value = node_for_deletion->right->value;
        delete node_for_deletion->right;
        node_for_deletion->right = nullptr;
    } else {
        std::pair<KEYTYPE, VALTYPE> del_key = node_for_deletion->left->max();
        remove(del_key.first);
        node_for_deletion->key = del_key.first;
        node_for_deletion->value = del_key.second;
    }
}

template <typename KEYTYPE, typename VALTYPE>
std::pair<KEYTYPE, VALTYPE> Tree<KEYTYPE, VALTYPE>::min()
{
    Tree<KEYTYPE, VALTYPE>* min = this;

    while (min->left != nullptr) {
        min = min->left;
    }

    return {min->key, min->value};
}

template <typename KEYTYPE, typename VALTYPE>
std::pair<KEYTYPE, VALTYPE> Tree<KEYTYPE, VALTYPE>::max()
{
    Tree<KEYTYPE, VALTYPE>* max = this;

    while (max->right != nullptr) {
        max = max->right;
    }

    return {max->key, max->value};
}

template <typename KEYTYPE, typename VALTYPE>
void Tree<KEYTYPE, VALTYPE>::delete_dfs()
{
    delete left;
    delete right;
}

template <typename KEYTYPE, typename VALTYPE>
std::ostream& Tree<KEYTYPE, VALTYPE>::print_preorder(std::ostream& os) const
{
    os << key << '\t' << value << '\n';
    if (left != nullptr)
        left->print_preorder(os);
    if (right != nullptr)
        right->print_preorder(os);
    return os;
}

// comparing KEYS ONLY (just for testing)
template <typename K, typename V>
bool same(Tree<K, V>*& tree1, Tree<K, V>*& tree2)
{
    if (tree1 == nullptr && tree2 == nullptr)
        return 1;

    if (tree1 != nullptr && tree2 != nullptr) {
        return (tree1->key == tree2->key && same(tree1->left, tree2->left)
                && same(tree1->right, tree2->right));
    }

    return 0;
}
