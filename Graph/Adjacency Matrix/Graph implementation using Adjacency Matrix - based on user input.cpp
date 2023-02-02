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
    void addEdge(int u, int v, bool directed = false){
        if(u >= m ||  v >= m){
            cout << "Invalid edge [" << u << "]" << (directed ? "" : "🠨") << "🠪[" << v << "]" << endl << "Node value should be max (m-1)" << endl << endl;
        } else {
            matrix[u][v] = 1;
            if(!directed) matrix[v][u] = 1;
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
    system("clear");
    int m =0, edges = 0, directed = 0; 
    cout << "Enter the number of nodes: ";
    cin >> m;
    cout << "Enter the number of edge(s): ";
    cin >> edges;

    if(edges > 0){
        cout << "Is this a directed graph? ([1]=YES/[0]=NO): ";
        cin >> directed;
        if(directed == 0 || directed == 1){
            cout << endl << "Each line will contain data for a single edge. Use space between the nodes." << endl;
            cout << "Let's start entering the data below ↴" << endl;
            Graph G(m);
            int u, v;
            for(int i = 0; i < edges; i++){
                cin >> u >> v;
                G.addEdge(u, v, directed);
            }
            cout << endl << "Adjacency Matrix: " << endl;
            G.print();
        } else {
            cout << "Invalid command!" << endl;
        }
    }
}