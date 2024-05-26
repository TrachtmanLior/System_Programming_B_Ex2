/*
 ID: 211791041, Email: lior16122000@gmail.com
*/

#include "Graph.hpp"
#include <iostream>
#include <string>
#include <ostream>

using namespace std;
namespace ariel {
    void Graph::loadGraph(vector<vector<int>> inputGraph) {
        // Check if the input graph is square
        for (size_t i = 0; i < inputGraph.size(); i++) {
            if (inputGraph[i].size() != inputGraph.size()) {
                throw invalid_argument("Invalid inputGraph: The inputGraph is not a square matrix.");
            }
        }
        // Initialize the graph and flags
        _graph = inputGraph;
        _hasNegativeCycles = false;
        _hasCycles = false;
    }

    std::string Graph::printGraph() const{
        std::string result;

        // Generate string representation of the graph
        for (size_t i = 0; i < _graph.size(); i++) {
            result += "[";
            for (size_t j = 0; j < _graph[i].size(); j++) {
                result += std::to_string(_graph[i][j]);
                if (j < _graph[i].size() - 1) {
                    result += ", ";
                }
            }
            result += "]";
            if (i < _graph.size() - 1) {
                result += "\n";
            }
        }

        return result;
    }


    int Graph::getWeight(size_t ver1, size_t ver2) const{
        // Get the weight of an edge between two vertices
        return _graph[ver1][ver2];   
    }

    size_t Graph::getVertices(){
        // Get the number of vertices in the graph
        return _graph.size();
    }
    bool Graph::containsNegativeCycles() const{
        // Check if the graph contains negative cycles
        return _hasNegativeCycles;
    }
    bool Graph::containsCycles() const{
        // Check if the graph contains cycles
        return _hasCycles;
    }
    void Graph::setNegativeCycles(){
        // Set flags indicating the presence of cycles and negative cycles
        _hasCycles = true;
        _hasNegativeCycles = true;
    }
        void Graph::setCycles(){
        // Set a flag indicating the presence of cycles
        _hasCycles = true;
    }

    // Arithmetic operators

    // Unary plus operator (+inputGraph)
    Graph& Graph::operator+() {
        // No change needed, return a reference to the current graph
        return *this;
    }

    // Binary plus operator (graph1 + graph2)
    Graph Graph::operator+(const Graph& inputGraph) {
        // Check if graphs have the same size
        if (_graph.size() != inputGraph._graph.size() || _graph[0].size() != inputGraph._graph[0].size()) {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        Graph result;
        vector<vector<int>> resultMatrix(_graph.size(), vector<int>(_graph[0].size(), 0));

        // Perform element-wise addition of the two graphs
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[0].size(); j++) {
                resultMatrix[i][j] = _graph[i][j] + inputGraph._graph[i][j];
            }
        }

