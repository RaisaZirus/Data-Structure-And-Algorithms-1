#include "stack.h"
#include <iostream>
using namespace std;
// Constructor implementation
ListStack::ListStack() {
    // TODO: Initialize head to nullptr
    head= nullptr;
    // TODO: Initialize current_size to 0
    current_size =0;
}

// Destructor implementation
ListStack::~ListStack() {
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Push implementation
void ListStack::push(int item) {
    // TODO: Create a new node with the given item
    Node* new_node = new Node(item, head);
    // TODO: Make the new node point to the current head
    // TODO: Update head to point to the new node
    head =new_node;
    // TODO: Increment current_size
    current_size++;
}

// Pop implementation
int ListStack::pop() {
    // TODO: Check if the stack is empty, display error message if it is
    if (empty()) {
        cout <<"Nothing left to pop!\n";
        return -1;
    }
    // TODO: Store the data from the head node
    int return_data =head->data;
    Node* temp= head;
    // TODO: Update head to point to the next node
    head =head->next;
    // TODO: Delete the old head node
    delete temp;
    // TODO: Decrement current_size
    current_size--;
    // TODO: Return the stored data
    return return_data;
}

// Clear implementation
void ListStack::clear() {
    // TODO: Traverse the linked list, deleting each node
    Node* current = head;
    while (current != nullptr) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    // TODO: Reset head to nullptr
    head =nullptr;
    // TODO: Reset current_size to 0
    current_size = 0;
}

// Size implementation
int ListStack::size() const {
    // TODO: Return the current size (current_size)
    return current_size;
}

// Top implementation
int ListStack::top() const {
    // TODO: Check if the stack is empty, display error message if it is
    if (empty()) {
        cout<< "Stack is empty! Nothing to give back!\n";
        return -1;
    }
    // TODO: Return the data from the head node without removing it
    return head->data;
}

// Empty implementation
bool ListStack::empty() const {
    // TODO: Return whether head is nullptr
    return head == nullptr;
}

// Print implementation
void ListStack::print() const {
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    // TODO: Traverse the linked list from head, printing each node's data
    cout << "|";
    Node* current = head;
    while(current != nullptr) {
        cout<< current->data;
        if (current->next !=nullptr) cout<< ", ";
        current =current->next;
    }
    cout <<">\n";
}