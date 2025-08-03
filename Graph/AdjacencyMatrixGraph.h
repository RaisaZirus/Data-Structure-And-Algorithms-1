#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"
#include "queue.h"

class AdjacencyMatrixGraph : public GraphADT
{
private:
    //TODO: Consider necessary private members as per your discretion
    int capacity; 
    arrayList *matrix;

    void resizeMatrix(int new_capacity)
    {
        //TODO: you need to resize your matrix when you will less data or more data
        arrayList *matrix2 = new arrayList[new_capacity];
        for(int i = 0; i<new_capacity; i++){
            init(&matrix2[i]);
            while(matrix2[i].listSize<new_capacity){
                increase_capacity(&matrix2[i]);
            }
            for(int j = 0; j< capacity; j++){
                if(i<=capacity && j<=capacity)matrix2[i].array[j] = matrix[i].array[j];
                else matrix[i].array[j] = 0;
            }
        }
        for (int i = 0; i < capacity; ++i) free_list(&matrix[i]);
        delete[] matrix;
        matrix = matrix2;
        new_capacity = capacity;
    }

public:
    AdjacencyMatrixGraph(){
        capacity = 10;
        matrix = new arrayList[capacity];
        for(int i = 0; i<capacity; i++){
            init(&matrix[i]);
            //arrayList 
            while(matrix[i].maxSize<10){
                increase_capacity(&matrix[i]);
            }
            for(int j = 0; j< capacity; j++){
                matrix[i].array[j] = 0;
            }
        }
    }
    ~AdjacencyMatrixGraph(){
        for(int i = 0; i<capacity; i++)free_list(&matrix[i]);
        delete[] matrix;
    }
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if(v>=capacity){//almost full
            int new_cap = capacity;
            while(new_cap<=v)new_cap*=2;
            resizeMatrix(new_cap);
        }
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        AddNode(u); AddNode(v);
        matrix[u].array[v] = 1;
        matrix[v].array[u] = 1;
        cout << "hehe\n";
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        if (u < 0 || u >= capacity || v < 0 || v >= capacity) return false;
        return matrix[u].array[v];
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        if(v<0 || v>= capacity){
            cout << "No such node to remove!\n";
            return;
        }
        for(int i = 0; i< capacity; i++){
            matrix[v].array[i] = 0;
            matrix[i].array[v] = 0;
        }
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if (u < 0 || u >= capacity || v < 0 || v >= capacity) return;
        matrix[u].array[v] = 0;
        matrix[v].array[u] = 0;
    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        if(u<0 || v<0 || u>=capacity || v>=capacity){return false;}
        bool *visited = new bool[capacity];
        for(int i = 0; i<capacity; i++) visited[i] =false;
        ArrayQueue q;
        visited[u] = true;
        q.enqueue(u);
        while(!q.empty()){
            int curr_node = q.dequeue();
            if(curr_node == v){
                delete[] visited; return true;
            }
            arrayList connected_nodes = matrix[curr_node];
            for(int i = 0; i<matrix[curr_node].maxSize; i++){
                if(connected_nodes.array[i]==1 && !visited[i]){
                    //neighbour uwu
                    visited[i] = true;
                    q.enqueue(i);
                }
            }
        }
        delete[] visited;
        return false;
    }

    void FindShortestPath(int u, int v) const override
    {
        //TODO: Find the shortest path between the nodes u and v and print it.
        if(!CheckPath(u,v)){
            cout << "No such path to traverse!\n";
            return;
        }
        bool *visited = new bool[capacity];
        for (int i = 0; i < capacity; ++i) visited[i] = false;
        int *parent = new int[capacity];
        for (int i = 0; i < capacity; ++i) parent[i] = -1;
        ArrayQueue q;
        visited[u] = true;
        q.enqueue(u);
        while(!q.empty()){
            int curr = q.dequeue();
            if(curr==v)break;
            arrayList connected_nodes = matrix[curr];
            for(int i = 0; i<matrix[curr].maxSize; i++){
                if(connected_nodes.array[i]==1 && !visited[i]){
                    //neighbour uwu
                    visited[i] = true;
                    parent[i] = curr;
                    q.enqueue(i);
                }
            }
        }
        arrayList tempo;
        init(&tempo);
        int curr = v;
        while (curr != -1) {
            append(curr, &tempo);
            curr = parent[curr];
        }
        cout << "Shortest path: ";
        for (int i = tempo.listSize - 1; i >= 0; --i) {
            std::cout << tempo.array[i] << " ";
        }
        cout << "\n";
        free_list(&tempo);
        delete[] visited;
        delete[] parent;
    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        if(!CheckPath(u,v)){
            cout << "No such path to traverse!\n";
            return -1;
        }
        bool *visited = new bool[capacity];
        for (int i = 0; i < capacity; ++i) visited[i] = false;
        int *dist = new int[capacity];
        for (int i = 0; i < capacity; ++i) dist[i] = -1;
        ArrayQueue q;
        visited[u] = true;
        q.enqueue(u);
        while(!q.empty()){
            int curr = q.dequeue();
            if(curr==v){
                int d = dist[v];
                delete[] visited;
                delete[] dist;
                return d;
            }
            arrayList connected_nodes = matrix[curr];
            for(int i = 0; i<matrix[curr].maxSize; i++){
                if(connected_nodes.array[i]==1 && !visited[i]){
                    //neighbour uwu
                    visited[i] = true;
                    dist[i] = dist[curr]+1;
                    q.enqueue(i);
                }
            }
        }
        delete[] visited;
        delete[] dist;
        return -1;
    }
    arrayList GetNeighbors(int u) const override
    {
        //TODO return a list of neighbors of node u
        arrayList list;
        init(&list);
        if (u < 0 || u >= capacity) return list;
        for (int i = 0; i < matrix[u].maxSize; ++i) {
            if(matrix[u].array[i]==1)append(i, &list);
        }
        return list;
    }

};

#endif // ADJACENCY_MATRIX_GRAPH_H
