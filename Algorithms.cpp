/*
 ID: 211791041, Email: lior16122000@gmail.com
*/

#include <stack>
#include "Algorithms.hpp"
#include <iostream>
#include <string>
#include <queue>

#define INT32_MIN -2147483648
#define INT32_MAX 2147483647

using namespace std;
namespace ariel{
    bool Algorithms::isConnected(Graph graph) {
        // If the graph has 0 or 1 vertices, it is connected
        if (graph.getVertices() <= 1) {
            return true;
        }

        // otherwise, run DFS
        // Initialize a vector to store if a vertex was visited or not
        vector<bool> visited(graph.getVertices(), false); 
        stack<size_t> verticeStack;
        // Start from the first vertex
        verticeStack.push(0);

        while (!verticeStack.empty()) {
            size_t vertice = verticeStack.top();
            verticeStack.pop();

            visited[vertice] = true;        // set as visited

            // add all the neighbors that weren't visited to the verticeStack
            for (size_t adj = 0; adj < graph.getVertices(); adj++) {
                if (graph.getWeight(vertice, adj) != 0 && !visited[adj]) { // Check if there's an edge and if the adj was not visited yet
                    verticeStack.push(adj);
                }
            }
        }

        // make sure all vertices were visited
        for (size_t vertice = 0; vertice < visited.size(); vertice++){
            if (!visited[vertice]) {
                return false;
            }
        }

        return true;
    }


    string Algorithms::shortestPath(Graph graph, size_t start, size_t end){
        // If the graph has 0 or 1 vertices, there is no path
        if (graph.getVertices() <= 1) {
            return "-1";
        }
        // otherwise:
        // find the shortest path using Bellman Ford Algorithm, from start vertex
        vector<size_t> path = bellmanFordAlgo(graph, start);

        // make sure there are no cycles - negative or positive
        if (graph.containsNegativeCycles() || isContainsCycle(graph) == "1"){
            return "-1";
        }

        // If the end vertex is not reachable from the start vertex, return -1
        if (path.empty() || (path[end] == INT32_MIN || path[end] == INT32_MAX || path[end] == 0)) {
            return "-1";
        }

        // Build the path string
        string result = to_string(end);
        // Start from the end vertex and go back to the start vertex
        size_t vertice = end;
        while (path[vertice] != start) {
            vertice = path[vertice];
            result.insert(0, to_string(vertice) + "->");
        }
        // Add the start vertex to the path
        result.insert(0, to_string(start) + "->");
        
        return result;
    }

    string Algorithms::isBipartite(Graph graph) {
        // If the graph has 0 vertices, it is bipartite
        if (graph.getVertices() == 0) {
            return "The graph is bipartite: A={}, B={}";
        }

        // otherwise, run BFS
        // Initialize a vector to store the color of each vertex
        vector<string> color(graph.getVertices(), "WHITE");
        // Initialize two vectors to store the vertices of each set
        vector<size_t> coloredBlue;
        vector<size_t> coloredRed;

        for (size_t vertice = 0; vertice < graph.getVertices(); vertice++) {
            if (color[vertice] == "WHITE") {
                queue<size_t> verticeQueue;
                color[vertice] = "BLUE";    // default color for the starting vertex
                // add the starting vertex to the coloredBlue set
                coloredBlue.push_back(vertice);
                 // push starting vertex to verticeQueue
                verticeQueue.push(vertice); 

                while (!verticeQueue.empty()) {
                    size_t vertice = verticeQueue.front();
                    verticeQueue.pop();

                    for (size_t adj = 0; adj < graph.getVertices(); adj++) {
                        if (graph.getWeight(vertice, adj) != 0) {
                            if (color[adj] == "WHITE") {
                                // if the adjacent vertex is not colored,
                                // color it the opposite color of the current vertex and add it to the queue
                                if(color[vertice] == "BLUE"){
                                    color[adj] = "RED";
                                }
                                else {
                                    color[adj] = "BLUE";
                                }
                                verticeQueue.push(adj);

                                // add the adjacent vertex to the set
                                if (color[adj] == "RED") {
                                    coloredRed.push_back(adj);
                                } else {
                                    coloredBlue.push_back(adj);
                                }
                            } else if (color[adj] == color[vertice]) {
                                // the graph is not bipartite because the adjacent vertex is already colored with the same color as the current vertex,
                                return "0";
                            }
                        }
                    }
                }
            }
        }

        // Graph is bipartite - Build the result string and return the two sets
        string result;
        result += "The graph is bipartite: A={";
        for (size_t vertice = 0; vertice < coloredBlue.size(); vertice++) {
            result += to_string(coloredBlue[vertice]);
            if (vertice < coloredBlue.size() - 1) {
                result += ", ";
            }
        }
        result += "}, B={";
        for (size_t vertice = 0; vertice < coloredRed.size(); vertice++) {
            result += to_string(coloredRed[vertice]);
            if (vertice < coloredRed.size() - 1) {
                result += ", ";
            }
        }
        result += "}";

        return result;
    }

