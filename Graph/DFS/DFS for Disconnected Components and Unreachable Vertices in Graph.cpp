#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, bool> visited;
    bool directed;
    void traverseDFS(int u){
        cout << u << ", ";
        visited[u] = true;
        for(auto v:graph[u]){
            if(!visited[v])
                traverseDFS(v);
        }
    }
  public:
    Graph(bool dir = false){ // Constructor
        directed = dir;
    }
    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v];
        if(!directed) graph[v].push_back(u);
    }

    void print(){
        for(auto u:graph){
            cout << "[" << u.first << "] => ";
            for(int i = 0; i < u.second.size(); i++){
                cout << (i == 0 ? "[" : ", ");
                cout << u.second[i];
                if(i == u.second.size()-1) cout << "]";
            }
            cout << endl;
        }
    }

    void DFS(int u){
        traverseDFS(u);
        // Condition for disconnected component(s) or unreachable vertices
        if(graph.size() != visited.size()){
            for(auto u:graph){
                if(!visited[u.first])
                    traverseDFS(u.first);
            }
        }
    }
};

int main(){
    Graph G(true);
    G.addEdge(1, 4);
    G.addEdge(4, 5);
    G.addEdge(4, 6);
    // G.addEdge(6, 5); // Unreachable
    G.addEdge(1, 6);
    G.addEdge(1, 2);
    G.addEdge(2, 6);
    G.addEdge(2, 8);
    G.addEdge(8, 6);
    G.addEdge(3, 2);
    G.addEdge(3, 8);
    G.addEdge(3, 7);
    G.addEdge(7, 6);

    cout << "Adjacency List: " << endl;
    G.print();

    cout << endl << "DFS: ";
    G.DFS(6);
}