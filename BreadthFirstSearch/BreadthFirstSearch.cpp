#include "BreadthFirstSearch.hpp"

int main(){
    // vector of graph edges as per the above diagram
    std::vector<Edge> edges = {
        {1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {5, 9},
        {5, 10}, {4, 7}, {4, 8}, {7, 11}, {7, 12}
        // vertex 0, 13, and 14 are single nodes
    };
 
    // total number of nodes in the graph (labelled from 0 to 14)
    int n = 15;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // to keep track of whether a vertex is discovered or not
    std::vector<bool> discovered(n, false);
 
    // Perform BFS traversal from all undiscovered nodes to
    // cover all connected components of a graph
    for (int i = 0; i < n; i++)
    {
        if (discovered[i] == false)
        {
            // start BFS traversal from vertex `i`
            iterativeBFS(graph, i, discovered);
        }
    }
    std::cout<<"\n";

    std::vector<bool> recdiscovered(n, false);
 
    // create a queue for doing BFS
    std::queue<int> recq;
 
    // Perform BFS traversal from all undiscovered nodes to
    // cover all connected components of a graph
    for (int i = 0; i < n; i++)
    {
        if (recdiscovered[i] == false)
        {
            // mark the source vertex as discovered
            recdiscovered[i] = true;
 
            // enqueue source vertex
            recq.push(i);
 
            // start BFS traversal from vertex `i`
            recursiveBFS(graph, recq, recdiscovered);
        }
    }
}