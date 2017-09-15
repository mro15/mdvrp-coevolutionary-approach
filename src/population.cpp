/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <population.h>

Population::Population(int id, Graph& g, Operation& op, int depot, double maxDuration, double capacity, int nIndividuals):
                       operation(op), graph(g) {
    this->_id = id;
    this->depot = depot;
    this->maxDuration = maxDuration;
    this->individuals = NULL;
    this->_nIndividuals = nIndividuals;
    this->capacity = capacity;
}

Individual* Population::iterate() {
    /*
        Executes one iteration of the solve method for this population

        One iteration means progress the solving process one step.
        In this case, an evolutionary algorithm, is apply the three operations
        in the individuals of this population that is, selection, cross-over
        than mutation, in this order.

        At the and of a iteration a new set of individuals will replace the
        last generation.

        Retuns the best individual of the new generation, NULL in case of error.
    */

    Individual*** parents = operation.select(this->individuals, this->_nIndividuals/2);
    Individual** offspring = new Individual*[this->_nIndividuals];
    int position = 0;
    for (int i = 0; i < this->_nIndividuals/2; ++i) {
        Individual** cross = operation.crossover(parents[i]);
        for (int j = 0; j < 2; ++j) {
            offspring[position +j] = cross[j];
        }
        position += 2;
        delete[] cross;
    }

    for (int i = 0; i < this->_nIndividuals; ++i) {
        operation.mutate(*offspring[i]);
    }
    delete[] individuals;
    delete[] parents;
    individuals = offspring;
    return NULL;
}

bool Population::addClient(int vertex) {
    /*
        Adds a client to this population.
        Parameters: vertex, id of vertex, tha is a client in the Graph g.

        Adds a vertex to be handled by this population, in other words the
        routes created by this population WILL include the client added to it.

        Returns true if the vertex is included, false otherwise.

        False can be retured for a inexistent vertex or a already added vertex
        to THIS population.

        WARNING: This method does NOT verify if the client is in other
        Populations.
    */
    for (std::vector<int>::iterator it = clients.begin() ; it != clients.end(); ++it) {
        if(*it == vertex) {
            return false;
        }
    }
    if (graph.setToRoute(vertex, this->_id)) {
        clients.push_back(vertex);
        return true;
    }
    return false;
}

bool Population::removeClient(int id) {
    /*
        Removes a client to this population.
        Parameters: id, id of vertex, tha is a client in the Graph g.

        Removes that was addes to this population, in other words the
        routes created by this population WILL NOT include that client.

        Returns true if the vertex is removed, false otherwise.

        False can be retured for a inexistent vertex;
    */
    std::vector<int>::iterator toRemove;
    bool find = false;
    for (std::vector<int>::iterator it = clients.begin() ; it != clients.end(); ++it) {
        if(*it == id) {
            toRemove = it;
            find = true;
        }
    }
    if (find) {
        clients.erase(toRemove);
        return true;
    }

    return false;
}

void Population::start() {
    /*
        Creates a random set of individuals and save it internaly.

        Using the clients added create a set of random individuals and
        add than to the individuals set.

        WARNING: This function assumes that individuals is NULL or
        clear has been called before.
    */

    individuals = new Individual*[this->_nIndividuals];
    for(int i = 0; i < this->_nIndividuals; i++) {
        std::vector<int> permutation(clients);
        random_shuffle(permutation.begin(), permutation.end());
        individuals[i] = new Individual(permutation, this->depot, this->maxDuration, this->capacity, graph);
    }
    return;
}

void Population::restart() {
    /*
        Reset a population, in other words, clear and start population.

        Removes the existent individuals and create a new random set using the
        clients added to this population.

        Is literay call start and clear in sequence and just it.
    */
    this->clear();
    this->start();

    return;
}

void Population::clear() {
    /*
        Removes the existent individuals.
    */
    for(int i = 0; i < this->_nIndividuals; i++) {
        delete individuals[i];
    }
    delete[] individuals;
    return;
}

int Population::badClient() {
    /*
        Returns the client (id) that proprably is impactly badly in the fitness
        of the individuals of this population.

        This is by now done in a mysterious way, when we have figured out how we
        are going to do it, we will change this description.

        returns 0 if none is bad.
    */
    return 0;
}
