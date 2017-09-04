/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <vertex.h>

struct AuxSorting {
    double distance;
    int id;
};

int compare (const void* a, const void* b) {
    if(((struct AuxSorting*) a)->distance > ((struct AuxSorting*) b)->distance){
        return 1;
    }else if(((struct AuxSorting*) a)->distance - ((struct AuxSorting*) b)->distance){
        return -1;
    }else{
        return 0;
    }
}

Vertex::Vertex(int id, double duration, double demand, double x, double y, int type){
   this->_id = id;
   this->duration = duration;
   this->demand = demand;
   this->x = x;
   this->y = y;
   this->_type = type;
   this->workSpace = NULL;
   this->sortedNeighbors = NULL;
}

Vertex::~Vertex() {
    if(this->workSpace != NULL) {
        delete[] this->workSpace;
    }

    if(this->sortedNeighbors != NULL) {
        delete[] (this->sortedNeighbors -2);
    }
}

void Vertex::debug() {
    std::cout << "id: " << this->_id << std::endl;
    std::cout << "Position: x: " << this->x << " y: " << this->y << std::endl;
    std::cout << "Demand: " << this->demand << " Duration: " << this->duration << std::endl;
    std::cout << "Depot: " << this->_nearestDepot << std::endl;
}

int Vertex::id() {
    return this->_id;
}

void Vertex::printDistances() {
    for(std::vector<double>::iterator i=distances.begin() +1; i !=distances.end(); ++i) {
        std::cout << _id << " " << i - distances.begin() << " " << *i << std::endl;
    }
}

void Vertex::setNeighborhood(Vertex** neighbors, double* distances, int length) {
    /*
        Create the vertex neighborhood
        Parameters: neighbors, array of vertices
                    distances, distance to this vertex to the neighbors
                    length, size of that array

        Save the reference array and create the distances array, the
        sortedNeighbors array and the _nearestDepot.
    */

    struct AuxSorting* aux = new struct AuxSorting[length];
    int nearestDepot = -1;
    double distanceToDepot = -1;
    this->sortedNeighbors = new Vertex*[length];
    for (int i =1; i < length; ++i) {
        aux[i].distance = distances[i];
        aux[i].id = i;
        if (neighbors[i]->_type == DEPOT &&
           (distanceToDepot > distances[i] || distanceToDepot == -1)) {
            nearestDepot = i;
            distanceToDepot = distances[i];
        }
    }
    this->_nearestDepot = nearestDepot;
    qsort(aux + 1, length -1, sizeof(struct AuxSorting), compare);

    for (int i = 1; i < length; ++i) {
        sortedNeighbors[i] = neighbors[aux[i].id];
    }
    this->sortedNeighbors[0] = NULL;
    this->sortedNeighbors = sortedNeighbors +2;
    // Remove 0 that is null and 1 that is himself
    this->nNeighbors = length -2;
    this->workSpace = new int[this->nNeighbors];
    delete[] aux;
    return;
}

double Vertex::distanceTo(Vertex *vertex) {
    /*
        Returns the distance to this vertex to another vertex.
        Parameters: vertex, vertex id of another vertex

        Retusn the weight of the edge beteween the 2 vertices, returns 0
        for a inexistent vertex or for the same vertex.
    */
    double xFactor, yFactor;
    xFactor = this->x - vertex->x;
    xFactor *= xFactor;
    yFactor = this->y - vertex->y;
    yFactor *= yFactor;
    return sqrt(xFactor + yFactor);
}

int Vertex::kNeighborsRoute(int k) {
    /*
        Returns the most common route in the nearest k neighbors this vertex.
        Parameters: k, quantity of nearest neighbors to check.

        Get the k nearest neighbors of this vertex and return the most
        common value. If there is a draw, any of the values can be returned
        but always the same while the routes remain unchanged.

        returns 0 in error.
    */
    for (int i = 0; i < nNeighbors && i < k; ++i) {
        this->workSpace[i] = 0;
    }

    for (int i = 0; i < nNeighbors && i < k; ++i) {
        ++this->workSpace[this->sortedNeighbors[i]->route];
    }

    int biggest = 0, value = this->workSpace[0];
    for (int i = 1; i < nNeighbors && i < k; ++i) {
        if (this->workSpace[i] > value) {
            biggest = i;
            value = this->workSpace[i];
        }
    }

    return biggest;
}

int Vertex::nearestDepot() {
    /*
        Returns the id of the nearest depot of this vertex.

        Just return the value of the atribute _nearestDepot
    */
    return _nearestDepot;
}

void Vertex::changeToRoute(int k) {
    /*
        Move a vertex to another route.
        Parameters: k, route to move to.

        Just change the value of the property route to the given parameter.

        WARNING: This method does not create any connection with other objects
        just act as a flag on this vertex. The value set here only affects
        results of function like kNearestNeighbors, internal to the vertices.
    */
    this->route = k;
    return;
}

int Vertex::type() {
    return this->_type;
}

int Vertex::furthest(int depot, int index) {
    /*
        Returns the furthest customer, assigned to the depot.
        Paramater: depot, depot id
                   index, how much further. 1 = 1st futhest, 2 = 2nd furthest, ...
    */
    int count = 1;
   /* printf("----------------------------------{%d}{%d}{%d}\n", this->_id, index, depot);
    printf("[%d", this->sortedNeighbors[0]->_id);
    for(int i = 1; i < this->nNeighbors; ++i) {
        printf(", %d", this->sortedNeighbors[i]->_id);
    }
    printf("]\n");*/
    for(int i = nNeighbors -1; i >= 0; --i) {
        Vertex* v = this->sortedNeighbors[i];
        //printf("{%d}--{%d}--{%d}\n", v->_id, v->_type, v->_nearestDepot);
        if(v->_type != DEPOT && v->_nearestDepot == depot) {
            if (count == index) {
                return v->_id;
            }
            else {
                ++count;
            }
        }
    }

    return -1;
}

int Vertex::nearest(int depot) {
    /*
        Returns the nearest customer, assigned to the depot.
        Paramater: depot, depot id
    */
    for(int i = 0; i < this->nNeighbors; ++i) {
        Vertex* v = this->sortedNeighbors[i];
        if(v->_type != DEPOT && v->_nearestDepot == depot) {
            if (v->route == 0) {
                return v->_id;
            }
        }
    }

    return -1;
}
