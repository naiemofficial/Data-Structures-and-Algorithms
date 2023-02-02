#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <tuple>
using namespace std;

class Graph {
  private:
    vector <tuple<int, int, int>> edges;
  public:
    void addEdge(int u, int v, int w){
        edges.push_back(make_tuple(u, v, w));
    }
    
    void print(){
        cout << " U  V   W" << endl;
        cout << "------------" << endl;
        int u, v, w;
        for(auto edge:edges){
            cout << "{";
            tie(u, v, w) = edge;
            cout << u << "  " << v << (w < 0 ? "  " : "   ") << w;
            cout << "}" << endl;
        }
    }

    void BellmanFord(int src, int n){
        vector <int> distance(n, INT_MAX);
        distance[src] = 0;

        // Start Algorithm
        int u, v, w;
        for(int i = 0; i < n-1; i++){
            for(auto edge:edges){
                tie(u, v, w) = edge;
                if(distance[u] != INT_MAX && (distance[u]+w) < distance[v]){
                    distance[v] = (distance[u]+w);
                }
            }
        }

        // Detect Cycle
        for(int i = 0; i < n-1; i++){
            for(auto edge:edges){
                tie(u, v, w) = edge;
                if(distance[u] != INT_MAX && (distance[u]+w) < distance[v]){
                    cout << "Graph contains nagetive weight cycle" << endl;
                    return;
                }
            }
        }

        // Print Distance
        cout << endl << "Distance From " << src << " to N: ";
        for(auto val:distance){
            cout << val << "  ";
        }
        cout << endl;
    }
};

int main(){
    Graph G;
    G.addEdge(0, 1, 2);
    G.addEdge(1, 2, -2);
    G.addEdge(2, 0, -1);

    cout << "Edge List: " << endl;
    G.print();

    int n = 3;
    G.BellmanFord(0, n);
}