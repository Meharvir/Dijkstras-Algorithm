#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

// Define Edge class
class Edge {
private:
    int startVertice;
    int endVertice;
public:
    Edge(int start, int end) : startVertice(start), endVertice(end) {}

    int getStart() const {
        return startVertice;
    }

    int getEnd() const {
        return endVertice;
    }
};

// Define Graph class
class Graph {
private:
    int numVertices;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    Graph(int numVertices) : numVertices(numVertices) {
        adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    }

    void addEdge(const Edge& edge) {
        int start = edge.getStart();
        int end = edge.getEnd();
        adjacencyMatrix[start - 1][end - 1] = 1; // Assuming edges have weight 1
        adjacencyMatrix[end - 1][start - 1] = 1; // Undirected graph
    }

    int getNumVertices() const {
        return numVertices;
    }

    const std::vector<std::vector<int>>& getAdjacencyMatrix() const {
        return adjacencyMatrix;
    }
};

// Dijkstra's algorithm
void dijkstra(const Graph& graph, int startVertex) {
    int numVertices = graph.getNumVertices();
    const std::vector<std::vector<int>>& adjacencyMatrix = graph.getAdjacencyMatrix();

    // Initialize distances
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    distances[startVertex - 1] = 0;

    // Array to track visited vertices
    std::vector<bool> visited(numVertices, false);

    // Main loop
    for (int i = 0; i < numVertices - 1; ++i) {
        int minDistance = std::numeric_limits<int>::max();
        int minIndex = -1;

        // Find the vertex with the minimum distance
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && distances[v] < minDistance) {
                minDistance = distances[v];
                minIndex = v;
            }
        }

        // Mark the minimum distance vertex as visited
        visited[minIndex] = true;

        // Update distances to adjacent vertices
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && adjacencyMatrix[minIndex][v] && 
                distances[minIndex] != std::numeric_limits<int>::max() &&
                distances[minIndex] + 1 < distances[v]) { // Assuming weight of each edge is 1
                distances[v] = distances[minIndex] + 1;
            }
        }
    }

    // Print shortest path lengths
    std::cout << "Single source shortest path lengths from node " << startVertex << std::endl;
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "  " << (i + 1) << ": " << distances[i] << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <graph_file.txt>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    int numOfVertices, numOfEdges;
    infile >> numOfVertices >> numOfEdges;

    Graph graph(numOfVertices);

    // Read edges from file and populate the graph
    for (int i = 0; i < numOfEdges; ++i) {
        int startVertice, endVertice;
        infile >> startVertice >> endVertice;
        Edge newEdge(startVertice, endVertice);
        graph.addEdge(newEdge);
    }

    // Print adjacency matrix
    std::cout << "The adjacency matrix of G:" << std::endl;
    const auto& adjacencyMatrix = graph.getAdjacencyMatrix();
    for (const auto& row : adjacencyMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Find odd degree vertices
    std::cout << "The odd degree vertices in G:" << std::endl;
    std::cout << "O = { ";
    for (int i = 0; i < numOfVertices; ++i) {
        int degree = 0;
        for (int j = 0; j < numOfVertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                ++degree;
            }
        }
        if (degree % 2 != 0) {
            std::cout << (i + 1) << " ";
            // Run Dijkstra's algorithm for odd degree vertex
            dijkstra(graph, i + 1);
        }
    }
    std::cout << "}" << std::endl;

    return 0;
}
