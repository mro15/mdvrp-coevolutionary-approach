#ifndef __SOLVER_H
#define __SOLVER_H

#include <iostream>
#include <operation.h>
#include <graph.h>
#include <population.h>

class MDVRPSolver {
    private:
        Operation& operation;
        Population** initPopulations(Graph &g, double maxDuration, double capacity, int nIndividuals);
    public:
        MDVRPSolver(Operation& op);
        int* solve(Graph& g, double maxDuration, double capacity, int iterations, int itToMigrate, int nIndividuals);
};

#endif
