#include"graph.h"

Vertex::Vertex(int id, int duration, int demand, double x, double y){
   this->id = id;
   this->duration = duration;
   this->demand = demand;
   this->x = x;
   this->y = y;
}

void Vertex::debug() {
    std::cout << "id: " << this->id << std::endl;
}
