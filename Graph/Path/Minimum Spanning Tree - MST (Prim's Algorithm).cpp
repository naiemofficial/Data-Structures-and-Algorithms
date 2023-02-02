#include <iostream>
#include <map>
#include <vector>
#include <climits>
using namespace std;

class Graph {
  private:
    map <int, vector<pair<int, int>>> graph;
    map <int, bool> visited;
    map <int, int> distance, parent;
    int minimum_distance_key(){
        int key = INT_MIN, min = INT_MAX;
        for(auto v:distance){
            if(!visited[v.first] && v.second < min){
                key = v.first;
                min = v.second;
            }
        }
        return key;
    }
    void spanningTree(int src){
        distance[src] = 0;
        for(int i = 0; i < graph.size(); i++){
            int min = minimum_distance_key();
            if(visited[min] == false){
                visited[min] = true;
                for(auto v:graph[min]){
                    if(v.second < distance[v.first]){
                        distance[v.first] = v.second;
                        parent[v.first] = min;
                    }
                }
            }
        }
    }
    void printMST(){
        cout << endl << endl;
        cout << "MST:  U  V   W" << endl;
        cout << "----------------" << endl;
        int mst = 0;
        for(auto v:parent){
            if(v.second != -1){
                cout << "      " << v.second << "  " << v.first << "   " << distance[v.first] << endl;
                mst += distance[v.first];
            }
        }
        cout << "----------------" << endl;
        cout << "MST Weight = " << mst << endl;
    }
  public:
    void addEdge(int a, int b, int weight){
        graph[a].push_back(make_pair(b, weight));
        graph[b].push_back(make_pair(a, weight));
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

    void MST(int src){
        for (auto u:graph){
            distance[u.first] = INT_MAX;
            parent[u.first] = -1;
        }

        spanningTree(src);
        printMST();
    }
};

int main(){
    Graph G;
    G.addEdge(0, 1, 2);
    G.addEdge(0, 3, 6);
    G.addEdge(1, 2, 3);
    G.addEdge(1, 3, 8);
    G.addEdge(1, 4, 5);
    G.addEdge(2, 4, 7);

    cout << "Adjacency List: " << endl;
    G.print();

    G.MST(0);
}