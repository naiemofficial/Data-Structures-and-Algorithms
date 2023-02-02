#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, bool> visited;
    map <int, int> parent;
    vector <int> result;
    queue <int> Q;
    void path(int src, int srcParent = -1){
        Q.push(src);
        visited[src] = true;
        parent[src] = srcParent;
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

    void shortestPath(int src, int destination){
        path(src);
        while(!Q.empty()){ // BFS
            for(auto v:graph[Q.front()]){
                if(!visited[v]) path(v, Q.front());
            }
            Q.pop();
        }

        if(!visited[src] || !visited[destination]){
            cout << "src or Destination doesn't exist in the Graph" << endl;
        } else {
            int p = parent[destination];
            result.push_back(destination);
            while(p != -1){
                result.push_back(p);
                p = parent[p];
            }
            reverse(result.begin(), result.end());

            // Print
            for(int i = 0; i < result.size(); i++){
                if(i != 0) cout << " => ";
                cout << result[i];
            }
            cout << endl;
        }
    }
};

int main(){
    Graph G;
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(1, 4);
    G.addEdge(2, 5);
    G.addEdge(3, 8);
    G.addEdge(4, 6);
    G.addEdge(5, 8);
    G.addEdge(6, 7);
    G.addEdge(7, 8);

    cout << "Adjacency List: " << endl;
    G.print();

    cout << endl << "Shortest Path: ";
    G.shortestPath(1, 8);
}