#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, bool> visited, visitedDFS;
    bool detectCycle(int u){
        visited[u] = visitedDFS[u] = true;
        for(auto v:graph[u]){
            if(!visited[v]){
                if(detectCycle(v))
                    return true;
            } else if(visited[v] && visitedDFS[v]){
                return true;
            }
        }
        return visitedDFS[u] = false;
    }
  public:
    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v];
    }

    bool isCyclic(){
        // Loop for disconnected component(s) in a graph
        for(auto u:graph){
            if(!visited[u.first])
                if(detectCycle(u.first)) return true;
        }
        return false;
    }
};

int main(){
    Graph G;
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 4);
    G.addEdge(4, 5);
    G.addEdge(3, 6);
    G.addEdge(6, 5);
    G.addEdge(7, 8);
    G.addEdge(8, 9);
    G.addEdge(9, 7);
    G.addEdge(2, 7);

    bool cyclic = G.isCyclic();
    cout << (cyclic ? "Cyclic Graph" : "Not a Cyclic Graph") << endl;
}