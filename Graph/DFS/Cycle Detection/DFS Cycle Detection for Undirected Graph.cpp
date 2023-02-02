#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, bool> visited;
    bool detectCycle(int u, int parent){
        visited[u] = true;
        for(auto v:graph[u]){
            if(!visited[v]){
                if(detectCycle(v, u))
                    return true;
            } else if(visited[v] && v != parent){
                return true;
            }
        }
        return false;
    }
  public:
    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bool isCyclic(){
        // Loop for disconnected component(s) in a graph
        for(auto u:graph){
            if(!visited[u.first])
                if(detectCycle(u.first, -1)) return true;
        }
        return false;
    }
};

int main(){
    Graph G;
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(2, 5);
    G.addEdge(3, 4);
    // G.addEdge(5, 6);
    G.addEdge(4, 7);
    G.addEdge(6, 7);
    G.addEdge(7, 8);
    G.addEdge(7, 9);

    bool cyclic = G.isCyclic();
    cout << (cyclic ? "Cyclic Graph" : "Not a Cyclic Graph") << endl;
}