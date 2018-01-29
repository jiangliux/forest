//
// Created by jiang on 18-1-27.
//

#ifndef FOREST_BS_TREE_H
#define FOREST_BS_TREE_H

#include <memory>

template<typename key_t, typename value_t>
struct bst_node {
    typedef typename std::shared_ptr<bst_node<key_t, value_t>> node_type;
    typedef typename std::weak_ptr<bst_node<key_t, value_t>> parent_type;

    key_t key;
    value_t val;
    node_type left;
    node_type right;
    parent_type parent;
};

template<typename key_t, typename value_t>
class bst {
    typedef typename bst_node<key_t, value_t>::node_type node_type;
    node_type root;

    node_type minimum(node_type node) {
        while (node->left)
            node = node->left;
        return node;
    }

    node_type successor(node_type node) {
        if (node->right)
            return minimum(node->right);

        auto parent = node->parent.lock();
        while (parent && parent->right == node) {
            node = parent;
            parent = parent->parent.lock();
        }
        return parent;
    }

public:
    bst() : root(nullptr) {}

    node_type search(key_t key) {
        auto current = root;
        while (current && key != current->key) {
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return current;
    };

    node_type insert(key_t key, value_t value) {
        auto current = root;
        node_type prev = nullptr;
        while (current) {
            prev = current;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        current = std::make_shared<node_type>(key, value);
        current->parent.lock() = prev;

        if (!prev)
            root = current;
        else if (current->key < prev->key)
            prev->left = current;
        else
            prev->right = current;
        return current;
    }

};

#endif //FOREST_BS_TREE_H
