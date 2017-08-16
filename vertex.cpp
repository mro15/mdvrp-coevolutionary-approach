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

void Vertex::calcDistances(std::vector<Vertex> vertices) {
    this->distances.clear();
    this->distances.push_back(0);
    double xFactor, yFactor;
    for(std::vector<Vertex>::iterator i=vertices.begin() +1; i != vertices.end(); ++i) {
        xFactor = this->x - (*i).x;
        xFactor *= xFactor;
        yFactor = this->y - (*i).y;
        yFactor *= yFactor;
        this->distances.push_back(sqrt(xFactor + yFactor));
    }
}

void Vertex::printDistances() {
    for(std::vector<double>::iterator i=distances.begin() +1; i !=distances.end(); ++i) {
        std::cout << id << " " << i - distances.begin() << " " << *i << std::endl;
    }
}
