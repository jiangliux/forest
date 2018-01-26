//
// Created by jiang on 18-1-25.
//

#ifndef FOREST_AVL_TREE_H
#define FOREST_AVL_TREE_H

#include <memory>
template <typename T>
struct avl_tree_node{
    T val;
    int balance_factor;
    std::shared_ptr<avl_tree_node<T>> left;
    std::shared_ptr<avl_tree_node<T>> right;
    std::weak_ptr<avl_tree_node<T>> parent;

    avl_tree_node(T value) :
            val(value), left(nullptr), right(nullptr)
    {
        parent.reset();
    }

};

template <typename T>
class avl_tree{
    std::shared_ptr<avl_tree_node<T>> root;

    void rotate_left(std::shared_ptr<avl_tree_node<T>>& rotation_root);
    void rotate_right(std::shared_ptr<avl_tree_node<T>>& rotation_root);
    void rebalance(std::shared_ptr<avl_tree_node<T>>& balance_root);
    void pre_order_traversal(std::shared_ptr<avl_tree_node<T>>& node){
        if (!node) return;
        std::cout << node->val<< " ";
        in_order_traversal(node->left);
        in_order_traversal(node->right);
    }
    void in_order_traversal(std::shared_ptr<avl_tree_node<T>>& node){
        if (!node) return;
        in_order_traversal(node->left);
        std::cout << node->val<< " ";
        in_order_traversal(node->right);
    }
    void post_order_traversal(std::shared_ptr<avl_tree_node<T>>& node){
        if (!node) return;
        in_order_traversal(node->left);
        in_order_traversal(node->right);
        std::cout << node->val<< " ";
    }

    unsigned long long height(std::shared_ptr<avl_tree_node<T>>& node){
        if (node==nullptr)
            return 0;
        else
            return std::max(height(node->left), height(node->right)) + 1;
    }
public:
    avl_tree() : root(nullptr) {}

    void in_order_traversal(){
        in_order_traversal(root);
    }

    void pre_order_traversal(){
        pre_order_traversal(root);
    }

    void post_order_traversal(){
        post_order_traversal(root);
    }
    std::shared_ptr<avl_tree_node<T>> insert_node(T);
    std::shared_ptr<avl_tree_node<T>> search_node(T);
    std::shared_ptr<avl_tree_node<T>> delete_node(T);
    std::shared_ptr<avl_tree_node<T>> min_val_node(std::shared_ptr<avl_tree_node<T>>&);
};

template <typename T>
void avl_tree<T>::rotate_left(std::shared_ptr<avl_tree_node<T>> &rotation_root) {
    std::shared_ptr<avl_tree_node<T>> new_root = rotation_root->right;
    std::shared_ptr<avl_tree_node<T>> orphan_tree = new_root->left;

    rotation_root->right = orphan_tree;
    if (orphan_tree)
        orphan_tree->parent = rotation_root;

    new_root->left = rotation_root;

    auto original_parent = rotation_root->parent.lock();
    if (original_parent==nullptr){
        root = new_root;
    } else if (rotation_root==original_parent->left){
        original_parent->left = new_root;
    } else{
        original_parent->right = new_root;
    }

    new_root->parent = original_parent;
    rotation_root->parent = new_root;
}

template<typename T>
void avl_tree<T>::rotate_right(std::shared_ptr<avl_tree_node<T>> &rotation_root) {
    std::shared_ptr<avl_tree_node<T>> new_root = rotation_root->left;
    std::shared_ptr<avl_tree_node<T>> orphan_tree = new_root->right;

    rotation_root->left = orphan_tree;
    if (orphan_tree)
        orphan_tree->parent = rotation_root;

    new_root->right = rotation_root;

    auto original_parent = rotation_root->parent.lock();
    if (original_parent==nullptr){
        root = new_root;
    } else if (rotation_root==original_parent->left){
        original_parent->left = new_root;
    } else{
        original_parent->right = new_root;
    }

    new_root->parent = original_parent;
    rotation_root->parent = new_root;
}

template<typename T>
void avl_tree<T>::rebalance(std::shared_ptr<avl_tree_node<T>> &balance_root) {
    while(balance_root!=nullptr){
        balance_root->balance_factor = height(balance_root->right) - height(balance_root->left);

        // rotate right
        if (balance_root->balance_factor==-2){
            // if left subtree is right heavy, double rotate
            if (balance_root->left->balance_factor==1){
                rotate_left(balance_root->left);
            }
            rotate_right(balance_root);
        }
            // rotate left
        else if (balance_root->balance_factor==2){
            // if right subtree is left heavy, double rotate
            if (balance_root->right->balance_factor==-1){
                rotate_right(balance_root->right);
            }
            rotate_left(balance_root);
        }
        balance_root = balance_root->parent.lock();
    }
}

template<typename T>
std::shared_ptr<avl_tree_node<T>> avl_tree<T>::insert_node(T val) {
    std::shared_ptr<avl_tree_node<T>> current = root;
    std::shared_ptr<avl_tree_node<T>> parent = nullptr;
    std::shared_ptr<avl_tree_node<T>> inserted_node = nullptr;

    // basic insert
    while(current!=nullptr){
        parent = current;
        if (val > current->val)
            current = current->right;
        else if (val < current->val)
            current = current->left;
        else
            return nullptr;
    }
    current = std::make_shared<avl_tree_node<T>>(val);
    current->parent = parent;
    if (parent== nullptr) {
        root = current;
    } else if (current->val < parent->val) {
        parent->left = current;
    } else{
        parent->right = current;
    }
    inserted_node = current;
    rebalance(parent);
    return inserted_node;
}

template<typename T>
std::shared_ptr<avl_tree_node<T>> avl_tree<T>::delete_node(T val) {
    auto wait_deleted_node = search_node(val);
    if (! wait_deleted_node)
        return nullptr;

    std::shared_ptr<avl_tree_node<T>> current = nullptr;
    // none or one child
    if (!wait_deleted_node->left || !wait_deleted_node->right){
        auto temp = wait_deleted_node->left ? wait_deleted_node->left : wait_deleted_node->right;
        auto parent = wait_deleted_node->parent.lock();

        if (!parent){
            root = temp;
        } else if (wait_deleted_node->val < parent->val){
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        current = parent;
    }
    // two child
    else {
        auto replace_node = min_val_node(wait_deleted_node->right);
        auto parent = replace_node->parent.lock();
        if (replace_node->val < parent->val){
            parent->left = nullptr;
        } else{
            parent->right = nullptr;
        }
        wait_deleted_node->val = replace_node->val;
        current = parent;
    }
    rebalance(current);
    return current;
}

template<typename T>
std::shared_ptr<avl_tree_node<T>> avl_tree<T>::search_node(T val) {
    std::shared_ptr<avl_tree_node<T>> current = root;
    while(current!=nullptr){
        if (val > current->val){
            current = current->right;
        } else if (val < current->val){
            current = current->left;
        } else{
            return current;
        }
    }
    return nullptr;
}

template<typename T>
std::shared_ptr<avl_tree_node<T>> avl_tree<T>::min_val_node(std::shared_ptr<avl_tree_node<T>> &node) {
    auto current = node;
    while(current->left){
        current = current->left;
    }
    return current;
}



#endif //FOREST_AVL_TREE_H
