#include <iostream>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

class Graph {
  private:
    map <int, list<int>> graph;
    map <int, bool> visited, visitedDFS;
    list <int> result;
    bool cyclic = false;
    void DFS(int u){
        visited[u] = visitedDFS[u] = true;
        for(auto v:graph[u]){
            if(!visited[v]){
                DFS(v);
            } else if(visited[v] && visitedDFS[v]){
                cyclic = true;
            }
        }
        result.push_front(u);
        visitedDFS[u] = false;
    }
  public:
    void addEdge(int a, int b){
        graph[a].push_back(b);
        graph[b];
    }

    void topoSort(){
        // Loop for disconnected component(s) in a graph
        for(auto u:graph){
            if(!visited[u.first])
                DFS(u.first);
        }

        // Print
        if(cyclic){
            cout << "Cycle Detected!" << endl;
            cout << "Note: Graph must be Directed Acyclic Graph (DAG) to perform Topological Sort" << endl;
        } else {
            cout << "| ";
            for(auto val:result)
                cout << val << " | ";
            cout << endl;
        }
    }
};

int main(){
    Graph G;
    // Componenet - 1
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 4);
    G.addEdge(4, 5);
    G.addEdge(3, 6);
    G.addEdge(6, 5);

    // Componenet - 2
    G.addEdge(7, 8);
    G.addEdge(8, 9);
    G.addEdge(7, 9);

    G.topoSort();
}