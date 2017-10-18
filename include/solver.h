#ifndef __SOLVER_H
#define __SOLVER_H

#include <iostream>
#include <operation.h>
#include <graph.h>
#include <population.h>

class MDVRPSolver {
    private:
        double bestResult;
        double maxDuration;
        double capacity;
        int nIndividuals;
        Migration lastMigration;
        Operation& operation;
        Graph& g;
        Population** initPopulations(int redudancy);
        void migrate(Population **p, int length, int redundancy, int searchSpace);
        void output(Population** population, int segment, int redundancy, int iterations, int itToMigrate, int seed);
        void undoMigration(Population **p, int segment, int redundancy);
    public:
        MDVRPSolver(Operation& op, Graph&g, double maxDuration, double capacity, int nIndividuals);
        void solve(int iterations, int itToMigrate, int redudancy, int seed);
};

#endif
