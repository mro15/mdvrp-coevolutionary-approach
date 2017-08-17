#include"graph.h"

Graph::Graph(){
    Vertex v(0, 0, 0, 0, 0, CUSTOMER);
    this->vertices.push_back(v);
}

bool Graph::insertVertex(Vertex v){
    this->vertices.push_back(v);
}

void Graph::debug(){
    std::cout << "Printing List" << std::endl;
    for(std::vector<Vertex>::iterator i=this->vertices.begin()+1; i != vertices.end(); ++i){
       (*i).debug();
    }
}

void Graph::printElem(int id){
    std::cout << "id: " << id << " elem: " << this->vertices[id].rId() <<std::endl;
}

void Graph::calcDistances() {
    for(std::vector<Vertex>::iterator i=this->vertices.begin() +1; i != this->vertices.end(); ++i) {
        (*i).calcDistances(this->vertices);
    }
}

void Graph::printDistances() {
    for(std::vector<Vertex>::iterator i=this->vertices.begin() +1; i != this->vertices.end(); ++i) {
        (*i).printDistances();
    }
}
