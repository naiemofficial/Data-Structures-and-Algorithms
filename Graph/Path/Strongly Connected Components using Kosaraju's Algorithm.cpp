#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph, transpose;
    map <int, bool> visited;
    stack <int> topoSort;
    bool cyclic = false;
    void DFS(int u){
        visited[u] = true;
        for(auto v:graph[u]){
            if(!visited[v])
                DFS(v);
        }
        topoSort.push(u);
    }
    void revDFS(int u){
        cout << u << " ";
        visited[u] = true;
        for(auto v:transpose[u]){
            if(!visited[v])
                revDFS(v);
        }
    } 
  public:
    void addEdge(int a, int b){
        graph[a].push_back(b);
        graph[b];
    }

    void SCC(){
        // 1. Toplogical Sort
        for(auto u:graph){
            if(!visited[u.first])
                DFS(u.first);
        }

        // 2. Transpose Graph
        for(auto u:graph){
            visited[u.first] = false;
            for(auto v:u.second){
                transpose[v].push_back(u.first);
            }
        }

        // 3. Traverse graph reverse order by transpose graph
        while(!topoSort.empty()){
            if(!visited[topoSort.top()]){
                revDFS(topoSort.top());
                cout << endl;
            }
            topoSort.pop();
        }

    }
};

int main(){
    Graph G;
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 1);
    G.addEdge(4, 5);
    G.addEdge(5, 6);
    G.addEdge(6, 4);
    G.addEdge(2, 4); // Connect Component

    G.SCC();
}