#ifndef __INDIVIDUAL_H

#include <iostream>
#include <graph.h>

class Individual {
    private:
        int* _clients;
        int _depot;
        double _maxDuration;
        double _capacity;
        int* _route;
        int _size;
    public:
        Individual(int* clients, int size, int depot, double maxDuration, double capacity, Graph& g);
        int badClient();
        double fitness();
        bool feasible();
};

#define __INDIVIDUAL_H
#endif
