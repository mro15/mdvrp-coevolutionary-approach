/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <solver.h>

MDVRPSolver::MDVRPSolver(Operation& op): operation(op) {
    /*
        Creates a instance of the solver
    */
}

int* MDVRPSolver::solve( Graph& g,
                         int maxDuration,
                         int iterations,
                         int itToMigrate,
                         int nIndividuals) {
    /*
        Solve the MDVRP.
        Parameters: g, Graph that represents clients and depots
                    maxDuration, max duration of a route
                    iterations, number of iterations of the method
                    itToMigrate, iterations to create a migration

        returns an array with the ids of the vertices, orderered in the routes
        with the format: d1, c1, c2, ..., cn d1 d1, cn+1, ..., d1, d2, ...

        Routes start and finish with the same depor, the routes are
        concatenated in this array.

        returns NULL in error or impossibility to solve.
    */
    Population ** population = this->initPopulations(g, maxDuration, nIndividuals);
    int length = g.nDepots()*g.maxVehicles();
    for(int i = 0; i < length; ++i) {
        population[i]->start();
    }
    for(int i = 0; i < iterations; ++i) {
        for(int j = 0; j < length; ++j) {
            population[j]->iterate();
        }
    }

    // Encontrar uma forma de retornar solução
    return NULL;
}

Population** MDVRPSolver::initPopulations(Graph& g, int maxDuration, int nIndividuals) {
    /*
        Creates a set of Populations and initializes it with some clients
        but 0 individuals.
        Parameters: g, Graph that represents clients and depots
                    nDepots, the number of depots of the problem
                    nVehicles, max number of vehicles in each depot

        This member function creates the instances of Populations and add the
        clients to it.
    */
    int nDepots = g.nDepots();
    int nVehicles = g.maxVehicles();
    int length = nDepots*nVehicles;
    Population** r = new Population*[length];
    int* depots = g.depots();
    int** assignment = g.assignment();
    for (int i = 0; i < nDepots; ++i) {
        for(int j = 0; j < nVehicles; ++j) {
            int index = i*nDepots + j;
            r[index] = new Population(index, g, this->operation, depots[i], maxDuration, nIndividuals);
            for(int k = 0; k < g.nVertices(); ++k) {
                if(assignment[index][k] == 1) {
                    r[index]->addClient(k);
                }
            }
        }
    }

    return r;
}
