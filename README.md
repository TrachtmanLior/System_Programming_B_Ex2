# Graph Operations Library

This library provides implementations for various operations on graphs, including arithmetic operations, comparison operators, increment/decrement operations, scalar multiplication/division, graph multiplication, and output operations. 

## Operators

### Arithmetic Operators

- Unary Plus (+)
- Binary Plus (+)
- Compound Binary Plus (+=)
- Unary Minus (-)
- Compound Binary Plus (-)
- Binary Minus (-=)

### Comparison Operators

- Equal (==)
- Not Equal (!=)
- Greater Than (>)
- Greater Than or Equal To (>=)
- Less Than (<)
- Less Than or Equal To (<=)

### Increment and Decrement Operators

- Prefix Increment (++)
- Prefix Decrement (--)
- Postfix Increment (++)
- Postfix Decrement (--)

### Scalar Operations

- Multiplication by Integer Scalar (*)
- Compound Assignment Scalar Multiplication (*=)
- Scalar Division (/)
- Compound Assignment Scalar Division (/=)

### Graph Multiplication

- Graph Multiplication (*)

### Output Operator

- Output Operator (<<)

## Code Structure

The codebase is divided into two main files:

1. **Graph.hpp / Graph.cpp**
   - Contains the implementation of the `Graph` class.
   - Provides functionalities to load adjacency matrices, print graphs, get weights of edges, check for negative cycles, and set cycle flags, and the following operations:
     - Arithmetic
     - Comparison
     - Increment and decrement
     - Scalar and graph multiplication
     - Output

## Usage

To use this library, include the `Graph.hpp` header file in your C++ code. Make sure to instantiate the `Graph` class and utilize the provided operators according to your requirements.

Example usage:

```cpp
#include "Graph.hpp"
#include <iostream>

using namespace ariel;

int main() {
    // Create two graphs
    Graph graph1({{1, 2}, {3, 4}});
    Graph graph2({{5, 6}, {7, 8}});

    // Perform operations
    Graph result = graph1 + graph2;
    std::cout << "Result of addition: " << result << std::endl;

    // Other operations work similarly...
    
    return 0;
}
