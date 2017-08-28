#include"graph.h"

Graph::Graph(){
    Vertex v(0, 0, 0, 0, 0, CUSTOMER);
    this->vertices.push_back(v);
}

bool Graph::insertVertex(Vertex v){
    this->vertices.push_back(v);
    return true;
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

bool Graph::addVertex() {
    /*
        Adds a vertex to the graph.
        Recieves the parameters used to create a Vertex object.
        returns true if the Vertex is created with success and added to the
        graph, otherwise false.

        Try to add the same vertex twice (same id) retruns false.
    */
    return true;
}
void Graph::buildEdges() {
    /*
        Build the edges between the vertices and set their weights.

        To solve the MDVRP a complete graph is used, so after add ALL  your
        vertices to the graph, using the x and y coordinates of each vertex
        an edge is create to each pair of vertices and the weight of this edge
        is set to the distance between then.
    */
    return;
}

double Graph::distanceTo(int a, int b) {
    /*
        Returns the distance between a pair of vertices.
        Parameters: a, id of a vertex in the the graph
                    b, id of a vertex in the graph
        
        Recieves the ids, find the vertices and get the weight of the edge
        between they.

        return 0.0 if a vertex is not found in the graph or if the ids are
        equal.
    */
    return 0.0;
}

bool Graph::setToRoute(int vertex, int route) {
    /*
        Set a vertex to some route.
        Parameters: vertex, vertex id
                    route, the route id
        
        Changes the value of the atribute route of the given vertex.
        Returns true if the vertex is found, false otherwise.

        WARNING: This method does not checks if this route id is valid.
    */
    return true;
}

int Graph::kNeighborsRoute(int vertex, int k) {
    /*
        Returns the most common route in the nearest k neighbors of a vertex.
        Parameters: vertex, vertex id
                    k, quantity of nearest neighbors to check.

        Get the k nearest neighbors of the given vertex and return the most
        common value. If there is a draw, any of the values can be returned
        but always the same while the routes remain unchanged.

        returns 0 in error.
    */
    return 0;
}

void Graph::resetRoutes() {
    /*
        Remove all vertices from their routes.

        Set all the vertices to a default, unused route value, 0.
    */
    return ;
}
