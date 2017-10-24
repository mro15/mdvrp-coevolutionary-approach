#ifndef __SOLVER_H
#define __SOLVER_H

#include <iostream>
#include <operation.h>
#include <graph.h>
#include <population.h>

class MDVRPSolver {
    private:
        double maxDuration;
        double capacity;
        int nIndividuals;
        bool* workSpace;
        Operation& operation;
        Graph& g;
        Population** initPopulations(int redudancy);
        void migrate(Population **p, int segment, int redundancy, int searchSpace, bool maxMigrations, std::vector<Migration>& effective, std::vector<double>& results);
        void output(Population** population, int segment, int redundancy, int iterations, int itToMigrate, int itToInnnerMig, int seed);
        void undoMigration(Population **p, const Migration& m, int segment, int redundancy);
        void innerRouteMigration(Population** p, int segment, int redundancy);
    public:
        MDVRPSolver(Operation& op, Graph&g, double maxDuration, double capacity, int nIndividuals);
        void solve(int iterations, int itToMigrate, int redudancy, int itToInnerMig, bool maxMigrations, int seed);
};

#endif
