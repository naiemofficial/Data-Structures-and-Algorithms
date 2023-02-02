#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
  public:
    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v];
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
};

int main(){
    Graph G;
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(3, 2);
    G.addEdge(3, 4);
    G.addEdge(4, 2);

    cout << "Adjacency List: " << endl;
    G.print();
}