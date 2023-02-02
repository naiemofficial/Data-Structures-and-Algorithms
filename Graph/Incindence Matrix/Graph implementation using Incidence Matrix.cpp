#include <iostream>
#include <vector>
using namespace std;

class Graph {
  private:
    int m = 0, edge = 0;
    vector<vector<int>> matrix;
  public:
    Graph(int nodes, int edges){ // Constructor
        m = nodes;
        matrix = vector<vector<int>>(m, vector<int>(edges));
    }
    void addEdge(int a, int b){
        if(a >= m ||  b >= m){
            cout << "Invalid edge [" << a << "]🠪[" << b << "]" << endl << "Node value should be max (m-1)" << endl << endl;
        } else if(edge == matrix[0].size()){
            cout << "Edge [" << a << "]🠪[" << b << "] not being " << (a == b ? "looped." : "connected.") << endl << "Maxmimum number of edge(s) has been reached!" << endl << endl;
        } else {
            matrix[a][edge] = 1;
            if(a != b) matrix[b][edge] = -1;
            edge++;
        }
    }

    void print(){
        for (int row = 0; row < matrix.size(); row++){
            for (int col = 0; col < matrix[row].size(); col++){
                cout << (matrix[row][col] == -1 ? " " : "  ") << matrix[row][col];
            }
            cout << endl;
        }
    }
};

int main(){
    int m = 6, edges = 8;
    Graph G(m, edges);
    G.addEdge(0, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 4);
    G.addEdge(4, 5);
    G.addEdge(4, 1);
    G.addEdge(1, 0);
    G.addEdge(0, 4);
    G.addEdge(2, 5);

    cout << "Incidence Matrix: " << endl;
    G.print();
}