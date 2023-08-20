/** 
Ref: https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/

The Floyd Warshall Algorithm is for solving all pairs of shortest-path problems.
The problem is to find the shortest distances between every pair of vertices in a
given edge-weighted directed Graph.

Input:  graph[][] = { {0,   5,  INF, 10},
                               {INF,  0,  3,  INF},
                               {INF, INF, 0,   1},
                               {INF, INF, INF, 0} }
which represents the following graph
             10
      (0)——->(3)
        |              /|\
     5 |               |  1
        |               |
       \|/             |
      (1)——->(2)
              3
Output: Shortest distance matrix
 0       5      8       9
 INF     0      3       4
 INF     INF    0       1
 INF     INF    INF     0
*/
#include <iostream>
#include <cstddef>
#include <limits>
#include <vector>
#include <algorithm>
#include <exception>

using graph_type = std::vector<std::vector<int>>;
constexpr int INF = std::numeric_limits<int>::max();

std::ostream& dash_line(std::ostream& os)
{
	return os << "\n--------------------------\n";
}

void printSolution(graph_type dist);
void floydWarshall(graph_type dist){
    if(std::any_of(dist.begin(), dist.end(), [dist_size = dist.size()](const auto& vec){return vec.size() != dist_size;})){
        throw std::runtime_error{"Unmatched Graph Size."};
    }

    /* Add all vertices one by one to
    the set of intermediate vertices.
    ---> Before start of an iteration,
    we have shortest distances between all
    pairs of vertices such that the
    shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as
    intermediate vertices.
    ----> After the end of an iteration,
    vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, ..
    k} */
    for (std::size_t k = 0; k < dist.size(); ++k) {
        // Pick all vertices as source one by one
        for (std::size_t i = 0; i < dist.size(); ++i) {
            // Pick all vertices as destination for the
            // above picked source
            for (std::size_t j = 0; j < dist.size(); ++j) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of
                // dist[i][j]
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INF
                        && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 
    // Print the shortest distance matrix
    printSolution(dist);
}

void printSolution(graph_type dist){
    std::cout << "The following matrix shows the shortest "
            "distances"
            " between every pair of vertices" << dash_line;
    
    for (std::size_t i = 0; i < dist.size(); ++i){
        for (std::size_t j = 0; j < dist.size(); ++j){
            if (dist[i][j] == INF)
                std::cout << "INF"
                     << " ";
            else
                std::cout << dist[i][j] << "   ";
        }
        std::cout<<"\n";
    }
    std::cout << dash_line;
}

int main()
{
    graph_type graph{{0, 5, INF, 10},
                     {INF, 0, 3, INF},
                     {INF, INF, 0, 1},
                     {INF, INF, INF, 0}};

    floydWarshall(graph);
}