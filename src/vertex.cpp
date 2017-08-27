#include <vertex.h>

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


void Vertex::setNeighborhood(Vertex* neighbors, int length) {
    /*
        Create the vertex neighborhood
        Parameters: neighbors, array of verttices
                    length, size of that array

        Save the reference array and create the distances array, the
        sortedNeighbors array and the _nearestDepot.
    */
    return;
}

double Vertex::distanceTo(int vertex) {
    /*
        Returns the distance to this vertex to another vertex.
        Parameters: vertex, vertex id of another vertex

        Retusn the weight of the edge beteween the 2 vertices, returns 0
        for a inexistnt vertex or for the same vertex.
    */
    return 0.0;
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