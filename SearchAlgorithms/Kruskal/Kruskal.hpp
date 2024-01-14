#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

namespace ownType{
    using iPair = std::pair<int, int>;
}

struct DisjointSets{
    DisjointSets(std::size_t n_): n{n_}, parent(n+1), rnk(n+1, 0){  
        for (std::size_t i{}; i <= n; ++i){ 
            //every element is parent of itself 
            parent[i] = i; 
        } 
    }

    int find(int u) {
        /* Make the parent of the nodes in the path 
        from u--> parent[u] point to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
        a subtree of the other tree */
        if (rnk[x] > rnk[y])  parent[y] = x; 
        else parent[x] = y; 
  
        if (rnk[x] == rnk[y]) ++rnk[y]; 
    } 

    std::size_t n; 
    std::vector<int> parent, rnk; 
}; 

class Graph{
    std::size_t V, E; 
    std::vector<std::pair<int, ownType::iPair>> edges; 

public:
    Graph(std::size_t v, std::size_t e) : V{v}, E{e}{} 

    void add_edge(int u, int v, int w){ 
        edges.emplace_back(w, ownType::iPair{u, v}); 
    } 
  
    // Function to find MST using Kruskal's MST algorithm
    int kruskalMST(){
        int mst_wt = 0; // Initialize result

        std::sort(edges.begin(), edges.end());

        DisjointSets ds(V);

        for (auto it = edges.begin(); it != edges.end(); ++it){
            int set_u = ds.find(it->second.first);
            int set_v = ds.find(it->second.second);

            if (set_u != set_v){
                std::cout << it->second.first << " - " << it->second.second << std::endl;

                // Update MST weight
                mst_wt += it->first;

                // Merge two sets
                ds.merge(set_u, set_v);
            }
        }

        return mst_wt;
    }
}; 
  