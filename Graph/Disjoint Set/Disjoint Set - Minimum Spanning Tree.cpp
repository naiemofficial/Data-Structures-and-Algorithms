#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

class Graph {
  private:
    vector <int> parent;
    vector <int> size;
    vector <tuple<int, int, int>> edges;
    int find_parent(int key){
        if(key == parent[key]) return key;
        return parent[key] = find_parent(parent[key]);
    }
    void make_union(int u, int v){
        int pu = find_parent(u), pv = find_parent(v);
        if(size[pu] < size[pv]){
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] = size[pv];
        }
    }
  public:
    Graph(int n){ // Constructor
        parent = vector<int>(n+1);
        size = vector<int>(n+1, 1);
        for(int i = 0; i <= n; i++)
            parent[i] = i;
    }
    void addEdge(int w, int u, int v){
        edges.push_back(make_tuple(w, u, v));
    }
    int spanningTree(){
        sort(edges.begin(), edges.end());
        int mst = 0, w, u, v;
        for(auto edge:edges){
            tie(w, u, v) = edge;
            if(find_parent(u) != find_parent(v)){
                make_union(u, v);
                mst += w;
            }
        }
        return mst;
    }
};

int main(){
    Graph G(10);

    G.addEdge(1, 1, 4);
    G.addEdge(2, 1, 2);
    G.addEdge(3, 2, 3);
    G.addEdge(3, 2, 4);
    G.addEdge(4, 1, 5);
    G.addEdge(5, 3, 4);
    G.addEdge(7, 2, 6);
    G.addEdge(8, 3, 6);
    G.addEdge(9, 4, 5);

    cout << "MST: " << G.spanningTree() << endl; 

}