#include <iostream>
#include "avl_tree.h"

using namespace std;

int main() {
    avl_tree<int> tree;
    int n ;
    cin >> n;
    for(int i=0, tmp ;i<n;++i){
        cin >> tmp;
        tree.insert_node(tmp);
    }
    tree.in_order_traversal();
    cout << "\n";
    tree.pre_order_traversal();
    cout << "\n";
    cin >> n;
    for(int i=0, tmp ;i<n;++i){
        cin >> tmp;
        tree.delete_node(tmp);
    }
    tree.in_order_traversal();
    cout << "\n";
    tree.pre_order_traversal();
}