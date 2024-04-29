#include <stdio.h>
#include <stdlib.h>

// Define a struct for Edge
struct Edge
{
    int startVertex;
    int endVertex;

    Edge(int start, int end) : startVertex(start), endVertex(end) {}
};

// Define a class for Graph
class Graph
{
private:
    int numVertices;
    int **adjacencyMatrix;

public:
    // Constructor to initialize a 2d array to represent the graph
    Graph(int numVertices) : numVertices(numVertices)
    {
        // Allocate memory
        adjacencyMatrix = new int *[numVertices];
        for (int i = 0; i < numVertices; ++i)
        {
            adjacencyMatrix[i] = new int[numVertices];
            // Initialize all elements to 0
            for (int j = 0; j < numVertices; ++j)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    // Destructor
    ~Graph()
    {
        for (int i = 0; i < numVertices; ++i)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    // func to add an edge to the graph
    void addEdge(const Edge &edge)
    {
        // Assuming edges have weight 1, set the corresponding elements in the adjacency matrix to 1
        int start = edge.startVertex;
        int end = edge.endVertex;

        // seting val of edge in both directions, weight is always 1
        adjacencyMatrix[start - 1][end - 1] = 1;

        adjacencyMatrix[end - 1][start - 1] = 1;
    }

    // Getter for num of vertices
    int getNumVertices() const
    {
        return numVertices;
    }

    // Getter for the adjacency matrix
    int **getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }
};

// func for Dijkstras algorithm
void dijkstra(const Graph &graph, int startVertex)
{
    int numVertices = graph.getNumVertices();
    int **adjacencyMatrix = graph.getAdjacencyMatrix();

    // Initialize distances array to represent shortest path distances from startVertex
    int *distances = new int[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        // using a large val to represent all distances as initially being infinity
        distances[i] = 1000000;
    }
    // initail distance which is always 0
    distances[startVertex - 1] = 0;

    // Array to track visited vertices
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        visited[i] = false;
    }

    // Main loop
    for (int i = 0; i < numVertices - 1; ++i)
    {
        // Initialize minimum distance to a large val
        int minDistance = 1000000;
        int minIndex = -1;

        // Find the vertex with the minimum distance
        for (int v = 0; v < numVertices; ++v)
        {
            if (!visited[v] && distances[v] < minDistance)
            {
                minDistance = distances[v];
                minIndex = v;
            }
        }

        // Mark the min distance vertex as visited
        visited[minIndex] = true;

        // Look for a shorter path and update distance
        for (int v = 0; v < numVertices; ++v)
        {
            if (!visited[v] && adjacencyMatrix[minIndex][v] &&
                distances[minIndex] != 1000000 &&
                distances[minIndex] + 1 < distances[v])
            {
                // Weight of each edge if 1 so its only neccessary to add 1(because there is only a difference of 1) when updating the distances array
                distances[v] = distances[minIndex] + 1;
            }
        }
    }

    // Print lengths of the shortest paths using array storing distance vals for all vertices
    printf("Single source shortest path lengths from node %d\n", startVertex);
    for (int i = 0; i < numVertices; ++i)
    {
        printf("  %d: %d\n", (i + 1), distances[i]);
    }
    // Free mem
    delete[] distances;
    delete[] visited;
}

int main(int argc, char *argv[])
{

    // Open file
    FILE *infile = fopen(argv[1], "r");

    // Returns error msg if file fails to open
    if (!infile)
    {
        printf("Error: Unable to open file %s\n", argv[1]);
        return 1;
    }

    int numOfVertices, numOfEdges;
    fscanf(infile, "%d %d", &numOfVertices, &numOfEdges);

    // Create a Graph object with 'n' vertices
    Graph graph(numOfVertices);

    // Read add 'm' number of edges by iterating through all lines in the file
    for (int i = 0; i < numOfEdges; ++i)
    {
        int startVertex, endVertex;
        fscanf(infile, "%d %d", &startVertex, &endVertex);
        Edge newEdge(startVertex, endVertex);
        graph.addEdge(newEdge);
    }

    fclose(infile); // Close file

    // Print the adjacency matrix using a nested loop on the 2d array
    printf("The adjacency matrix of G:\n");
    int **adjacencyMatrix = graph.getAdjacencyMatrix();
    for (int i = 0; i < numOfVertices; ++i)
    {
        for (int j = 0; j < numOfVertices; ++j)
        {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    // Find odd degrees and apply Dijkstra's algorithm func
    printf("The odd degree vertices in G:\n");
    printf("O = { ");
    for (int i = 0; i < numOfVertices; ++i)
    {
        int degree = 0;
        for (int j = 0; j < numOfVertices; ++j)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                ++degree;
            }
        }
        // Condition to check if degree is odd
        if (degree % 2 != 0)
        {
            // Print the vertex number
            printf("%d ", (i + 1));
            // Apply Dijkstra's
            dijkstra(graph, i + 1);
        }
    }
    printf("}\n");

    return 0;
}
