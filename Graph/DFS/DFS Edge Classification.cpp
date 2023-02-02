#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
  private:
    map <int, vector<int>> graph;
    map <int, bool> visited;
    map <int, pair<int, int>> record; // Record start & ending time
    map <char, vector<pair<int, int>>> edges; // Tree, Forward, Back, Cross Edges entries 
    int time = 0;
    bool directed;

    bool pathFinder(int start, int target, bool init = true){
        for(auto val:graph[target]){
            if(target == start){
                return true;
            } else if(find(edges['T'].begin(), edges['T'].end(), make_pair(target, val)) != edges['T'].end()){ // Find the path that matches with 'target' ---to--> 'key'
                return pathFinder(start, val, false);
            }
        }
        return false;
    }
  public:
    Graph(bool dir = false){ // Constructor
        directed = dir;
    }
    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v];
        if(!directed) graph[v].push_back(u);
    }

    void print(){
        for(auto key:graph){
            cout << "[" << key.first << "] => ";
            for(int i = 0; i < key.second.size(); i++){
                cout << (i == 0 ? "[" : ", ");
                cout << key.second[i];
                if(i == key.second.size()-1) cout << "]";
            }
            cout << endl;
        }
    }

    void traverseDFS(int u, bool init = true){
        cout << u << ", ";
        visited[u] = true;
        record[u].first = ++time; // Record visited time
        int i = 0;
        for(auto v:graph[u]){
            if(visited[v]){
                if(record[u].first < record[v].first){
                    edges['F'].push_back(make_pair(u, v)); // Forward Edge
                } else if(record[u].first > record[v].first && pathFinder(u, v)){
                    edges['B'].push_back(make_pair(u, v)); // Back Edge
                } else {
                    edges['C'].push_back(make_pair(u, v)); // Cross Edge
                }
            } else {
                edges['T'].push_back(make_pair(u, v)); // Tree Edge
                traverseDFS(v, false);
            }
            i++;
        }
        record[u].second = ++time; // Record visiting complete time
        if(init && graph.size() != visited.size()){
            for(auto u:graph)
                if(!visited[u.first]) traverseDFS(u.first);
        }
    }

    void printRecords(){
        cout << "V  = ST\t ET" << endl;
        cout << "------------" << endl;
        for(auto v:record){
            cout << v.first << "  = ";
            auto value = v.second;
            cout << value.first << "\t " << value.second << endl;
        }
    }

    void printEdges(){
        cout << endl << "Tree Edges \tForward Edges \tBack Edges \tCross Edges" << endl;
        cout << "---------- \t------------- \t---------- \t-----------" << endl;
        int n = 0;
        for(auto edge:edges)
            if(n < edge.second.size()) n = edge.second.size();
        
        for(int i = 0; i < n; i++){
            cout << (i < edges['T'].size() ? to_string(edges['T'][i].first) + " --> " + to_string(edges['T'][i].second) : "") << "\t\t";
            cout << (i < edges['F'].size() ? to_string(edges['F'][i].first) + " --> " + to_string(edges['F'][i].second) : "") << "\t\t";
            cout << (i < edges['B'].size() ? to_string(edges['B'][i].first) + " --> " + to_string(edges['B'][i].second) : "") << "\t\t";
            cout << (i < edges['C'].size() ? to_string(edges['C'][i].first) + " --> " + to_string(edges['C'][i].second) : "") << endl;
        }
        
    }
};

int main(){
    Graph G(true);
    G.addEdge(1, 4);
    G.addEdge(4, 5);
    G.addEdge(5, 1);
    G.addEdge(4, 6);
    G.addEdge(6, 5);
    G.addEdge(1, 6);
    G.addEdge(1, 2);
    G.addEdge(2, 6);
    G.addEdge(2, 8);
    G.addEdge(8, 6);
    G.addEdge(3, 2);
    G.addEdge(3, 8);
    G.addEdge(3, 7);
    G.addEdge(7, 6);

    cout << "Adjacency List: " << endl;
    G.print();

    cout << endl << endl << "DFS: ";
    G.traverseDFS(1);

    cout << endl << endl;
    cout << "Timestamps (Start & Ending Time)" << endl;
    G.printRecords();

    cout << endl;
    G.printEdges();
}