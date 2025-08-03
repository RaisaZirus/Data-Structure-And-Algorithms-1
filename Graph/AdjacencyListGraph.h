#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"
#include "queue.h"

class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members
    int capacity; 
    arrayList *adjList;
    void resize(int new_cap){
        arrayList *adjList2 = new arrayList[new_cap];
        for(int i = 0; i<new_cap; i++)init(&adjList2[i]);
        for(int i = 0; i< capacity; i++){
            for(int j =0; j<new_cap; j++){
                append(adjList[i].array[j], &adjList2[i]);
            }
        }
        for (int i = 0; i < capacity; ++i) free_list(&adjList[i]);
        delete[] adjList;
        adjList = adjList2;
        new_cap = capacity;
    }
public:
    AdjacencyListGraph(){
        capacity = 10;
        adjList = new arrayList[capacity];
        for(int i = 0; i<capacity; i++){
            init(&adjList[i]);
        }
    }
    ~AdjacencyListGraph(){
        for (int i = 0; i < capacity; ++i) free_list(&adjList[i]);
        delete[] adjList;
    }
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if(v>=capacity)//almost full
        {
            int new_cap = capacity;
            while(new_cap<=v)new_cap*=2;
            resize(new_cap);
        }
        //otherwise , already added
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        AddNode(u);AddNode(v);
        //agei ache kina dekha lagbe-_-
        if(!is_present(v, &adjList[u]))append(v,&adjList[u]);
        if(!is_present(u, &adjList[v]))append(u,&adjList[v]);
        
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        // check if u, v exists
        if(u<0 || v <0 || u>=capacity || v>=capacity)return false;
        return is_present(u,&adjList[v]);
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        //check if v exists
        if(v<0 || v>= capacity){
            cout << "No such node to remove!\n";
            return;
        }
        for(int i = 0; i<capacity; i++){
            if(i!=v)delete_item(v,&adjList[i]);
        }
        clear(&adjList[v]);
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if(CheckEdge(u,v)){
            delete_item(u, &adjList[v]);
            delete_item(v, &adjList[u]);
        }else{
            cout << "No such edge to remove!\n";
            return;
        }
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
            arrayList connected_nodes = adjList[curr_node];
            for(int i = 0; i<adjList[curr_node].listSize; i++){
                if(!visited[connected_nodes.array[i]]){
                    q.enqueue(connected_nodes.array[i]);
                    visited[connected_nodes.array[i]]=true;
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
            arrayList connected_nodes = adjList[curr];
            for (int i = 0; i < connected_nodes.listSize; ++i) {
                int w = connected_nodes.array[i];
                if (!visited[w]) {
                    visited[w] = true;
                    parent[w] = curr;
                    q.enqueue(w);
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
            arrayList connected_nodes = adjList[curr];
            for (int i = 0; i < connected_nodes.listSize; ++i) {
                int w = connected_nodes.array[i];
                if (!visited[w]) {
                    visited[w] = true;
                    dist[w] = dist[curr]+1;
                    q.enqueue(w);
                }
            }
        }
        
        delete[] visited;
        delete[] dist;
        return -1;
    }

    arrayList GetNeighbors(int u) const override
    {
        arrayList list;
        init(&list);
        if (u < 0 || u >= capacity) return list;
        for (int i = 0; i < adjList[u].listSize; ++i) {
            append(adjList[u].array[i], &list);
        }
        return list;
    }

};

#endif // ADJACENCY_LIST_GRAPH_H
