#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;
/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    void clear_2(Node* node) {
        if (!node) return;
        clear_2(node->left);
        clear_2(node->right);
        delete node;
    }
    Node* insert_2(Node* node, Key key, Value value) {
        if (!node) {
            node_count++;
            return new Node(key, value);
        }
        if (key < node->key) {
            node->left = insert_2(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert_2(node->right, key, value);
        } else {
            
            return node;
        }
        return node;
    }
    Node* remove_2(Node* node, Key key) {
        if (!node) {
            return node;
        }
        if (key < node->key){
            node->left = remove_2(node->left, key);
        } else if (key > node->key) {
            node->right = remove_2(node->right, key);
        } else {
            //found
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                node_count--;
                return temp;
            }else if (!node->right){
                Node* temp = node->left;
                delete node;
                node_count--;
                return temp;
            }
            Node* temp = find_min_helper(node->right); //In-order successor
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove_2(node->right, temp->key);
        }
        return node;
    }
    Node* find_min_helper(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    Node* find_max_helper(Node* node) const {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }
    bool find_helper(Node* node, Key key) const {
        if (!node) {
            return false;
        }
        if (key < node->key) {
            return find_helper(node->left, key);
        } else if (key > node->key) {
            return find_helper(node->right, key);
        }
        return true;
    }
    Value get_helper(Node* node, Key key) const {
        if (!node){
            cout <<"Key not found\n"; 
        }
        if (key < node->key) {
            return get_helper(node->left, key);
        } else if (key > node->key) {
            return get_helper(node->right, key);
        }
        return node->value;
    }
    void update_helper(Node* node, Key key, Value value) {
        if (!node) {
            cout << "Key not found\n";
        }
        if (key < node->key) {
            update_helper(node->left, key, value);
        } else if (key > node->key){
            update_helper(node->right, key, value);
        } else {
            node->value = value;
        }
    }
    void clear_helper(Node* node) {
        if (!node) return;
        clear_helper(node->left);
        clear_helper(node->right);
        delete node;
    }
    // print modification
    void printinOrder(Node *root) const
    {
        if (!root)
            return;
        printinOrder(root->left);
        std::cout << "(" << root->key << ":" << root->value << ") ";
        printinOrder(root->right);
    }
    void printpostOrder(Node *root) const
    {
        if (!root)return;
        printpostOrder(root->left);
        printpostOrder(root->right);
        std::cout << "(" << root->key << ":" << root->value << ") ";
    }
    void printpreOrder(Node *root) const
    {
        if (!root)return;
        std::cout << "(" << root->key << ":" << root->value << ") ";
        printpreOrder(root->left);
        printpreOrder(root->right);
    }
    void printdefault(Node *root) const
    {
        if (!root)
        {
            return;
        }
        std::cout << "(" << root->key << ":" << root->value;
        if (root->left || root->right)
        {
            if(!root->left) 
                std::cout << " ()";
            printdefault(root->left);
            printdefault(root->right);
        }
        std::cout << ") ";
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST() {
        // TODO: Implement destructor to free memory
        clear_helper(root);
    }
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override {
        // TODO: Implement insertion logic
        if (find(key)) {
            return false; // Key already exists
        }
        root = insert_2(root, key, value);
        return true;
    }
    
    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override {
        if (!find(key)) {
            return false; // Key not found
        }
        root = remove_2(root, key);
        return true;
    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override {
        // TODO: Implement find logic
        return find_helper(root, key);
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override {
        // TODO: Implement get logic
        return get_helper(root, key);
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override {
        // TODO: Implement update logic
        update_helper(root, key, value);
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override {
        // TODO: Implement clear logic
        clear_helper(root);
        root = nullptr;
        node_count = 0;
    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        // TODO: Implement size logic
        return node_count;
    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        // TODO: Implement empty check logic
        return root == nullptr;
    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override {
        // TODO: Implement find_min logic
        Node* min_node = find_min_helper(root);
        if (!min_node)cout << "BST is empty\n";
        return min_node->key;
    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override {
        // TODO: Implement find_max logic
        Node* max_node = find_max_helper(root);
        if (!max_node) cout << "BST is empty\n";
        return max_node->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        if(empty()){
            std::cout << "The tree is Empty!\n";
            return;
        }
        // TODO: Implement print logic
        switch (traversal_type)
        {
        case 'd':
        case 'D':
        {
            std::cout << "BST (Default): ";
            printdefault(root);
            std::cout << std::endl;
            break;
        }
        case 'i':
        case 'I':
        {
            std::cout << "BST (In-order): ";
            printinOrder(root);
            std::cout << std::endl;
            break;
        }
        case 'p':
        case 'P':
        {
            std::cout << "BST (Pre-order): ";
            printpreOrder(root);
            std::cout << std::endl;
            break;
        }
        case 'o':
        case 'O':
        {
            std::cout << "BST (Post-order): ";
            printpostOrder(root);
            std::cout << std::endl;
            break;
        }
        }
    }
    
};

#endif // LISTBST_H