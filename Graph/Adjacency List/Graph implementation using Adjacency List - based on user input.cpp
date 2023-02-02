#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
  public:
    void addEdge(int u, int v, bool directed = false){
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
};

int main(){
    system("clear");
    int edges = 0; int directed = 0; 
    cout << "Enter the number of edge(s): ";
    cin >> edges;

    if(edges > 0){
        cout << "Is this a directed graph? ([1]=YES/[0]=NO): ";
        cin >> directed;
        if(directed == 0 || directed == 1){
            cout << endl << "Each line will contain data for a single edge. Use space between the nodes." << endl;
            cout << "Let's start entering the data below ↴" << endl;
            Graph G;
            int u, v;
            for(int i = 0; i < edges; i++){
                cin >> u >> v;
                G.addEdge(u, v, directed);
            }
            cout << endl << "Adjacency List: " << endl;
            G.print();
        } else {
            cout << "Invalid command!" << endl;
        }
    }
}