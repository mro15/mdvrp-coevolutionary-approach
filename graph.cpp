#include"graph.h"

Graph::Graph(){
}

bool Graph::insertVertex(Vertex v){
    this->vertices.push_back(v);
}

void Graph::debug(){
    std::cout << "Printing List" << std::endl;
    for(std::list<Vertex>::iterator i=this->vertices.begin(); i != vertices.end(); ++i){
       (*i).debug();
    }
}
