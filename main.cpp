#include <iostream>
#include <memory>
#include <string>
#include "trie.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    trie t;
    for(int i=0;i<n;++i){
        string s;
        cin >> s;
        t.insert(s);
    }
    int m;
    cin >> m;
    for(int i=0;i<m;++i){
        string s;
        cin >> s;
        if (t.search(s)) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}