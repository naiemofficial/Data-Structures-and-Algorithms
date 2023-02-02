#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <climits>
using namespace std;

class Graph {
  private:
    map <int, vector<pair<int, int>>> graph;
    map <int, int> distance;
    set <pair<int, int>> Set;
    void BFS(int u){
        distance[u] = 0;
        Set.insert(make_pair(distance[u], u));
        while(!Set.empty()){
            auto top = *(Set.begin());
            Set.erase(Set.begin());
            for(auto v:graph[top.second]){
                int weightSum = top.first + v.second;
                if(weightSum < distance[v.first]){ // new_distance < old_distance
                    auto search = Set.find(make_pair(distance[v.first], v.first));
                    if(search != Set.end()){
                        Set.erase(search);
                    }
                    distance[v.first] = weightSum;
                    Set.insert(make_pair(distance[v.first], v.first));
                }
            }
        }
    }
  public:
    void addEdge(int u, int v, int w){
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
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
        // Set infinity (∞) as default value for the distance map
        for(auto u:graph)
            distance[u.first] = INT_MAX;

        BFS(src);

        // Print Shortest
        cout << endl << "Shortest Path from the " << src << " to N: ";
        for(auto u:distance){
            cout << ((u.second == INT_MAX) ? "∞" : to_string(u.second)) << "  ";
        }
        cout << endl;
    }
};

int main(){
    Graph G;
    G.addEdge(0, 1, 7);
    G.addEdge(0, 2, 1);
    G.addEdge(0, 3, 2);
    G.addEdge(1, 2, 3);
    G.addEdge(1, 3, 5);
    G.addEdge(1, 4, 1);
    G.addEdge(3, 4, 7);

    cout << "Adjacency List: " << endl;
    G.print();

    G.shortestPath(0);

}