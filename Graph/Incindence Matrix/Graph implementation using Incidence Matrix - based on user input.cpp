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
    void addEdge(int u, int v){
        if(u >= m ||  v >= m){
            cout << "Invalid edge [" << u << "]🠪[" << v << "]" << endl << "Node value should be max (m-1)" << endl << endl;
        } else if(edge == matrix[0].size()){
            cout << "Edge [" << u << "]🠪[" << v << "] not being " << (u == v ? "looped." : "connected.") << endl << "Maxmimum number of edge(s) has been reached!" << endl << endl;
        } else {
            matrix[u][edge] = 1;
            if(u != v) matrix[v][edge] = -1;
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
    system("clear");
    int edges = 0, m = 0;
    cout << "Enter the number of edge(s): ";
    cin >> edges;
    cout << "Enter the number of nodes: ";
    cin >> m;

    if(edges > 0){
        if(m >= 2 && edges >= 1){
            cout << endl << "Each line will contain data for a single edge. Use space between the nodes." << endl;
            cout << "Let's start entering the data below ↴" << endl;
            Graph G(m, edges);
            int u, v;
            for(int i = 0; i < edges; i++){
                cin >> u >> v;
                G.addEdge(u, v);
            }
            cout << endl << "Incidence Matrix: " << endl;
            G.print();
        } else {
            cout << "Minimum number of nodes would be 2 & number of edge must be at least 1" << endl;
        }
    }
}