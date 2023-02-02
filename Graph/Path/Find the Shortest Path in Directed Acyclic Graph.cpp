#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <climits>
using namespace std;

class Graph {
  private:
    map <int, vector<pair<int, int>>> graph;
    map <int, bool> visited;
    map <int, int> distance;
    stack <int> topoSort;
    void DFS(int u){
        visited[u] = true;
        for(auto v:graph[u]){
            if(!visited[v.first]) DFS(v.first);
        }
        topoSort.push(u);
    }
    void path(int u){
        distance[u] = 0;
        int top, weightSum;
        while(!topoSort.empty()){
            top = topoSort.top();
            if(distance[top] != INT_MAX){
                for(auto v:graph[top]){
                    int weightSum = distance[top] + v.second;
                    if(weightSum < distance[v.first])
                        distance[v.first] = weightSum;
                }
            }
            topoSort.pop();
        }
    }
  public:
    void addEdge(int u, int v, int w){
        graph[u].push_back(make_pair(v, w));
        graph[v];
    }

    void print(){
        for(auto u:graph){
            cout << "[" << u.first << "] => ";
            for(int i = 0; i < u.second.size(); i++){
                cout << (i == 0 ? "[" : ", ");
                cout << "{" << u.second[i].first << ", " << u.second[i].second << "}";
                if(i == u.second.size()-1) cout << "]";
            }
            cout << endl;
        }
    }

    void shortestPath(int src){
        DFS(src);
        // Set infinity (∞) as default value for the distance map
        for(auto u:graph)
            distance[u.first] = INT_MAX;

        path(src);

        // Print Shortest
        cout << endl << "Shortest Path from the " << src << " to N: ";
        for(auto v:distance){
            cout << ((v.second == INT_MAX) ? "∞" : to_string(v.second)) << "  ";
        }
        cout << endl;
    }
};

int main(){
    Graph G;
    G.addEdge(0, 1, 5);
    G.addEdge(0, 2, 3);
    G.addEdge(1, 2, 2);
    G.addEdge(1, 3, 6);
    G.addEdge(2, 3, 7);
    G.addEdge(2, 4, 4);
    G.addEdge(2, 5, 2);
    G.addEdge(3, 4, -1);
    G.addEdge(4, 5, -2);

    cout << "Adjacency List: " << endl;
    G.print();

    G.shortestPath(1);
}