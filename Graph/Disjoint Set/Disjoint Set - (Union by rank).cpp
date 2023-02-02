#include <iostream>
#include <vector>
using namespace std;

class Graph {
  private:
    vector <int> parent;
    vector <int> rank;
  public:
    Graph(int n){ // Constructor
        parent = vector<int>(n+1);
        rank = vector<int>(n+1, 0);
        for(int i = 0; i <= n; i++)
            parent[i] = i;
    }
    int find_parent(int key){
        if(key == parent[key]) return key;
        return parent[key] = find_parent(parent[key]);
    }
    void make_union(int u, int v){ // Union By Rank
        int pu = find_parent(u), pv = find_parent(v);
        if(rank[pu] < rank[pv]){
            parent[pu] = pv;
        } else if(rank[pv] < rank[pu]){
            parent[pv] = pu;
        } else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }
    void isDisjoint(int u, int v){
        if(find_parent(u) != find_parent(v)){
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

};

int main(){
    Graph G(10);

    G.make_union(1, 2);
    G.make_union(2, 3);

    G.make_union(4, 5);
    G.make_union(5, 6);

    // Check disjoint sets
    cout << "{1, 3}: "; G.isDisjoint(1, 3);
    cout << "{1, 6}: "; G.isDisjoint(1, 6);

}