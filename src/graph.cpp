/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <graph.h>

Graph::Graph(int nCustomers, int _nDepots, int _maxVehicles){
    this->nCustomers = nCustomers;
    this->_nDepots = _nDepots;
    this->_maxVehicles = _maxVehicles;
    this->_nVertices = nCustomers + _nDepots+1;
    this->_depots = new int[_nDepots];
    this->_customers = new int[nCustomers];
    this->vertices = new Vertex*[_nVertices];
    this->matrix = new double*[nCustomers+_nDepots+1];
    for(int i=0; i<_nVertices; ++i){
        this->matrix[i]=new double[_nVertices];
    }
}

Graph::~Graph() {
    for(int i=0; i<_nVertices; ++i){
        delete[] this->matrix[i];
        delete this->vertices[i];
    }
    delete[] this->matrix;
    delete[] this->vertices;
    delete[] this->_depots;
    delete[] this->_customers;
}


void Graph::debug(){
    /*
        Debug function
        Print all vertices position, demand and duration
    */
    // std::cout << "Printing List" << std::endl;
    for(int i=1; i < _nVertices; ++i){
       vertices[i]->debug();
    }
}


void Graph::printDistances() {
    for(int i=1; i<_nVertices; ++i){
        for(int j=1; j<_nVertices; ++j){
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
    int depotIndex = 0, customerIndex = 0;
    for(int i=1; i<_nVertices; ++i){
        for(int j=1; j<_nVertices; ++j){
            this->matrix[i][j]=vertices[i]->distanceTo(vertices[j]);
        }
        if (this->vertices[i]->type() == DEPOT) {
            this->_depots[depotIndex] = i;
            ++depotIndex;
        }

        else {
            this->_customers[customerIndex] = i;
            ++customerIndex;
        }
    }
    for (int i=1; i<_nVertices; ++i) {
        vertices[i]->setNeighborhood(vertices, this->matrix[i], _nVertices);
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
    if(a < _nVertices && b < _nVertices && a > -1 && b > -1) {
        return this->matrix[a][b];
    }
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
    if(vertex < _nVertices && vertex > -1) {
        this->vertices[vertex]->changeToRoute(route);
        return true;
    }
    return false;
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
    if(vertex < _nVertices && vertex > -1) {
        return this->vertices[vertex]->kNeighborsRoute(k);
    }
    return 0;
}

void Graph::resetRoutes() {
    /*
        Remove all vertices from their routes.

        Set all the vertices to a default, unused route value, 0.
    */
    for (int i = 1; i < this->_nVertices; ++i) {
        this->vertices[i]->changeToRoute(0);
    }
    return;
}

int* Graph::depots() {
    return this->_depots;
}

int* Graph::customers() {
    return this->_customers;
}

int Graph::nVertices() {
    return this->_nVertices;
}

int Graph::nDepots() {
    return this->_nDepots;
}

int Graph::maxVehicles() {
    return this->_maxVehicles;
}

int** Graph::assignment() {
    this->resetRoutes();
    int nRoutes = this->_nDepots * this->_maxVehicles;
    int **r = new int*[nRoutes];
    for(int i = 0; i < nRoutes; ++i) {
        r[i] = new int[this->_nVertices];
        for(int j = 1; j < this->_nVertices; ++j) {
            r[i][j] = 0;
        }
    }

    for(int i = 0; i < this->_nDepots; ++i) {
        for(int j = 1; j < this->_nVertices; ++j) {
            if (this->vertices[j]->nearestDepot() == this->_depots[i]) {
                r[i*this->_maxVehicles][j] = 1;
            }
            else {
                r[i*this->_maxVehicles][j] = 0;
            }
        }
    }


    int* centers = new int[this->_maxVehicles];
    int* workSpace = new int[this->_nVertices];
    int centersLength = 0;
    int index = 0;
    int foundCenter = -1;
    bool centerFounded = false, fewCustomers = false;
    for(int i = 0; i < this->_nDepots; ++i) {
        Vertex* depot = this->vertices[this->_depots[i]];
        centers[0] = depot->furthest(depot->id(), 1);
        centersLength = 1;
        index = 1;
        fewCustomers = false;
        centerFounded = false;
        for(int j = 0; j < this->_nVertices; ++j) {
            workSpace[j] = 0;
        }
        while(centersLength < _maxVehicles && !fewCustomers) {
            for(int j = 0; j < centersLength; ++j) {
                Vertex* v = this->vertices[centers[j]];
                int furthest = v->furthest(depot->id(), index);
                if(furthest == -1) {
                    fewCustomers = true;
                }
                else {
                    ++workSpace[furthest];
                    /*if(centersLength == 1) {
                        printf("FUR00: %d, %d\n", furthest, workSpace[furthest]);
                    }*/
                    if (workSpace[furthest] == centersLength && !centerFounded) {
                        foundCenter = furthest;
                        centerFounded = true;
                    }
                }
            }

            while (centerFounded && centersLength < _maxVehicles) {
                centerFounded = false;
                centers[centersLength] = foundCenter;
                /*if(centersLength == 1) {
                    printf("FUR11: %d\n", centers[centersLength]);
                }*/
                ++centersLength;
                for(int j = 1; j <= index; ++j) {
                    Vertex* v = this->vertices[foundCenter];
                    int furthest = v->furthest(depot->id(), j);
                    if(furthest == -1) {
                        fewCustomers = true;
                    }
                    else {
                        ++workSpace[furthest];
                        if (workSpace[furthest] == centersLength && !centerFounded) {
                            foundCenter = furthest;
                            centerFounded = true;
                        }
                    }
                }
            }

            ++index;
        }

        for(int k = 0; k < centersLength; ++k) {
            /*if(centers[k] == 10) {
                printf("%d OK OKDO\n", k);
            }*/
            this->vertices[centers[k]]->changeToRoute(i*_maxVehicles+k +1);
            r[i*_maxVehicles][centers[k]] = 0;
            r[i*_maxVehicles+k][centers[k]] = 1;
        }

        bool allAssigned = false;
        while (!allAssigned) {
            for(int k = 0; k < centersLength; ++k) {
                int vertex = this->vertices[centers[k]]->nearest(depot->id());
                if(vertex == -1) {
                    allAssigned = true;
                    k = centersLength;
                }
                else {
                    /*if(vertex == 10) {
                        printf("1111111111\n");
                    }*/
                    this->vertices[vertex]->changeToRoute(i*_maxVehicles+k +1);
                    r[i*_maxVehicles][vertex] = 0;
                    r[i*_maxVehicles+k][vertex] = 1;
                }

            }
        }

        r[i*_maxVehicles][this->_depots[i]] = 0;
        depot->changeToRoute(0);
    }
    /*for(int k = 0; k < this->_nDepots*_maxVehicles; ++k) {
        printf("(%d)[%d", k+1, r[k][1]);
        for(int j = 2; j < this->_nVertices; ++j) {
            printf(", %d", r[k][j]);
        }
        printf("]\n");
    }*/
    return r;
}
