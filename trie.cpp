//
// Created by jiang on 18-4-12.
//

#include "trie.h"

void trie::insert(const std::string& key) {
    auto cur = root;
    for(auto c : key){
        int index = c - 'a';
        if (cur->children[index] == nullptr){
            cur->children[index] = std::make_shared<trie_node>();
        }
        cur = cur->children[index];
    }
    cur->isLastWord = true;
}

bool trie::search(const std::string& key) {
    auto cur = root;
    for(auto c : key){
        int index = c - 'a';
        if (cur->children[index] == nullptr){
            return false;
        }
        cur = cur->children[index];
    }
    return cur && cur->isLastWord;
}

bool trie::remove(const std::string& key) {
    auto cur = root;
    for(auto c : key){
        int index = c - 'a';
        if (cur->children[index] == nullptr){
            return false;
        }
        cur = cur->children[index];
    }
    if (cur && cur->isLastWord){
        cur->isLastWord = false;
        return true;
    }
    return false;
}

