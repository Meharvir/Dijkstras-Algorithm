#ifndef EDGE_H
#define EDGE_H

class Edge{
    private:
        int startVert;
        int endVert;
        int weight;
    public:
        Edge();
        Edge(int, int);
        int getWeight();
        void setWeight(int);
};


#endif
