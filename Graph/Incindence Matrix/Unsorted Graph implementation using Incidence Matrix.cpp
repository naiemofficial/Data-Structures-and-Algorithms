#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
  private:
    int m = 0, edge = 0, aID = -1, bID = -1;
    vector<vector<int>> matrix;
    vector<int> OL, NL; // Old List, New List 
    int searchIndex(vector<int> vect, int key){
        for(int i = 0; i < vect.size(); i++)
            if(vect[i] == key) return i;
        return -1;
    }
    void add_to_list(int u, int v){
        NL.push_back(u);
        NL.push_back(v);
        sort(NL.begin(), NL.end());
        NL.erase(unique(NL.begin(), NL.end()), NL.end());
        aID = searchIndex(NL, u);
        bID = searchIndex(NL, v);
    }
    void shift(int from, int to = 0){
        if(to < from) to = matrix.size()-1;
        vector<int> swapRow;
        for(int row = matrix.size()-1; row >= 0; --row){
            if(row >= from && row <= to){
                if(row == to) swapRow = matrix[row];
                matrix[row] = (row == from) ? swapRow : matrix[row-1];
            }
        }
    }
    void resizeMatrix(int from, int to){
        if(OL.size() > from && from != NL.size()-1 && OL[from] != NL[from]){
            shift(from, to);
        }
        if(from != to){
            if(OL.size() > to && to != NL.size()-1 && OL[to] != NL[to]){
                shift(to, from);
            }
        }
    }
  public:
    Graph(int nodes, int edges){ // Constructor
        m = nodes;
        matrix = vector<vector<int>>(m, vector<int>(edges));
    }
    void addEdge(int u, int v){
        if(NL.size() > m){
            cout << "Invalid edge [" << u << "]🠪[" << v << "]" << endl << "Node value should be max (m-1)" << endl << endl;
            NL = OL;
        } else if(edge == matrix[0].size()){
            cout << "Edge [" << u << "]🠪[" << v << "] not being " << (u == v ? "looped." : "connected.") << endl << "Maxmimum number of edge(s) has been reached!" << endl << endl;
            NL = OL;
        } else {
            add_to_list(u, v);
            resizeMatrix(aID, bID);
            matrix[aID][edge] = 1;
            if(aID != bID) matrix[bID][edge] = -1;
            edge++;
            OL = NL; // Update Old List (OL) from the new New List (NL)
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
    G.addEdge(10, 12);
    G.addEdge(12, 13);
    G.addEdge(13, 14);
    G.addEdge(14, 15);
    G.addEdge(14, 11);
    G.addEdge(11, 10);
    G.addEdge(10, 14);
    G.addEdge(12, 15);

    cout << "Incidence Matrix: " << endl;
    G.print();
}