# Dijkstra's Algorithm on an Undirected Graph

## Overview

This project implements **Dijkstra's algorithm** to find the shortest paths from vertices with odd degrees in an undirected graph. The graph is represented using an adjacency matrix, and edges are assumed to have a uniform weight of 1.

### Key Features:
- **Graph Representation**: The graph is represented as an adjacency matrix.
- **Dijkstra's Algorithm**: Finds the shortest path from vertices with odd degrees to all other vertices.
- **Edge Handling**: Edges are read from an input file, and the program processes them as undirected and unweighted (weight = 1).
- **Odd Degree Detection**: The program detects vertices with odd degrees and applies Dijkstra's algorithm to them.

## Files

- **main.cpp**: Contains the main logic of the program.
- **input.txt**: Input file specifying the number of vertices, edges, and the edges themselves (format explained below).

## Input File Format

The input file must have the following format:

1. The first line contains two integers:
   - `n`: the number of vertices.
   - `m`: the number of edges.

2. The next `m` lines each contain two integers representing an edge between two vertices `u` and `v`.

### Example:

For a graph with 5 vertices and 6 edges:

5 6 1 2 1 3 2 3 3 4 4 5 5 1


## Output

- The program first prints the **adjacency matrix** of the graph.
- It then detects vertices with **odd degrees** and prints the shortest paths from these vertices using **Dijkstra's algorithm**.



