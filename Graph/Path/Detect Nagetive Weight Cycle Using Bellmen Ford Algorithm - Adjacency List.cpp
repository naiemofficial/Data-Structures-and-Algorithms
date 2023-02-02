#include <iostream>
#include <map>
#include <vector>
#include <climits>
using namespace std;

class Graph {
  private:
    map <int, vector<pair<int, int>>> graph;
    map <int, int> distance;
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

    void BellmanFord(int src){
        for (auto u:graph){
            distance[u.first] = INT_MAX;
        }

        // Start Algorithm
        distance[src] = 0;
        for(int i = 0; i < graph.size()-1; i++){ // n-1
            for(auto u:graph){ // Get the edges as 'u' from adjacency list
                for(auto v:u.second){ // Iterate every edges of 'u'
                    if(distance[u.first] != INT_MAX && (distance[u.first]+v.second) < distance[v.first]){
                        distance[v.first] = (distance[u.first]+v.second);
                    }
                }
            }
        }

        // Detect Cycle
        for(int i = 0; i < graph.size()-1; i++){
            for(auto u:graph){
                for(auto v:u.second){
                    if(distance[u.first] != INT_MAX && (distance[u.first]+v.second) < distance[v.first]){
                        cout << "Graph contains nagetive weight cycle" << endl;
                        return;
                    }
                }
            }
        }

        // Print Distance
        cout << endl << "Distance From " << src << " to N: ";
        for(auto key:distance){
            cout << key.second << "  ";
        }
        cout << endl;
    }
};

int main(){
    Graph G;
    G.addEdge(1, 2, 2);
    G.addEdge(2, 3, 2);
    G.addEdge(3, 1, -1);

    cout << "Adjacency List: " << endl;
    G.print();

    G.BellmanFord(1);
}