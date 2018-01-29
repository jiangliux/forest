#include <iostream>
#include "avl_tree.h"
#include "red_black_tree.h"
#include <vector>
using namespace std;

int main() {
    red_black_tree<int> tree;
    int n ;
    cin >> n;
    for(int i=0, tmp ;i<n;++i){
        cin >> tmp;
        tree.insert_node(tmp);
    }
    tree.in_order_traversal();
    cout << "\n";
    tree.pre_order_traversal();
}