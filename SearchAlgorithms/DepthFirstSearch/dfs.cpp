#include <iostream>
#include <map>
#include <list>

class Graph{
public:
    void addEdge(int v,int w);
    void DFS(int v);
private:
    std::map<int, bool> visited;
    std::map<int, std::list<int>> adj;
};

void Graph::addEdge(int v,int w){
    adj[v].push_back(w);
}
void Graph::DFS(int v){
    visited[v] = true;
    std::cout << v << " ";

    std::list<int>::iterator it;
    for(it = adj[v].begin(); it!=adj[v].end();++it){
        if(!this->visited[*it]){
            DFS(*it);
        }
    }
}
int main(){
    Graph G;

    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(1,2);
    G.addEdge(2,0);
    G.addEdge(2,3);
    G.addEdge(3,3);

    std::cout << "Following is Depth First Traversal (starting from vertex 2) \n";
    G.DFS(2);

    return 0;
}