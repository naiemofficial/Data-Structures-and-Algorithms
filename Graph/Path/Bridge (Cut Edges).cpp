#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, int> disc, low;
    map <int, bool> visited;
    int time = 0;
    void DFS(int u, int parent){
        disc[u] = low[u] = ++time;
        visited[u] = true;
        for(auto v:graph[u]){
            if(v == parent) continue;
            if(!visited[v]){
                DFS(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] > disc[u]){
                    cout << u << " 🠰🠲 " << v << endl;
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
  public:
    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v].push_back(u);
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

    void Bridge(){
        for(auto u:graph){
            if(!visited[u.first])
                DFS(u.first, -1);
        }
    }
};

int main(){
    Graph G;
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(1, 2);
    G.addEdge(2, 3); // Bridge
    G.addEdge(3, 4);
    G.addEdge(3, 5);
    G.addEdge(4, 5);

    cout << "Adjacency List: " << endl;
    G.print();

    cout << endl << "Bridges: " << endl;
    G.Bridge();
}