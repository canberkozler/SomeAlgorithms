#include <limits>
#include <utility>
#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <iostream>

using iPair = std::pair<int, int>;

class Graph {
public:
    //0x3f3f3f3f for INF?
    enum { INF=std::numeric_limits<int>::max() };

    Graph(int N_) : N{ N_ }, adj{ new std::list<iPair>[N] } {}
    ~Graph() {
        delete adj;
    }

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // Dijkstra Algorithm
    void shortestPath(int src){
        std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;
        std::vector<int> dist(N, INF);
        dist[src] = 0;
        std::list<iPair>::iterator it;

        pq.emplace(0, src);
        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            for (it = adj[u].begin(); it != adj[u].end(); ++it)
            {
                int v = it->first;
                int w = it->second;
                if (dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        for (int i = 0; i < N; i++){
            std::cout << i << " -> " << dist[i] << "\n";
        }
    }

private:
    int N;
    std::list<iPair>* adj;
};

int main() {
    int N = 5;
    Graph g(N);
    g.addEdge(0,0,2);
    g.addEdge(1,0,3);
    g.addEdge(1,1,5);
    g.addEdge(0,1,2);
    g.addEdge(2,1,4);
    g.addEdge(3,1,4);
    g.addEdge(4,1,4);
    g.addEdge(4,2,10);
    g.addEdge(4,3,1);
    g.addEdge(4,4,4);
    int src = 0;
    g.shortestPath(src);
    return 0;
}