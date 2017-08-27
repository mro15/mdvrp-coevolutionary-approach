#ifndef __POPULATION_H
#define __POPULATION_H

#include <iostream>
#include <individual.h>
#include <operation.h>

class Population {
    private:
        Individual* individuals;
        int* clients;
        int depot, id;
        double maxDuration;
    public:
        Population(int depot, Operation& op, double maxDuration, Graph g);
        Individual* iterate();
        bool addClient(int id);
        bool removeClient(int id);
        void start();
        void restart();
        void clear();
        int badClient();
};

#endif