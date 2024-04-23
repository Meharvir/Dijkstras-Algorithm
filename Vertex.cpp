#include "Vertex.h"

Vertex::Vertex(){
    this->index = -1;
    this->degree = -1;
}

int Vertex::getIndex(){
    return this->Index;
}

int Vertex::getDegree(){
    return this->degree;
}

void Vertex::setIndex(int index){
    this->index = index;
}

void Vertex::setDegree(int deg){
    this->degree = deg;
}
