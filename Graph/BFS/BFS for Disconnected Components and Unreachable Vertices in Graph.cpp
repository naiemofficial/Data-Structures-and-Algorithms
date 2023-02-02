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
    void traverseBFS(int u){
        Q.push(u);
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

    void BFS(int src){
        traverseBFS(src);
        // Condition for disconnected component(s) or unreachable vertices
        if(graph.size() != visited.size()){
            for(auto u:graph){
                if(!visited[u.first])
                    traverseBFS(u.first);
            }
        }
    }
};

int main(){
    Graph G(true);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(1, 3);
    cout << "Adjacency List: " << endl;
    G.print();

    cout << endl << "BFS: ";
    G.BFS(3);
}