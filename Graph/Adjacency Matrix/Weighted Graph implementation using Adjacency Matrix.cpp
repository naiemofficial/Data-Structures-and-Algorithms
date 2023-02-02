#include <iostream>
#include <vector>
using namespace std;

class Graph {
  private:
    int m = 0;
    bool directed;
    vector<vector<int>> matrix;
    int w = 0;
  public:
    Graph(int nodes, bool dir = false){ // Constructor
        m = nodes;
        directed = dir;
        matrix = vector<vector<int>>(m, vector<int>(m, INT_MAX));
    }
    void addEdge(int u, int v){
        if(u >= m ||  v >= m){
            cout << "Invalid edge [" << u << "]🠨🠪[" << v << "]" << endl << "Node value should be max (m-1)" << endl << endl;
        } else {
            matrix[u][v] = ++w;
            if(!directed) matrix[v][u] = w;
        }
    }

    void print(){
        for (int row = 0; row < matrix.size(); row++){
            for (int col = 0; col < matrix[row].size(); col++){
                if(matrix[row][col] == INT_MAX){
                    cout << "   ∞";
                } else {
                    cout << (to_string(matrix[row][col]).size() > 1 ? "  " : "   ") << matrix[row][col];
                }
            }
            cout << endl;
        }
    }
};

int main(){
    int m = 6;
    Graph G(m);
    G.addEdge(0, 2);
    G.addEdge(0, 4);
    G.addEdge(1, 0);
    G.addEdge(2, 3);
    G.addEdge(2, 5);
    G.addEdge(3, 4);
    G.addEdge(4, 5);
    G.addEdge(4, 1);

    cout << "Adjacency Matrix: " << endl;
    G.print();
}