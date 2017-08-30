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
    return ((struct AuxSorting*) a)->distance - ((struct AuxSorting*) b)->distance;
}

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

void Vertex::printDistances() {
    for(std::vector<double>::iterator i=distances.begin() +1; i !=distances.end(); ++i) {
        std::cout << id << " " << i - distances.begin() << " " << *i << std::endl;
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
        if (neighbors[i]->type == DEPOT && distanceToDepot > distances[i]) {
            nearestDepot = i;
            distanceToDepot = distances[i];
        }
    }
    this->_nearestDepot = nearestDepot;
    qsort(aux + 1, length -1, sizeof(struct AuxSorting), compare);

    for (int i = 1; i < length; ++i) {
        sortedNeighbors[i] = neighbors[aux[i].id];
    }
    sortedNeighbors[0] = NULL;
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
    return 0;
}

int Vertex::nearestDepot() {
    /*
        Returns the id of the nearest depot of this vertex.

        Just return the value of the atribute _nearestDepot
    */
    return 0;
}
