#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

class Graph {
  private:
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

    bool isCyclic(){
        // Count Indegree
        for(auto u:graph){
            indegree[u.first];
            for(auto v:u.second)
                indegree[v]++; 
        }
        // Find the vertices and add to the Queue that indegree is zero
        for(auto v:indegree){
            if(v.second == 0) Q.push(v.first);
        }
        //BFS
        while(!Q.empty()){
            for(auto v:graph[Q.front()]){
                indegree[v]--;
                if(indegree[v] == 0) Q.push(v);
            }
            result.push_back(Q.front());
            Q.pop();
            visitCount++;
        }
        return (visitCount != graph.size()) ? true : false;
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

    bool cyclic = G.isCyclic();
    cout << (cyclic ? "Cyclic Graph" : "Not a Cyclic Graph") << endl;
}