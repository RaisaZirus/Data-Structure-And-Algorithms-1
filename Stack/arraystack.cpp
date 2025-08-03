#include "stack.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayStack::ArrayStack(int initial_capacity) {
    // TODO: Initialize data members (data, capacity, current_size)
    if (initial_capacity<10) initial_capacity= 10;
    capacity= initial_capacity;
    current_size= 0;
    // TODO: Allocate memory for the array with the specified initial capacity
    data = new int[capacity];
}

// Destructor implementation
ArrayStack::~ArrayStack() {
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Push implementation
void ArrayStack::push(int item) {
    // TODO: Check if the array is 50% full (current_size >= capacity/2)
    // TODO: If 50% full, resize the array to double its current capacity
    if (current_size>= capacity/2) {
        resize(capacity*2);
    }
    // TODO: Add the new element to the top of the stack and increment current_size
    data[current_size++] =item;
}

// Pop implementation
int ArrayStack::pop() {
    // TODO: Check if the stack is empty, display error message if it is
    if (empty()) {
        cout<<"Nothing left to pop!\n";
        return -1; 
    }
    // TODO: Decrement current_size and return the element at the top of the stack
    int pop_element =data[--current_size];
    // TODO: If the array is less than 25% full, resize it to half its current capacity
    if ((current_size< capacity/4) && capacity > 10) {
        int new_capacity =capacity/2;
        if (new_capacity <10)new_capacity = 10;
        resize(new_capacity);
    }
    // TODO: Return the popped element
    return pop_element;
}

// Clear implementation
void ArrayStack::clear() {
    // TODO: Reset the stack to be empty (set current_size to 0)
    current_size =0;
    // TODO: No need to free memory, just logically clear the stack
}

// Size implementation
int ArrayStack::size() const {
    // TODO: Return the number of elements currently in the stack (current_size)
    return current_size;
}

// Top implementation
int ArrayStack::top() const {
    // TODO: Check if the stack is empty, display error message if it is
    if (empty()){
        cout<<"Stack is empty! Nothing to give back!\n";
        return -1;
    }
    // TODO: Return the element at the top of the stack without removing it
    return data[current_size - 1];
}

// Empty implementation
bool ArrayStack::empty() const {
    // TODO: Return whether the stack is empty (current_size == 0)
    return current_size == 0;
}

// Print implementation
void ArrayStack::print() const {
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    cout<< "|";
    for (int i =current_size-1; i >= 0; i--) {
        cout <<data[i];
        if(i>0) cout<< ", ";
    }
    cout <<">\n";
}

// Resize implementation
void ArrayStack::resize(int new_capacity) {
    // TODO: Create a new array with the new capacity
    int* new_data = new int[new_capacity];
    // TODO: Copy elements from the old array to the new array
    for(int i = 0; i<current_size; i++){
        new_data[i] = data[i];
    }
    // TODO: Delete the old array
    delete[] data;
    // TODO: Update the data pointer and capacity
    data = new_data;
    capacity = new_capacity;
}