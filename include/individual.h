#ifndef __INDIVIDUAL_H

#include <iostream>
#include <graph.h>

class Individual {
    private:
        int* clients;
        int depot;
        double maxDuration;
        int* route;
    public:
        Individual(int* clients, int depot, double maxDuration, Graph g);
        int badClient();
        double fitness();
        bool feasible();
};

#define __INDIVIDUAL_H
#endif
