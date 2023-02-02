#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, bool> visited;
    bool directed;
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
        cout << u << ", ";
        visited[u] = true;
        for(auto v:graph[u]){
            if(!visited[v]) DFS(v);
        }
    }
};

int main(){
    Graph G;
    G.addEdge(0, 1);
    G.addEdge(1, 4);
    G.addEdge(4, 5);
    G.addEdge(4, 3);
    G.addEdge(3, 2);
    G.addEdge(2, 1);
    G.addEdge(2, 0);
    G.addEdge(3, 1);
    G.addEdge(4, 0);

    cout << "Adjacency List: " << endl;
    G.print();

    cout << endl << "DFS: ";
    G.DFS(3);
}