#include "Edge.h"

Edge::Edge(){
    this->startVert = -1;
    this->endVert = -1;
    this->weight = -1;
}

Edge::Edge(int start, int end){
    this->startVert = start;
    this->endVert = end;
    this->weight = 1;
}

int Edge::getWeight(){
    return this->weight;
}

void Edge::setWeight(int newWeight){
    this->weight = newWeight;
}
