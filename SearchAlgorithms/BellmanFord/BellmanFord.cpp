#include <vector>
#include <utility>
#include <iostream>
#include <iterator>
#include <limits>

class Graph{
public:
    using sr_tr_pair = std::pair<int,int>; //source and target IDs.
    using weight = int;
    Graph(int _N): N{_N}{}

    void addEdge(int u,int v,int w){
        edges.emplace_back(w, sr_tr_pair{u,v});
    }

    void bellmanFord(int src){
    std::vector<int> dist(N, INF); // Initialize all distances to infinity.
    dist[src] = 0; // Distance to the source vertex is 0.

    // Relax all edges N-1 times
    for (int i = 1; i <= N - 1; ++i) {
        for (const auto& edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int w = edge.first;
            if (dist[u] != INF && (dist[u] + w) < dist[v]) {
                dist[v] = dist[u] + w; // Edge relaxation
            }
        }
    }

    // Check for negative cycles
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int w = edge.first;
        if (dist[u] != INF && (dist[u] + w) < dist[v]) {
            hasNegativeCycle = true;
        }
    }

    if (!hasNegativeCycle) {
        // Print all distances from the origin to all vertices.
        for (int i = 0; i < N; ++i) {
            std::cout << i << " - " << dist[i] << '\n';
        }
    }
    }

private:
    int N;
    
    std::vector<std::pair<weight, sr_tr_pair>> edges; //list of edges, formatted <weight,source,target>
    bool hasNegativeCycle = false;
    enum { INF = std::numeric_limits<int>::max()};
};

int main(){
    int N = 5;

    Graph g(N);
    g.addEdge(0,1,7);
    g.addEdge(0,4,6);
    g.addEdge(1,2,9);
    g.addEdge(1,3,-3);
    g.addEdge(2,0,2);
    g.addEdge(2,3,7);
    g.addEdge(3,4,-2);
    g.addEdge(4,1,8);
    g.addEdge(4,2,-4);
    g.addEdge(4,3,5);

    g.bellmanFord(2);
    return 0;
}