    string Algorithms::negativeCycle(Graph graph){
        bellmanFordAlgo(graph, 0);
        if(!graph.containsNegativeCycles()){
            return "The graph doesn't contain negative cycles";
        }
        return "The graph contain negative cycles";
    }

    vector<size_t> Algorithms::bellmanFordAlgo(Graph& graph, size_t source) {
        // Initialize path and distance vectors
        vector<size_t> path(graph.getVertices(), INT32_MAX);
        vector<int> distance(graph.getVertices(), INT32_MAX);

        // Set the distance of the source vertex to 0
        distance[source] = 0;

        // relax all edges V-1 times to find the shortest path
        for (int vertice = 0; vertice < graph.getVertices()-1; vertice++){
            // if no edges were relaxed in the last iteration, we can stop ahead of time
            if (relax(graph, distance, path) == 0){
                return path;  
            }
        }

        // check negative cycles
        // if there are still edges to relax, there is a negative cycle
        if (relax(graph, distance, path) != 0){
            graph.setNegativeCycles();
        }

        // If the graph contains negative cycles, return an empty vector to indicate that there is no path
        if (graph.containsNegativeCycles()){
            return vector<size_t>();
        }

        return path;
    }


    int Algorithms::relax(Graph graph, vector<int>& distance, vector<size_t>& path){
        int count = 0;
        for (size_t vertice = 0; vertice < graph.getVertices(); vertice++) {
            for (size_t adj = 0; adj < graph.getVertices(); adj++) {
                // Get the weight of the edge (vertice, adj)
                int weight = graph.getWeight(vertice, adj);
                // If the weight is 0, there is no edge between the vertices
                // otherwise, check if the distance can be updated
                if (weight != 0 && distance[vertice] != INT32_MAX && distance[vertice] + weight < distance[adj]) {
                    // Update the path to print the shortest path later
                    path[adj] = vertice;
                    // Update the distance and increase the count of changes
                    distance[adj] = distance[vertice] + weight;
                    count++;
                }
            }
        }
        return count;
    }

    bool Algorithms::dfs(Graph graph, size_t vertice, vector<bool>& visited, vector<size_t>& parent, vector<size_t>& cycle) {
        // Mark the current vertex as visited
        visited[vertice] = true;

        // Iterate over all adjacent vertices
        for (size_t adj = 0; adj < graph.getVertices(); adj++) {
            // Get the weight of the edge (vertice, adj)
            int weight = graph.getWeight(vertice, adj);

            // if the weight is not 0 and the adjacent vertex is not the parent of the current vertex
            if (weight != 0 && parent[vertice] != adj) {
                // If the vertex is visited, there is a cycle - trace it back
                if (visited[adj]) {
                    size_t cycleIndex = vertice;
                    while (cycleIndex != adj) {
                        cycle.push_back(cycleIndex);
                        cycleIndex = parent[cycleIndex];
                    }
                    cycle.push_back(adj);
                    cycle.push_back(vertice);
                    return true;    // Cycle found
                }
                // Otherwise, visit the adjacent vertex and set the parent
                parent[adj] = vertice;
                if (dfs(graph, adj, visited, parent, cycle)) {
                    return true;    // Cycle found
                }
            }
        }
        return false; // Cycle not found
    }

    string Algorithms::isContainsCycle(Graph graph) {
        // If the graph has 0 or 1 vertices, there is no cycle
        if (graph.getVertices() <= 1) {
            return "0";
        }

        // otherwise:
        // Initialize vectors to store the parent of each vertex, if it was visited or not, and the cycle
        vector<size_t> parent(graph.getVertices(), INT32_MAX);
        vector<bool> visited(graph.getVertices(), false);
        vector<size_t> cycle;

        // Run DFS to detect cycles
        for (size_t vertice = 0; vertice < graph.getVertices(); vertice++) {
            if (!visited[vertice]) {
                if (dfs(graph, vertice, visited, parent, cycle)) {
                    // cycle found (dfs func returned true) - build the result string
                    string result = "The cycle is: ";
                    size_t cycleIndex = 0;
                    for (size_t current = 0; current < cycle.size()-1; current++) {
                        result += to_string(cycle[current]) + "->";
                        cycleIndex = current+1;
                    }
                    result += to_string(cycle[cycleIndex]);
                    graph.setCycles();  // set the graph as having cycles
                    return result;
                }
            }
        }
        // ran DFS on all vertices and no cycle was found
        return "0";
    }
}