        result.loadGraph(resultMatrix);
        return result;
    }

    // Compound assignment plus operator (graph1 += graph2)
    Graph& Graph::operator+=(const Graph& inputGraph) {
        // Perform addition and update the current graph
        *this = *this + inputGraph;
        return *this;
    }

    // Unary minus operator (-inputGraph)
    Graph Graph::operator-() {
        // Negate each element of the graph
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[i].size(); j++) {
                _graph[i][j] = -_graph[i][j];
            }
        }
        // Return a reference to the current graph object
        return *this;
    }

    // Binary minus operator (graph1 - graph2)
    Graph Graph::operator-(const Graph& inputGraph) {
        // Check if graphs have the same size
        if (_graph.size() != inputGraph._graph.size() || _graph[0].size() != inputGraph._graph[0].size()) {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        Graph result;
        vector<vector<int>> resultMatrix(_graph.size(), vector<int>(_graph[0].size(), 0));

        // Perform element-wise subtraction of the two graphs
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[0].size(); j++) {
                resultMatrix[i][j] = _graph[i][j] - inputGraph._graph[i][j];
            }
        }

        result.loadGraph(resultMatrix);
        return result;
    }

    // Compound assignment minus operator (graph1 -= graph2)
    Graph& Graph::operator-=(const Graph& inputGraph) {
        // Perform subtraction and update the current graph
        *this = *this - inputGraph;
        return *this;
    }


    // Comparison operators

    bool Graph::operator==(const Graph& inputGraph) const {
        // Check if graphs are equal
        if (_graph.size() != inputGraph._graph.size() || _graph[0].size() != inputGraph._graph[0].size()){
            return false;
        }

        for(size_t i=0; i< _graph.size(); i++){
            for(size_t j=0; j<_graph[0].size(); j++){
                if(_graph[i][j] != inputGraph._graph[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    bool Graph::operator!=(const Graph& inputGraph) const {
        // Check if graphs are not equal
        return !(*this == inputGraph);
    }

    // Check if graph1 is greater than graph2
    bool Graph::operator>(const Graph& inputGraph) const {
        // Compare graphs based on elements and number of edges
        if(this->_graph >= inputGraph._graph || _edges > inputGraph._edges){
            return true;
        }
        // Iterate over each element and compare
        for(size_t i=0; i< _graph.size(); i++){
            for(size_t j=0; j<_graph[0].size(); j++){
                if(_graph[i][j] <= inputGraph._graph[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    // Check if graph1 is greater than or equal to graph2
    bool Graph::operator>=(const Graph& inputGraph) const {
        // Iterate over each element and compare
        for(size_t i=0; i< _graph.size(); i++){
                for(size_t j=0; j<_graph[0].size(); j++){
                    if(_graph[i][j] < inputGraph._graph[i][j]){
                        return false;
                    }
                }
            }
        return true;
    }

    // Check if graph1 is less than graph2
    bool Graph::operator<(const Graph& inputGraph) const {
        // Compare graphs based on elements and number of edges
        if(this->_graph <= inputGraph._graph || _edges < inputGraph._edges){
            return true;
        }
        // Iterate over each element and compare
        for(size_t i=0; i< _graph.size(); i++){
            for(size_t j=0; j<_graph[0].size(); j++){
                if(_graph[i][j] >= inputGraph._graph[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    // Check if graph1 is less than or equal to graph2
    bool Graph::operator<=(const Graph& inputGraph) const {
        // Iterate over each element and compare
        for(size_t i=0; i< _graph.size(); i++){
                for(size_t j=0; j<_graph[0].size(); j++){
                    if(_graph[i][j] > inputGraph._graph[i][j]){
                        return false;
                    }
                }
            }
        return true;
    }

    // Increment and decrement operators

    // Pre-increment operator (++inputGraph)
    Graph& Graph::operator++() {
        // Increment each edge weight by 1
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[0].size(); j++) {
                _graph[i][j] = _graph[i][j] + 1;
                }
            }
        return *this;
    }

    // Pre-decrement operator (--inputGraph)
    Graph& Graph::operator--() {
        // Decrement each edge weight by 1
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[0].size(); j++) {
                _graph[i][j] = _graph[i][j] - 1;
                }
            }
        return *this;
    }

    // Post-increment operator (inputGraph++)
    Graph Graph::operator++(const int) {
        // Create a temporary copy of the graph, increment the original, and return the copy
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    // Post-decrement operator (inputGraph--)
    Graph Graph::operator--(const int) {
        // Create a temporary copy of the graph, decrement the original, and return the copy
        Graph temp = *this;
        --(*this);
        return temp;
    }

    // Scalar multiplication

    // Scalar multiplication operator (inputGraph * scalar)
    Graph& Graph::operator*(const int scalar) {
        // Multiply each edge weight by the scalar
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[i].size(); j++) {
                _graph[i][j] = _graph[i][j] * scalar;
            }
        }

        return *this;
    }

    // Compound assignment scalar multiplication operator (inputGraph *= scalar)
    Graph& Graph::operator*=(const int scalar) {
        // Multiply each edge weight by the scalar
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[i].size(); j++) {
                _graph[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Scalar division

    // Scalar division operator (inputGraph / scalar)
    Graph& Graph::operator/(const int scalar){
        // Divide each edge weight by the scalar
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[i].size(); j++) {
                _graph[i][j] /= scalar;
            }
        }
        return *this;
    }

    // Compound assignment scalar division operator (inputGraph /= scalar)
    Graph& Graph::operator/=(const int scalar){
        // Divide each edge weight by the scalar
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[i].size(); j++) {
                _graph[i][j] = _graph[i][j] / scalar;
            }
        }
        return *this;
    }

    // Matrix multiplication

    // Matrix multiplication operator (inputGraph1 * inputGraph2)
    Graph& Graph::operator*(const Graph& inputGraph) {
        // Check if graphs have the same size for multiplication
        if (_graph.size() != inputGraph._graph.size() || _graph[0].size() != inputGraph._graph[0].size()) {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        // Initialize result matrix with appropriate dimensions
        vector<vector<int>> resultMatrix(_graph.size(), vector<int>(_graph[0].size(), 0));

        // Perform matrix multiplication
        for (size_t i = 0; i < _graph.size(); i++) {
            for (size_t j = 0; j < _graph[i].size(); j++) {
                for(size_t k = 0; k < _graph[i].size(); k++){
                    resultMatrix[i][j] += _graph[i][k] * inputGraph._graph[k][j];
                }
            }
        }

        // Load the result matrix into the current graph
        this->loadGraph(resultMatrix);

        return *this;
    }

    // Output operator

    // Output operator to print the graph
    ostream& operator<<(ostream& os_stream, const Graph& inputGraph) {
        //print graph
        return os_stream << inputGraph.printGraph();
    }
}
