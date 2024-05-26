#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream>

using namespace std;

// Test case for graph addition
TEST_CASE("Test graph addition")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    
    // Creating graph g2 and loading weighted graph data into it
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    
    // Adding g1 and g2 to form g3
    ariel::Graph g3 = g1 + g2;
    // Expected resulting graph after addition
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    // Checking if the resulting graph matches the expected graph
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

// Test case for graph multiplication
TEST_CASE("Test graph multiplication")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    
    // Creating graph g2 and loading weighted graph data into it
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    
    // Multiplying g1 and g2 to form g4
    ariel::Graph g4 = g1 * g2;
    // Expected resulting graph after multiplication
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    // Checking if the resulting graph matches the expected graph
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}

// Test case for invalid operations
TEST_CASE("Invalid operations")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    
    // Creating graph g2 and loading invalid weighted graph data into it
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    // Checking if loading such data into g2 throws an exception
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    
    // Creating graph g5 and loading graph data into it
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    // Checking if multiplying g5 with g1 throws an exception
    CHECK_THROWS(g5 * g1);
    // Checking if multiplying g1 with g2 throws an exception
    CHECK_THROWS(g1 * g2);

    // Creating graph g6 and loading graph data with different dimensions into it
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    // Checking if adding g1 with g6 throws an exception due to mismatched dimensions
    CHECK_THROWS(g1 + g6);
}

// Test case for unary plus operator on a graph
TEST_CASE("Test graph unary plus operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Applying unary plus operator on g1 to create g2
    ariel::Graph g2 = +g1;
    // Checking if g2 is identical to g1
    CHECK(g2.printGraph() == g1.printGraph());
}

// Test case for unary minus operator on a graph
TEST_CASE("Test graph unary minus operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, -2, 3},
        {-4, 5, -6},
        {7, -8, 9}};
    g1.loadGraph(graph1);
    
    // Applying unary minus operator on g1 to create g2
    ariel::Graph g2 = -g1;
    // Expected resulting graph after applying unary minus operator
    vector<vector<int>> expectedGraph = {
        {-1, 2, -3},
        {4, -5, 6},
        {-7, 8, -9}};
    // Checking if the resulting graph matches the expected graph
    CHECK(g2.printGraph() == "[-1, 2, -3]\n[4, -5, 6]\n[-7, 8, -9]");
}

// Test case for equality operator on two graphs
TEST_CASE("Test graph equality operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading graph data identical to g1 into it
    ariel::Graph g2;
    g2.loadGraph(graph1);
    
    // Checking if g1 is equal to g2
    CHECK(g1 == g2);
}

// Test case for inequality operator on two graphs
TEST_CASE("Test graph inequality operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading different graph data into it
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}};
    g2.loadGraph(graph2);
    
    // Checking if g1 is not equal to g2
    CHECK(g1 != g2);
}

// Test case for greater than operator on two graphs
TEST_CASE("Test graph greater than operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading different graph data into it
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g2.loadGraph(graph2);
    
    // Checking if g1 is greater than g2
    CHECK(g1 > g2);
}

// Test case for greater than or equal to operator on two graphs
TEST_CASE("Test graph greater than or equal to operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading identical graph data to g1 into it
    ariel::Graph g2;
    g2.loadGraph(graph1);
    
    // Checking if g1 is greater than or equal to g2
    CHECK(g1 >= g2);
}

// Test case for less than operator on two graphs
TEST_CASE("Test graph less than operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading different graph data into it
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11}};
    g2.loadGraph(graph2);
    
    // Checking if g1 is less than g2
    CHECK(g1 < g2);
}

// Test case for less than or equal to operator on two graphs
TEST_CASE("Test graph less than or equal to operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading different graph data into it
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g2.loadGraph(graph2);
    
    // Checking if g2 is less than or equal to g1
    CHECK(g2 <= g1);
}

// Test case for prefix increment operator on a graph
TEST_CASE("Test graph prefix increment operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}};
    g1.loadGraph(graph1);
    
    // Applying prefix increment operator on g1
    ++g1;
    // Expected resulting graph after applying prefix increment operator
    vector<vector<int>> expectedGraph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    // Checking if the resulting graph matches the expected graph
    CHECK(g1.printGraph() == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]");
}

// Test case for postfix increment operator on a graph
TEST_CASE("Test graph postfix increment operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}};
    g1.loadGraph(graph1);
    
    // Applying postfix increment operator on g1 and assigning the result to g2
    ariel::Graph g2 = g1++;
    // Expected resulting graph after applying postfix increment operator
    vector<vector<int>> expectedGraph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    // Checking if the resulting graph and the original graph match the expected graph
    CHECK(g1.printGraph() == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]");
    CHECK(g2.printGraph() == "[0, 1, 2]\n[3, 4, 5]\n[6, 7, 8]");
}

