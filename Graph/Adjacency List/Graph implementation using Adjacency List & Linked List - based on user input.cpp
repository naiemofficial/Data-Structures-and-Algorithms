#include <iostream>
#include <map>
using namespace std;

class Graph {
  private:
    struct NODE {
        int data;
        NODE *next = NULL;
    };
    void push_back(NODE *&root, int value, string test = ""){
        NODE *temp;
        if(root == NULL){
            root = temp = new NODE;
        } else {
            temp = root;
            while(temp->next) temp = temp->next;
            temp = temp->next = new NODE;
        }
        temp->data = value;
    }

    map <int, NODE*> graph;
  public:
    void addEdge(int u, int v, bool directed = false){
        push_back(graph[u], v);
        if(!directed){
            push_back(graph[v], u);
        } else {
            graph[v];
        }
    }

    void print(){
        for(auto u:graph){
            cout << "[" << u.first << "] => ";
            NODE *node = u.second;
            while(node){
                cout << (node == u.second ? "[" : ", ");
                cout << node->data;
                if(!node->next) cout << "]";
                node = node->next;
            }
            cout << endl;
        }
    }
};


int main(){
    system("clear");
    int edges = 0; int directed = 0; 
    cout << "Enter the number of edge(s): ";
    cin >> edges;

    if(edges > 0){
        cout << "Is this a directed graph? ([1]=YES/[0]=NO): ";
        cin >> directed;
        if(directed == 0 || directed == 1){
            cout << endl << "Each line will contain data for a single edge. Use space between the nodes." << endl;
            cout << "Let's start entering the data below ↴" << endl;
            Graph G;
            int u, v;
            for(int i = 0; i < edges; i++){
                cin >> u >> v;
                G.addEdge(u, v, directed);
            }
            cout << endl << "Adjacency List: " << endl;
            G.print();
        } else {
            cout << "Invalid command!" << endl;
        }
    }
}