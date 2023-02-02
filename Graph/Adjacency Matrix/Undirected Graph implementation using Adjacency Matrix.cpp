#include <iostream>
#include <vector>
using namespace std;

class Graph {
  private:
    int m = 0;
    vector<vector<int>> matrix;
  public:
    Graph(int nodes){ // Constructor
        m = nodes;
        matrix = vector<vector<int>>(m, vector<int>(m));
    }
    void addEdge(int u, int v){
        if(u >= m ||  v >= m){
            cout << "Invalid edge [" << u << "]🠨🠪[" << v << "]" << endl << "Node value should be max (m-1)" << endl << endl;
        } else {
            matrix[u][v] = matrix[v][u] = 1;
        }
    }

    void print(){
        for (int row = 0; row < matrix.size(); row++){
            for (int col = 0; col < matrix[row].size(); col++){
                cout << " " << matrix[row][col];
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