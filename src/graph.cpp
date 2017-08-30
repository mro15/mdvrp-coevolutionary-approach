/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include"graph.h"

Graph::Graph(int nCustomers, int nDepots){
    this->nCustomers = nCustomers;
    this->nDepots = nDepots;
    this->nVertex = nCustomers + nDepots+1;
    this->vertices = new Vertex*[nVertex];
    this->matrix = new double*[nCustomers+nDepots+1];
    for(int i=0; i<nVertex; ++i){
        this->matrix[i]=new double[nVertex];
    }
}


void Graph::debug(){
    /*
        Debug function
        Print all vertices position, demand and duration
    */
    std::cout << "Printing List" << std::endl;
    for(int i=1; i < nVertex; ++i){
       vertices[i]->debug();
    }
}


void Graph::printDistances() {
    for(int i=1; i<nVertex; ++i){
        for(int j=1; j<nVertex; ++j){
            printf("%f ", this->matrix[i][j]);
        }
        printf("\n");
    }
}


bool Graph::addVertex(int id, double duration, double demand, double x, double y, int type) {
    /*
        Adds a vertex to the graph.
        Recieves the parameters used to create a Vertex object.
        returns true if the Vertex is created with success and added to the
        graph, otherwise false.

        Try to add the same vertex twice (same id) retruns false.
    */
    if (vertices[id] == NULL ) {
        vertices[id] = new Vertex(id, duration, demand, x, y, type);
        return true;
    }
    else {
        return false;
    }
}
void Graph::buildEdges() {
    /*
        Build the edges between the vertices and set their weights.

        To solve the MDVRP a complete graph is used, so after add ALL  your
        vertices to the graph, using the x and y coordinates of each vertex
        an edge is create to each pair of vertices and the weight of this edge
        is set to the distance between then.
    */
    for(int i=1; i<nVertex; ++i){
        for(int j=1; j<nVertex; ++j){
            this->matrix[i][j]=vertices[i]->distanceTo(vertices[j]);
        }
    }
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
