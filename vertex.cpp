#include"graph.h"

Vertex::Vertex(int id, double duration, double demand, double x, double y, int type){
   this->id = id;
   this->duration = duration;
   this->demand = demand;
   this->x = x;
   this->y = y;
   this->type = type;
}

void Vertex::debug() {
    std::cout << "id: " << this->id << std::endl;
    std::cout << "Position: x: " << this->x << " y: " << this->y << std::endl;
    std::cout << "Demand: " << this->demand << " Duration: " << this->duration << std::endl;
}

int Vertex::rId() {
    return this->id;
}
