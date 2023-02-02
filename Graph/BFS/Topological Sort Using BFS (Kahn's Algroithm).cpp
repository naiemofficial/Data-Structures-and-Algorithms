#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

class Graph {
  private:
    int val = 0;
    map <int, vector<int>> graph;
    map <int, int> indegree;
    vector <int> result;
    queue <int> Q;
    int visitCount = 0;
  public:
    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v];
    }

    void topoSort(){
        // Count Indegree
        for(auto u:graph){
            indegree[u.first];
            for(auto v:u.second)
                indegree[v]++; 
        }
        // Find the key(s) and add to the Queue that indegree is zero
        for(auto u:indegree){
            if(u.second == 0) Q.push(u.first);
        }

        //BFS
        if(Q.empty()){
            cout << "Topological sort not possible" << endl;
        } else {
            while(!Q.empty()){
                for(auto v:graph[Q.front()]){
                    indegree[v]--;
                    if(indegree[v] == 0) Q.push(v);
                }
                result.push_back(Q.front());
                Q.pop();
                visitCount++;
            }

            if(visitCount != graph.size()){
                cout << "Cycle Detected!" << endl;
                cout << "Note: Graph must be Directed Acyclic Graph (DAG) to perform Topological Sort" << endl;
            } else {
                // Print
                cout << "| ";
                for (auto key:result)
                    cout << key << " | ";
                cout << endl;
            }

        }
    }
};

int main(){
    Graph G;
    // Component - 1
    G.addEdge(6, 3);
    G.addEdge(6, 1);
    G.addEdge(5, 1);
    G.addEdge(5, 2);
    G.addEdge(3, 4);
    G.addEdge(4, 2);

    // Component - 2
    G.addEdge(7, 8);
    G.addEdge(8, 10);
    G.addEdge(7, 9);
    G.addEdge(9, 10);

    G.topoSort();
}