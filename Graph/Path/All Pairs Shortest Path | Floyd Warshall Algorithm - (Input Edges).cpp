#include <iostream>
#include <vector>
using namespace std;

class Graph {
  private:
    bool directed;
    vector<vector<int>> matrix;
  public:
    Graph(int n, bool dir = false){ // Constructor
        directed = dir;
        matrix = vector<vector<int>>(n, vector<int>(n, 1e9));
    }
    void addEdge(int u, int v, int w){
        matrix[u][v] = w;
        if(!directed) matrix[v][u] = w;
    }

    void shortestPath(){
        for(int k = 0; k < matrix.size(); k++){
            for(int i = 0; i < matrix.size(); i++){
                for(int j = 0; j < matrix[i].size(); j++){
                    if(i == j) matrix[i][j] = 0;
                    matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
                }
            }
        }
    }

    void print(){
        for (int row = 0; row < matrix.size(); row++){
            for (int col = 0; col < matrix[row].size(); col++){
                if(matrix[row][col] == 1e9){
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
    Graph G(4, true);
    G.addEdge(1, 0, 1);
    G.addEdge(0, 1, 2);
    G.addEdge(1, 2, 3);
    G.addEdge(3, 0, 3);
    G.addEdge(3, 2, 4);
    G.addEdge(3, 1, 5);

    G.shortestPath();
    cout << "Shortest Distance(s): " << endl;
    G.print();
}