/*
 ID: 211791041, Email: lior16122000@gmail.com
*/

#pragma once
#include <vector>
#include <string>

using namespace std;
namespace ariel {
    class Graph{
        private:
        
        vector<vector<int>> _graph;
        bool _hasNegativeCycles;
        bool _hasCycles;
        int _edges;

        public:
            // Constructors
            Graph(){ 
                _hasNegativeCycles = false;
                _hasCycles = false;
                _edges = 0;
                _graph = {};
            }

            Graph(vector<vector<int>> _graph){
                Graph();
                loadGraph(_graph); 
            }
            
            // Functions:
            // Loads adjacency matrix to _graph. Returns 1 if successful, 0 if unsuccessful.
            void loadGraph(vector<vector<int>>);
            
            // Prints the _graph and the number of verices and edges in the graph.
            string printGraph() const;

            // Returns the size of _graph - the number vertices
            size_t getVertices();

            int getWeight(size_t, size_t) const;
            bool containsNegativeCycles() const;
            bool containsCycles() const;
            void setNegativeCycles();
            void setCycles();


            // Arithmetic operators
            Graph& operator+();
            Graph operator+(const Graph&);
            Graph& operator+=(const Graph&);
            Graph operator-();
            Graph operator-(const Graph&);
            Graph& operator-=(const Graph&);

            // Comparison operators
            bool operator==(const Graph&) const;
            bool operator!=(const Graph&) const;
            bool operator>(const Graph&) const;
            bool operator>=(const Graph&) const;
            bool operator<(const Graph&) const;
            bool operator<=(const Graph&) const;

            // Increment and decrement operators
            Graph& operator++(); // Prefix increment
            Graph& operator--(); // Prefix decrement
            Graph operator++(const int); // Postfix increment
            Graph operator--(const int); // Postfix decrement

            // Scalar multiplication
            Graph& operator*(const int scalar);
            Graph& operator*=(const int scalar);
            Graph& operator/(const int scalar);
            Graph& operator/=(const int scalar);

            // Graph multiplication
            Graph& operator*(const Graph&);

            // Output operator
            friend std::ostream& operator<<(std::ostream&, const Graph&);
    };
}