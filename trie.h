//
// Created by jiang on 18-4-12.
//

#ifndef FOREST_TRIE_H
#define FOREST_TRIE_H

#include <memory>
#include <string>

const int ALPHABET_SIZE = 26;

struct trie_node{
    std::shared_ptr<trie_node> children[ALPHABET_SIZE];
    bool isLastWord;
    trie_node() : isLastWord(false){
        for(int i=0;i<ALPHABET_SIZE;++i) children[i] = nullptr;
    }
};

class trie {
public:
    void insert(const std::string&);
    bool search(const std::string&);
    bool remove(const std::string&);
    trie() : root(std::make_shared<trie_node>()) {};
private:
    std::shared_ptr<trie_node> root;
};


#endif //FOREST_TRIE_H
