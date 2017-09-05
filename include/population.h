#ifndef __POPULATION_H
#define __POPULATION_H

#include <iostream>
#include <individual.h>
#include <operation.h>
#include <vector>

class Population {
    private:
        Individual* individuals;
        Operation& operation;
        Graph& graph;
        std::vector<int> clients;
        int depot, _id;
        double maxDuration;
    public:
        Population(int id, Graph& g, Operation& op, int depot, double maxDuration);
        Individual* iterate();
        bool addClient(int id);
        bool removeClient(int id);
        void start();
        void restart();
        void clear();
        int badClient();
};

#endif
