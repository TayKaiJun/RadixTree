//
//  RadixTree.h
//  Project4
//
//  Created by Kai Jun Tay on 6/3/22.
//

#ifndef RadixTree_h
#define RadixTree_h

#include <iostream>
const int OFFSET = ' ';
const int VECTOR_SIZE = 'z' - OFFSET+1;
using namespace std;

template <typename ValueType>
class RadixTree{
    
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;

//    void print() const; //for testing purpose - prints everything in tree
    
private:
    struct Node{
        std::string key_prefix;
        ValueType leaf_value;
        std::vector<Node*> children = std::vector<Node*>(VECTOR_SIZE, nullptr);
        bool operator<(const Node& rhs) const {
            return (key_prefix < rhs.key_prefix);
        };
        bool isword = false;
    };
    void cleanup_tree(Node* cur);
    void insert_childNode(std::string prefix, const ValueType &value, Node* &cur);
    ValueType* search_from(std::string key, Node* cur) const;
    Node* root;
//    void print(Node* cur) const; //for testing purpose - prints everything in tree
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree(){
    root = nullptr;
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree(){
//    cerr<<"CLEANING TREE"<<endl;
    cleanup_tree(root);
}

template <typename ValueType>
void RadixTree<ValueType>::cleanup_tree(Node* cur){
    if(cur == nullptr)
        return;
    for(int i = 0; i < VECTOR_SIZE; i++){
        if(cur->children[i] == nullptr)
            continue;
        cleanup_tree(cur->children[i]);
    }
//    delete cur;
    
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType &value){

    if(key == "")
        return;

    //case 1: empty tree - initialize a root node (special node that has no key/val)
    int pos = key[0] - OFFSET;
    if(root == nullptr){
        root = new Node();
    }
    //always attempt to insert based on the first letter of the key
    insert_childNode(key, value, root->children[pos]);
}

template <typename ValueType>
void RadixTree<ValueType>::insert_childNode(std::string prefix, const ValueType &value, Node* &cur){
    //empty node: inserts remainder of key, inserts value, and updates isword to true
    if(cur == nullptr){
        cur = new Node();
        cur->key_prefix = prefix;
        cur->leaf_value = value;
        cur->isword = true;
        return;
    }

    int matchingPos = 0;
    for(; matchingPos < cur->key_prefix.length(); matchingPos++){
        if(cur->key_prefix[matchingPos] != prefix[matchingPos])
            break;
    }

    if(matchingPos == prefix.length()){
//        std::cerr << "matched" << std::endl;
        if(!cur->isword){
            cerr<<"I'm here!"<<endl;
            cur->isword = true;
            cur->leaf_value = value;
        }
        return; //key found, do not insert anything
    }
    else {
        if(matchingPos == cur->key_prefix.length()){
            //word to be inserted encompasses the prefix already
            
            std::string newPrefix = prefix.substr(matchingPos);
            insert_childNode(newPrefix, value, cur->children[newPrefix[0]-OFFSET]);
        }
        else{
            //key does not match, breaks current node's key into the common prefix, then inserts the remainder of the key into a new node and the remainder of the newkey into a new node.
            std::string updated_key = cur->key_prefix.substr(0,matchingPos);
            std::string remainder = cur->key_prefix.substr(matchingPos);
            cur->key_prefix = updated_key;
            Node* branch = new Node();
            branch->key_prefix = remainder;
            branch->leaf_value = cur->leaf_value;
            branch->children = vector<Node*>(cur->children);
//            ValueType temp = cur->leaf_value;
//            cur->leaf_value = 0;
            if(cur->isword){
                branch->isword = true;
                cur->isword = false;
            }
            for(int i = 0; i < VECTOR_SIZE; i++)
                cur->children[i] = nullptr;
            cur->children[remainder[0]-OFFSET] = branch;
//            insert_childNode(remainder, temp, cur->children[remainder[0]-OFFSET]); //this should carry over the old vector of arrays.
            std::string newPrefix = prefix.substr(matchingPos);
            insert_childNode(newPrefix, value, cur->children[newPrefix[0]-OFFSET]);
        }
    }


}

//template <typename ValueType>
//void RadixTree<ValueType>::print() const{
//    print(root);
//}
//
//template <typename ValueType>
//void RadixTree<ValueType>::print(Node* cur) const{
//    if(cur == nullptr)
//        return;
//    if(cur != root)
//        std::cerr << cur->key_prefix << "(is word: " << cur->isword << ")"<< std::endl;
//    for(int i = 0; i < VECTOR_SIZE; i++){
//        print(cur->children[i]);
//    }
//}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const{
    if(key == "" || root==nullptr)
        return nullptr;
    return search_from(key, root);
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search_from(std::string key, Node* cur) const{
    if(cur == nullptr) //key does not exist
        return nullptr;

    int matchingPos = 0;
    for(; matchingPos < cur->key_prefix.length(); matchingPos++){
        if(cur->key_prefix[matchingPos] != key[matchingPos])
            break;
    }
    
    if(matchingPos == key.length()){
        return cur->isword ? &(cur->leaf_value) : nullptr;
    }

    std::string remainder = key.substr(matchingPos);
    return search_from(remainder, cur->children[remainder[0]-OFFSET]);
}

#endif /* RadixTree_h */