// Test case for prefix decrement operator on a graph
TEST_CASE("Test graph prefix decrement operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Applying prefix decrement operator on g1
    --g1;
    // Expected resulting graph after applying prefix decrement operator
    vector<vector<int>> expectedGraph = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}};
    // Checking if the resulting graph matches the expected graph
    CHECK(g1.printGraph() == "[0, 1, 2]\n[3, 4, 5]\n[6, 7, 8]");
}

// Test case for postfix decrement operator on a graph
TEST_CASE("Test graph postfix decrement operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Applying postfix decrement operator on g1 and assigning the result to g2
    ariel::Graph g2 = g1--;
    // Expected resulting graph after applying postfix decrement operator
    vector<vector<int>> expectedGraph = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}};
    // Checking if the resulting graph and the original graph match the expected graph
    CHECK(g1.printGraph() == "[0, 1, 2]\n[3, 4, 5]\n[6, 7, 8]");
    CHECK(g2.printGraph() == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]");
}

// Test case for chaining multiple operations on graphs
TEST_CASE("Test chaining multiple operations")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading different graph data into it
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}};
    g2.loadGraph(graph2);
    
    // Creating graph g3 and loading graph data into it
    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g3.loadGraph(graph3);
    
    // Applying multiple operations on graphs g1, g2, and g3, and assigning the result to result
    ariel::Graph result = ((g1 + g2) - g3) * 2;
    // Expected resulting graph after chaining the operations
    vector<vector<int>> expectedGraph = {
        {18, 16, 12},
        {18, 16, 12},
        {18, 16, 12}};
    // Checking if the resulting graph matches the expected graph
    CHECK(result.printGraph() == "[18, 18, 18]\n[18, 18, 18]\n[18, 18, 18]");
}

// Test case for identity property of graph addition
TEST_CASE("Test identity property of graph addition")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Creating a zero graph with the same dimensions as g1
    ariel::Graph zeroGraph;
    vector<vector<int>> zeroMatrix = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    zeroGraph.loadGraph(zeroMatrix);
    
    // Performing addition of g1 and the zero graph
    ariel::Graph result = g1 + zeroGraph;
    // Checking if the result matches g1, which demonstrates the identity property
    CHECK(result.printGraph() == g1.printGraph());
}

// Test case for graph scalar multiplication
TEST_CASE("Test graph scalar multiplication")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Performing scalar multiplication of g1 with 2
    ariel::Graph g2 = g1 * 2;
    // Expected resulting graph after scalar multiplication
    vector<vector<int>> expectedGraph = {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}};
    // Checking if the result matches the expected graph
    CHECK(g2.printGraph() == "[2, 4, 6]\n[8, 10, 12]\n[14, 16, 18]");
}

// Test case for graph multiplication with another graph
TEST_CASE("Test graph multiplication with another graph")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and loading different graph data into it
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}};
    g2.loadGraph(graph2);
    
    // Performing multiplication of g1 with g2
    ariel::Graph g3 = g1 * g2;
    // Expected resulting graph after multiplication
    vector<vector<int>> expectedGraph = {
        {18, 14, 10},
        {96, 77, 58},
        {174, 140, 106}};
    // Checking if the result matches the expected graph
    CHECK(g3.printGraph() == "[30, 24, 18]\n[84, 69, 54]\n[138, 114, 90]");
}

// Test case for scalar multiplication with commutativity
TEST_CASE("Test scalar multiplication with commutativity")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Performing scalar multiplication of g1 with 2
    ariel::Graph g2 = g1 * 2;

    // Creating graph g3 with the same data as the expected result of g1 * 2
    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {4, 8, 12},
        {16, 20, 24},
        {28, 32, 36}};
    g3.loadGraph(graph2);
    // Performing division of g3 by 2
    ariel::Graph g4 = g3 / 2;
    
    // Checking if the result of g1 * 2 matches the result of g3 / 2, demonstrating commutativity
    CHECK(g2.printGraph() == g4.printGraph());
}

// Test case for graph output operator
TEST_CASE("Test graph output operator")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Creating a stringstream object to capture the output of g1
    stringstream ss;
    ss << g1;
    
    // Checking if the stringstream content matches the expected string representation of g1
    CHECK(ss.str() == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]");
}

// Test case for graph self-assignment
TEST_CASE("Test graph self-assignment")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Assigning g1 to itself
    g1 = g1;
    // Checking if g1 remains unchanged after self-assignment
    CHECK(g1.printGraph() == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]");
}

// Test case for graph copy assignment
TEST_CASE("Test graph copy assignment")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 and assigning g1 to it
    ariel::Graph g2;
    g2 = g1;
    // Checking if g2 has the same data as g1 after copy assignment
    CHECK(g2.printGraph() == g1.printGraph());
}

// Test case for graph copy constructor
TEST_CASE("Test graph copy constructor")
{
    // Creating graph g1 and loading graph data into it
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph1);
    
    // Creating graph g2 using the copy constructor and initializing it with g1
    ariel::Graph g2(g1);
    // Checking if g2 has the same data as g1 after copy construction
    CHECK(g2.printGraph() == g1.printGraph());
}
