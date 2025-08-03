#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    if(initial_capacity<2)initial_capacity= 2;
    capacity = initial_capacity;
    data = new int[capacity];
    front_idx = -1; rear_idx = -1;
    // TODO: Allocate memory for the array with the specified initial capacity
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    int current_size;
    if(rear_idx==-1){
        current_size = 0;
        front_idx = 0;
        
    }
    else if(rear_idx<front_idx){
        current_size = rear_idx+1+capacity-front_idx;
    }else{
        current_size = rear_idx-front_idx+1;
    }
    if(current_size==capacity){
        resize(capacity*2);
    }
    
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    int index = (rear_idx+1)%capacity;
    data[index] = item;
    rear_idx = index;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty()) {
        cout<<"Nothing left to pop!\n";
        return -1;                                                                //-----?
    }
    // TODO: Decrement current_size and return the element at the front of the queue
    int current_size = size();
    current_size--;
    int item = data[front_idx];
    if(current_size==0){
        //clear();
        rear_idx = -1; front_idx = -1;
        return item;
    }
    front_idx=(front_idx+1)%capacity;
    if(current_size<=capacity/4 && capacity/2 >= 2){
        resize(capacity/2);
    }
    return item;
    // TODO: Update front index
    // TODO: Return the dequeued element
}
// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    int* new_data = new int[new_capacity];
    // TODO: Copy elements from the old array to the new array
    int index = front_idx;
    int i = 0;
    while(index!=rear_idx){
        new_data[i++]=data[index];
        index = (index+1)%capacity;
    }
    new_data[i++]=data[rear_idx];
    // TODO: Delete the old array
    delete[] data;
    // TODO: Update the data pointer and capacity
    data = new_data;
    // TODO: Update front and rear indices
    capacity = new_capacity;
    front_idx = 0; rear_idx = --i;
}
// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    int* new_data = new int[20];
    delete[] data;
    data = new_data;
    capacity = 20;
    front_idx = -1; rear_idx = -1;
    
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    int current_size;
    if(rear_idx==-1){
        current_size = 0;
    }
    else if(rear_idx<front_idx){
        current_size = rear_idx+1+capacity-front_idx;
    }else{
        current_size = rear_idx-front_idx+1;
    }
    return current_size;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty()){
        cout<<"Queue is empty! Nothing to give back!\n";
        return -1;
    }
    // TODO: Return the element at the front of the queue without removing it
    return data[front_idx];
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if (empty()){
        cout<<"Queue is empty! Nothing to give back!\n";
        return -1;
    }
    // TODO: Return the element at the back of the queue without removing it
    return data[rear_idx];
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    int current_size = size();
    return current_size == 0;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    
    string s = "<";
    int index = front_idx;
    while(index!=rear_idx){
        s+=(to_string(data[index]));
        s+=", ";
        index = (index+1)%capacity;
    }
    if(rear_idx!=-1)s+=(to_string(data[rear_idx]));
    s+="|\n";
    return s;
}



int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}