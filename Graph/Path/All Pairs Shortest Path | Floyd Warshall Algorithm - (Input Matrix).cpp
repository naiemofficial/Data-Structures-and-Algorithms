#include <iostream>
#include <vector>
using namespace std;
#define INF (int)1e9

class Graph {
  public:
    vector<vector<int>> matrix;
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
    Graph G;
    G.matrix = {
        {INF,     2,   INF,    INF},
        {  1,   INF,     3,    INF},
        {INF,   INF,   INF,    INF},
        {  3,     5,     4,    INF},
    };

    G.shortestPath();
    cout << "Shortest Distance(s): " << endl;
    G.print();
}