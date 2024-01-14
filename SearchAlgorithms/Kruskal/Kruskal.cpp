#include "Kruskal.hpp"
 
int main() { 
    std::size_t V = 9, E = 14; 
    Graph g(V, E); 
  
    g.add_edge(0, 1, 4); 
    g.add_edge(0, 7, 8); 
    g.add_edge(1, 2, 8); 
    g.add_edge(1, 7, 11); 
    g.add_edge(2, 3, 7); 
    g.add_edge(2, 8, 2); 
    g.add_edge(2, 5, 4); 
    g.add_edge(3, 4, 9); 
    g.add_edge(3, 5, 14); 
    g.add_edge(4, 5, 10); 
    g.add_edge(5, 6, 2); 
    g.add_edge(6, 7, 1); 
    g.add_edge(6, 8, 6); 
    g.add_edge(7, 8, 7); 
  
    std::cout << "Edges of MST are \n"; 
    int mst_wt = g.kruskalMST(); 
  
    std::cout << "\nWeight of MST is " << mst_wt; 
} 