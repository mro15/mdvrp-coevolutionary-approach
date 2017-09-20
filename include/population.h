#ifndef __POPULATION_H
#define __POPULATION_H

#include <iostream>
#include <individual.h>
#include <operation.h>
#include <vector>
#include <algorithm>

class Population {
    private:
        Individual** individuals;
        Operation& operation;
        Graph& graph;
        std::vector<int> customers;
        int depot, _id, _nIndividuals;
        double maxDuration, capacity;
    public:
        Population(int id, Graph& g, Operation& op, int depot, double maxDuration, double capacity, int nIndividuals);
        Individual* iterate();
        bool addClient(int id);
        bool removeClient(int id);
        void start();
        void restart();
        void clear();
        int badClient();
};

#endif
