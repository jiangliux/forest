//
// Created by jiang on 18-1-26.
//

#ifndef FOREST_RED_BLACK_TREE_H
#define FOREST_RED_BLACK_TREE_H

#include <iostream>
#include <memory>

enum color_t {
    red, black
};

template<typename T>
struct red_black_tree_node {
    T val;
    color_t color;
    std::shared_ptr<red_black_tree_node<T>> left;
    std::shared_ptr<red_black_tree_node<T>> right;
    std::weak_ptr<red_black_tree_node<T>> parent;

    red_black_tree_node(T value, color_t c) :
            val(value), color(c), left(nullptr), right(nullptr) {
        parent.reset();
    }

    red_black_tree_node(T value) :
            val(value), color(red), left(nullptr), right(nullptr) {
        parent.reset();
    }
};

template<typename T>
class red_black_tree {
    std::shared_ptr<red_black_tree_node<T>> root;

    void rotate_left(std::shared_ptr<red_black_tree_node<T>> &);

    void rotate_right(std::shared_ptr<red_black_tree_node<T>> &);

    void fix(std::shared_ptr<red_black_tree_node<T>> &node);

    void pre_order_traversal(std::shared_ptr<red_black_tree_node<T>> &node) {
        if (!node) return;
        std::cout << node->val << " ";
        pre_order_traversal(node->left);
        pre_order_traversal(node->right);
    }

    void in_order_traversal(std::shared_ptr<red_black_tree_node<T>> &node) {
        if (!node) return;
        in_order_traversal(node->left);
        std::cout << node->val << " ";
        in_order_traversal(node->right);
    }

    void post_order_traversal(std::shared_ptr<red_black_tree_node<T>> &node) {
        if (!node) return;
        post_order_traversal(node->left);
        post_order_traversal(node->right);
        std::cout << node->val << " ";
    }

public:
    red_black_tree() : root(nullptr) {}

    void in_order_traversal() {
        in_order_traversal(root);
    }

    void pre_order_traversal() {
        pre_order_traversal(root);
    }

    void post_order_traversal() {
        post_order_traversal(root);
    }

    std::shared_ptr<red_black_tree_node<T>> insert_node(T);

    std::shared_ptr<red_black_tree_node<T>> search_node(T);

    std::shared_ptr<red_black_tree_node<T>> delete_node(T);


};

template<typename T>
void red_black_tree<T>::rotate_left(std::shared_ptr<red_black_tree_node<T>> &rotation_root) {
    auto new_root = rotation_root->right;
    auto orphan_tree = new_root->left;

    rotation_root->right = orphan_tree;
    if (orphan_tree) {
        orphan_tree->parent = rotation_root;
    }

    new_root->left = rotation_root;
    auto old_parent = rotation_root->parent.lock();

    if (!old_parent) {
        root = new_root;
    } else if (rotation_root == old_parent->left) {
        old_parent->left = new_root;
    } else {
        old_parent->right = new_root;
    }

    rotation_root->parent = new_root;
    new_root->parent = old_parent;
}

template<typename T>
void red_black_tree<T>::rotate_right(std::shared_ptr<red_black_tree_node<T>> &rotation_root) {
    auto new_root = rotation_root->left;
    auto orphan_tree = new_root->right;

    rotation_root->left = orphan_tree;
    if (orphan_tree) {
        orphan_tree->parent = rotation_root;
    }

    new_root->right = rotation_root;
    auto old_parent = rotation_root->parent.lock();

    if (!old_parent) {
        root = new_root;
    } else if (rotation_root == old_parent->left) {
        old_parent->left = new_root;
    } else {
        old_parent->right = new_root;
    }

    rotation_root->parent = new_root;
    new_root->parent = old_parent;
}

template<typename T>
void red_black_tree<T>::fix(std::shared_ptr<red_black_tree_node<T>> &node) {
    while (node != root && node->color == red && node->parent.lock()->color == red) {
        auto parent = node->parent.lock();
        auto grandpa = parent->parent.lock();
        if (parent == grandpa->left) {
            auto uncle = grandpa->right;
            if (uncle && uncle->color == red) {
                parent->color = black;
                uncle->color = black;
                grandpa->color = red;
                node = grandpa;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotate_left(node);
                }
                parent = node->parent.lock();
                grandpa = parent->parent.lock();
                parent->color = black;
                grandpa->color = red;
                rotate_right(grandpa);
            }
        } else {
            auto uncle = grandpa->left;
            if (uncle && uncle->color == red) {
                parent->color = black;
                uncle->color = black;
                grandpa->color = red;
                node = grandpa;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotate_right(node);
                }
                parent = node->parent.lock();
                grandpa = parent->parent.lock();
                parent->color = black;
                grandpa->color = red;
                rotate_left(grandpa);
            }
        }
    }
    root->color = black;
}

template<typename T>
std::shared_ptr<red_black_tree_node<T>> red_black_tree<T>::insert_node(T val) {
    std::shared_ptr<red_black_tree_node<T>> current = root;
    std::shared_ptr<red_black_tree_node<T>> parent = nullptr;

    while (current) {
        parent = current;
        if (val < current->val) {
            current = current->left;
        } else if (val > current->val) {
            current = current->right;
        } else {
            return nullptr;
        }
    }

    current = std::make_shared<red_black_tree_node<T>>(val);
    current->parent = parent;

    if (!parent) {
        root = current;
    } else if (val < parent->val) {
        parent->left = current;
    } else {
        parent->right = current;
    }

    fix(current);
    return current;
}


#endif //FOREST_RED_BLACK_TREE_H
