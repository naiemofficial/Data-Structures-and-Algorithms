#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, bool> visited;
    queue <int> Q;
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

    void BFS(int source){
        Q.push(source);
        while(!Q.empty()){
            if(visited[Q.front()]){
                Q.pop();
            } else {
                cout << Q.front() << ", ";
                visited[Q.front()] = true;
                for(auto v:graph[Q.front()])
                    if(!visited[v]) Q.push(v);
                Q.pop();
            }
        }
    }
};

int main(){
    Graph G;
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 1);
    G.addEdge(3, 4);
    G.addEdge(0, 4);
    cout << "Adjacency List: " << endl;
    G.print();

    cout << endl << "BFS: ";
    G.BFS(3);
}