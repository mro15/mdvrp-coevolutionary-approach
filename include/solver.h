#ifndef __SOLVER_H
#define __SOLVER_H

#include <iostream>
#include <operation.h>
#include <graph.h>

class MDVRPSolver {
    private:
        Operation* operation;
    public:
        MDVRPSolver(Operation* op);
        int* solve(Graph& g, int maxDuration, int iterations, int itToMigrate);
};

#endif
