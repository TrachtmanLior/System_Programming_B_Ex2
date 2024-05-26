/*
 ID: 211791041, Email: lior16122000@gmail.com
*/

#pragma once
#include "Graph.hpp"
#include <string>

using namespace std;
namespace ariel{
    class Algorithms{
    private:
        /*
         * Runs the Bellman Ford Algorithm on the graph from a given start vertex.
         * Returns a vector of distances from the start vertex to all other vertices,
         * or empty vector if a cycle is detected.
         */
        static vector<size_t> bellmanFordAlgo(Graph&, size_t);

        /*
         * Attempts to relax all the edges in the graph once.
         * Updates distance and path vectors accordingly.
         * Returns the number of edges relaxed.
         */
        static int relax(Graph, vector<int>&, vector<size_t>&);

        /*
         * Helper function for DFS traversal to detect cycles.
         * Visits each vertex and detects cycles recursively.
         * Returns true if a cycle is detected, otherwise returns false.
         */
        static bool dfs(Graph, size_t, vector<bool>&, vector<size_t>&, vector<size_t>&);

    public:
         /*
         * Checks if the given graph is connected.
         * Returns 1 if the graph is connected, otherwise returns 0.
         */
        static bool isConnected(Graph);

        /*
         * Finds the shortest path between two vertices in the graph.
         * Returns the path as a string, or -1 if no path exists.
         */
        static string shortestPath(Graph, size_t, size_t);


        /*
         * Checks if the graph contains any cycles.
         * Returns a string representing a cycle if found, otherwise returns 0.
         */
        static string isContainsCycle(Graph);

        /*
         * Checks if the graph is bipartite.
         * Returns a string representing the bipartition if possible, otherwise returns 0.
         * Utilizes BFS to partition the vertices into two sets.
         */
        static string isBipartite(Graph);

        /*
         * Checks for the presence of a negative cycle in the graph.
         * Prints the cycle if found and returns 1, otherwise returns 0.
         */ 
        static string negativeCycle(Graph);
    };
}