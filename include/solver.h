#ifndef __SOLVER_H
#define __SOLVER_H

#include <iostream>
#include <operation.h>
#include <graph.h>
#include <population.h>

class MDVRPSolver {
    private:
        int seed;
        double bestResult;
        Migration lastMigration;
        Operation& operation;
        Population** initPopulations(Graph &g, double maxDuration, double capacity, int nIndividuals);
    public:
        MDVRPSolver(Operation& op, int seed);
        void solve(Graph& g, double maxDuration, double capacity, int iterations, int itToMigrate, int nIndividuals);
    void migrate(Population **p, int length, int searchSpace);
};

#endif
