#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<pair<int, int>>> graph;
    bool directed;
    int w = 0;
  public:
    Graph(bool dir = false){ // Constructor
        directed = dir;
    }
    void addEdge(int u, int v){
        graph[u].push_back(make_pair(v, ++w));
        graph[v];
        if(!directed) graph[v].push_back(make_pair(u, w));
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
};

int main(){
    Graph G;
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 1);
    G.addEdge(3, 4);
    G.addEdge(0, 4);

    G.print();
}