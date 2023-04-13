#ifndef BFS_HPP_
#define BFS_HPP_

#include<iostream>
#include <queue>
#include <vector>
// Structure to store in graph
struct Edge{
    int src, dest;
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    std::vector<std::vector<int>> adjList;
 
    // Graph Constructor
    Graph(const std::vector<Edge>& evec, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);
 
        // add edges to the undirected graph
        for (const auto &edge: evec){
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};

// Perform BFS iteratively on the graph
inline void iterativeBFS(const Graph& graph, int v, std::vector<bool>& discovered)
{
    // create a queue for doing BFS
    std::queue<int> q;
 
    // mark the source vertex as discovered
    discovered[v] = true;
 
    // enqueue source vertex
    q.push(v);
 
    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and print it
        v = q.front();
        q.pop();
        std::cout << v << " ";
 
        // do for every edge (v, u)
        for (int u: graph.adjList[v])
        {
            if (!discovered[u])
            {
                // mark it as discovered and enqueue it
                discovered[u] = true;
                q.push(u);
            }
        }
    }
}

// Perform BFS recursively on the graph
inline void recursiveBFS(const Graph& graph, std::queue<int>& q, std::vector<bool>& discovered)
{
    if (q.empty()) {
        return;
    }
 
    // dequeue front node and print it
    int v = q.front();
    q.pop();
    std::cout << v << " ";
 
    // do for every edge (v, u)
    for (int u: graph.adjList[v])
    {
        if (!discovered[u])
        {
            // mark it as discovered and enqueue it
            discovered[u] = true;
            q.push(u);
        }
    }

    recursiveBFS(graph, q, discovered);
}

#endif