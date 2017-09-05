#ifndef __SOLVER_H
#define __SOLVER_H

#include <iostream>
#include <operation.h>
#include <graph.h>
#include <population.h>

class MDVRPSolver {
    private:
        Operation& operation;
        Population** initPopulations(Graph &g, int nDepots, int maxVehicles, int maxDuration);
    public:
        MDVRPSolver(Operation& op);
        int* solve(Graph& g, int maxDuration, int iterations, int itToMigrate);
};

#endif
