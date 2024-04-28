#include <stdio.h>
#include <stdlib.h>

// Define a struct for Edge
struct Edge {
    int startVertex;
    int endVertex;

    Edge(int start, int end) : startVertex(start), endVertex(end) {}
};

// Define a class for Graph
class Graph {
private:
    int numVertices;
    int** adjacencyMatrix;

public:
    Graph(int numVertices) : numVertices(numVertices) {
        adjacencyMatrix = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            adjacencyMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                adjacencyMatrix[i][j] = 0; 
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    void addEdge(const Edge& edge) {
        int start = edge.startVertex;
        int end = edge.endVertex;
        adjacencyMatrix[start - 1][end - 1] = 1; // Assuming edges have weight 1
        adjacencyMatrix[end - 1][start - 1] = 1; // Undirected graph
    }

    int getNumVertices() const {
        return numVertices;
    }

    int** getAdjacencyMatrix() const {
        return adjacencyMatrix;
    }
};

// Dijkstra's algorithm implementation
void dijkstra(const Graph& graph, int startVertex) {
    int numVertices = graph.getNumVertices();
    int** adjacencyMatrix = graph.getAdjacencyMatrix();

    // Initialize distances
    int* distances = new int[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        distances[i] = 1000000; // This value is large enough to the point that it represents infinity
    }
    distances[startVertex - 1] = 0;

    // Array is used to track visited vertices
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }

    // Main loop for the program 
    for (int i = 0; i < numVertices - 1; ++i) {
        int minDistance = 1000000; // This value is large enough to the point that it represents infinity
        int minIndex = -1;

        // Find the vertex with the minimum distance
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && distances[v] < minDistance) {
                minDistance = distances[v];
                minIndex = v;
            }
        }

        // Mark minimum distance vertex as being visited
        visited[minIndex] = true;

        // Method that updates the distances to adjacent vertices
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && adjacencyMatrix[minIndex][v] && 
                distances[minIndex] != 1000000 &&
                distances[minIndex] + 1 < distances[v]) { // Assuming weight of each edge is 1
                distances[v] = distances[minIndex] + 1;
            }
        }
    }
    
    // Method to print the shortest path lengths
    printf("Single source shortest path lengths from node %d\n", startVertex);
    for (int i = 0; i < numVertices; ++i) {
        printf("  %d: %d\n", (i + 1), distances[i]);
    }
    delete[] distances;
    delete[] visited;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <graph.txt>\n", argv[0]);
        return 1;
    }
    
    //method to open file 
    FILE* infile = fopen(argv[1], "r");
    if (!infile) {
    //error managing system
        printf("Error: Unable to open file %s\n", argv[1]);
        return 1;
    }

    int numOfVertices, numOfEdges;
    fscanf(infile, "%d %d", &numOfVertices, &numOfEdges);

    Graph graph(numOfVertices);

    // Method to read edges from the file in order to populate the graph
    for (int i = 0; i < numOfEdges; ++i) {
        int startVertex, endVertex;
        fscanf(infile, "%d %d", &startVertex, &endVertex);
        Edge newEdge(startVertex, endVertex);
        graph.addEdge(newEdge);
    }

    fclose(infile);

    // Method to Print matrix
    printf("The adjacency matrix of G:\n");
    int** adjacencyMatrix = graph.getAdjacencyMatrix();
    for (int i = 0; i < numOfVertices; ++i) {
        for (int j = 0; j < numOfVertices; ++j) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    // Method to find the odd degree vertices
    printf("The odd degree vertices in G:\n");
    printf("O = { ");
    for (int i = 0; i < numOfVertices; ++i) {
        int degree = 0;
        for (int j = 0; j < numOfVertices; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                ++degree;
            }
        }
        //Dijkstra's algorithm for the odd degree vertexes
        if (degree % 2 != 0) {
            printf("%d ", (i + 1));
            dijkstra(graph, i + 1);
        }
    }
    printf("}\n");

    return 0;
}
