#pragma once
#include<bits/stdc++.h>
using namespace std;
class Heap{
    private:
        vector<int> heap;
        int curr_index = -1;
        //helper functions 
        void push_up(int curr_index){
            while(curr_index>0 && heap[(curr_index-1)/2]<heap[curr_index]){
                swap(heap[curr_index],heap[(curr_index-1)/2]);
                curr_index = (curr_index-1)/2;
            }
        }
        void push_down(int curr_index){
            int max_n = curr_index;
            int lefty = 2*curr_index+1;
            int righty = 2*curr_index+2;
            if(heap.size()>lefty && heap[lefty]>heap[max_n]){
                max_n = lefty;
            }
            if(heap.size()>righty && heap[righty]>heap[max_n]){
                max_n = righty;
            }
            if(max_n!=curr_index){
                swap(heap[curr_index],heap[max_n]);
                push_down(max_n);
            }
        }
    public:
        Heap(int n){
            heap.resize(n);
            curr_index = 0;
        }
        void insert(int item){
            heap[curr_index] = item;
            push_up(curr_index);
            curr_index++;
        }
        int size(){
            return heap.size();
        }
        int getMax(){
            if(heap.empty()){
                cout << "Nothing here!\n";
                return -1;
            }else return heap[0];
        }
        int deleteKey(){
            if(heap.empty()){
                cout << "Nothing here!\n";
                return -1;
            }
            int max_n = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            push_down(0);
            return max_n;
        }
        
  
};

void heapsort(vector<int>&v){
    int n = v.size();
    Heap h = Heap(n);
    for(int i = 0; i<n;i++){
        h.insert(v[i]);
    }
    for(int i = 0; i<n;i++){
        v[i] = h.deleteKey();
    }
}