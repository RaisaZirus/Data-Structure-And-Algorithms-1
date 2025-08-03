#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    front_node = nullptr;
    rear_node = nullptr;
    // TODO: Initialize current_size to 0
    current_size = 0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    //cout << "hhehehn\n";
    // TODO: Create a new node with the given item
    Node *newnode = new Node(item,rear_node);                          ///???
    // TODO: Link the new node to the rear
    
    // TODO: Update the rear_node
    rear_node = newnode;
    // TODO: Increment the current size
    current_size++;
    if(current_size==1){
        front_node = rear_node;
    }
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty()) {
        cout <<"Nothing left to pop!\n";
        return -1;
    }
    // TODO: Store the data from the front node
    int item = front_node->data;
    Node *temp = front_node;
    // TODO: Update the front pointer to the next node
    if(current_size==1){
        delete temp;
        front_node = nullptr; rear_node = nullptr;
        current_size--;
        return item;
    }else{
        Node *curr = rear_node;
        Node *curr2 = curr;
        while(curr!=front_node){
            curr2 = curr;
            curr = curr->next;
        }
        front_node = curr2;
        front_node->next = nullptr;
        // TODO: Update the rear pointer if the queue becomes empty
        
        // TODO: Delete the old front node
        delete temp;
        // TODO: Decrement current_size
        current_size--;
        // TODO: Return the stored data
        return item;
    }
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    Node* curr = rear_node;
    while(curr!=nullptr){
        Node* nextnode = curr->next;
        delete curr;
        curr = nextnode;
    }
    // TODO: Reset front and rear pointer
    front_node = nullptr, rear_node = nullptr;
    // TODO: Reset current_size to 0
    current_size = 0;
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty()) {
        cout<< "Queue is empty! Nothing to give back!\n";
        return -1;
    }
    // TODO: Return the data from the front node without removing it
    return front_node->data;
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty()) {
        cout<< "Queue is empty! Nothing to give back!\n";
        return -1;
    }
    // TODO: Return the data from the back node without removing it
    return rear_node->data;
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    return front_node==nullptr;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
    string s = "|";
    Node* curr = rear_node;
    while(curr!=nullptr){
        string p;
        if(curr!=front_node)p=", ";
        else p = "< ";
        p+=(to_string(curr->data));
        s = p+s;
        curr = curr->next;
    }
    s+="\n";
    return s;
}
