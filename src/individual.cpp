/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <individual.h>

Individual::Individual(std::vector<int>& customers, int depot, double maxDuration, double capacity, Graph& g): _customers(customers), _graph(g) {
    _depot = depot;
    _maxDuration = maxDuration;
    _capacity = capacity;
}

int Individual::badClient() {
    /*
        Returns the client (id) that proprably is impactly badly in the fitness
        of this individual..

        This is by now done in a mysterious way, when we have figured out how we
        are going to do it, we will change this description.

        returns 0 if none is bad.
    */
    return 0;
}

double Individual::fitness() {
    /*
        Returns the value of fitness.

        This is by now done in a mysterious way, when we have figured out how we
        are going to do it, we will change this description.

        returns 0.0 on error.

        Adicionar a discanpia para os depostios
    */
    return -this->duration();
}

double Individual::duration() {
    /*
        Returns the duration of a route
    */

    double duration = _graph.distanceTo(this->_depot, *(_customers.begin()));
    for (std::vector<int>::iterator it = _customers.begin()+1 ; it != _customers.end(); ++it) {
        duration += _graph.distanceTo(*(it -1), *it);
    }

    return duration + _graph.distanceTo(*(_customers.end()), this->_depot);
}

bool Individual::feasible() {
    /*
        Checks  if this individual is localy fesible.

        Returns true if this individual passes in all constraints of the problem
        applyed on it, returns false if fail in at least one constraint.
    */

    return (this->_maxDuration != 0 ) ? this->duration() < this->_maxDuration: true ;
}

std::vector<int>& Individual::customers() {
    /*
        Returns the sequence of customers that
        represents a individual
    */
    return this->_customers;
}

void Individual::debug() {
    printf("[");
    for (std::vector<int>::iterator it = _customers.begin() ; it != _customers.end(); ++it) {
        printf("%d, ", *it);
    }
    printf("]");
}
