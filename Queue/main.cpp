#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/
/*
g++ -std=c++11 main.cpp arrayqueue.cpp listqueue.cpp -o main
.\main.exe 
*/

int main()
{
    freopen("test_input_1.txt", "r", stdin); // Test Case 1
    // freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;
    int timestamps[10001];
    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        int op; cin >> op;
        cout << "Operation " << i << " ";
        
        if(op==1){ // Arrival
            
            int id, timestamp;
            cin >> id >> timestamp;
            timestamps[id] = timestamp;
            cout << "(Arrival "<< id << " "<< timestamps[id] << "): ";
            if(!Q->empty()){
                Q->enqueue(id);
                cout << "\n";
            }
            else if (Q1->empty() && Q2->empty()) 
            {
                //cout << "randomQueue() called";
                int which_one = randomQueue();
                if(which_one==1){
                    Q1->enqueue(id);
                }else Q2->enqueue(id);
            }
            else if(Q1->empty())
            {
                Q1->enqueue(id); // Otherwise, add to Q1
                cout << "\n";
            }else if(Q2->empty()){
                Q2->enqueue(id);
                cout << "\n";
            }else{
                //not one of them is empty
                int q1backtime = timestamps[Q1->back()];
                int q2backtime = timestamps[Q2->back()];
                if(q1backtime>q2backtime){
                    //q2 te 
                    Q2->enqueue(id);
                }else{
                    Q1->enqueue(id);
                }
                cout << "\n";
            }
            
        }else if(op==2){ 
        // Leave
            int id_to_leave;
            cin >> id_to_leave;
            int hehe ; cin >> hehe;
            //first search Q1
            cout << "(Leave "<< id_to_leave << " "<< timestamps[id_to_leave] << "): ";
            Queue *Q_temp = new ListQueue();
            int size = Q1->size();
            bool found = false;
            for(int i = 0; i< size; i++){
                int curr = Q1->dequeue();
                if(id_to_leave==curr){
                    found = true;
                    timestamps[id_to_leave]=0;
                    //break;
                }else{
                    Q_temp->enqueue(curr);
                }
            }
            
            int si = Q_temp->size();
            for(int i = 0; i<si; i++){
                Q1->enqueue(Q_temp->dequeue());
            }
            if(!found){
                //search q2;
                int siz = Q2->size();
                Q_temp->clear();
                for(int i = 0; i< siz; i++){
                    int curr = Q2->dequeue();
                    if(id_to_leave==curr){
                        found = true;
                        timestamps[id_to_leave]=0;
                        //break;
                    }else{
                        Q_temp->enqueue(curr);
                    }
                }
                //Q2 = Q_temp;
                int ss = Q_temp->size();
                for(int i = 0; i<ss; i++){
                    Q2->enqueue(Q_temp->dequeue());
                }
                if(!found){
                    //seach Q
                    siz = Q->size();
                    Q_temp->clear();
                    for(int i = 0; i< siz; i++){
                        int curr = Q->dequeue();
                        if(id_to_leave==curr){
                            found = true;
                            timestamps[id_to_leave]=0;
                            //break;
                        }else{
                            Q_temp->enqueue(curr);
                        }
                    }
                    //Q = Q_temp;
                    int sss = Q_temp->size();
                    for(int i = 0; i<sss; i++){
                        Q->enqueue(Q_temp->dequeue());
                    }
                    if(!found){
                        cout << "No such patient is here";
                    }
                }
            }
            cout << "\n";
        }else if(op==3){
            cout << "(Merge):\n";
            if(Q1->empty()){
                int size = Q2->size();
                for(int i = 0; i<size; i++){
                    Q->enqueue(Q2->dequeue());
                }
            }else if(Q2->empty()){
                int size = Q1->size();
                for(int i = 0; i<size; i++){
                    Q->enqueue(Q1->dequeue());
                }
            }else{
                while(!Q1->empty() || !Q2->empty()){
                    if(!Q1->empty() && !Q2->empty()){
                        int q1fronttime = timestamps[Q1->front()];
                        int q2fronttime = timestamps[Q2->front()];
                        if(q1fronttime<q2fronttime){
                        //q1 e 
                            int curr = Q1->dequeue();
                            Q->enqueue(curr);
                        }else{
                            int curr = Q2->dequeue();
                            Q->enqueue(curr);
                        }
                    }else if(Q1->empty()){
                        int curr = Q2->dequeue();
                        Q->enqueue(curr);
                    }else{
                        int curr = Q1->dequeue();
                        Q->enqueue(curr);
                    }
                }
            }
        }else if(op==4){

            cout << "(Split):\n";
            // Split Q into Q1 and Q2 based on odd/even position
            int size = Q->size();
            for(int i = 1; i<=size; i++){
                int curr = Q->dequeue();
                if(i%2==0){
                    Q2->enqueue(curr);
                }else{
                    Q1->enqueue(curr);
                }
            }
        }else if(op==5){
            cout << "(Departure): ";
            if(!Q1->empty() && !Q2->empty()){
                int which_one = randomQueue();
                if(which_one==1){
                    Q1->dequeue();
                }else Q2->dequeue();
            }else if(Q1->empty()){
                Q2->dequeue();
                cout << "\n";
            }else if(Q2->empty()){
                Q1->dequeue();
                cout << "\n";
            }
            
            
        }

        // Print the state of all queues after each operation
        
        cout << "Q1: " << Q1->toString();
        cout << "Q2: " << Q2->toString();
        cout << "Q: " << Q->toString();
        
        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
        
    }

    return 0;
}