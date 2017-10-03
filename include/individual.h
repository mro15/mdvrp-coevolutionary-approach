#ifndef __INDIVIDUAL_H

#include <iostream>
#include <graph.h>
#include <cstdlib>

class Individual {
    private:
        std::vector<int> _customers;
        int _depot;
        double _maxDuration;
        double _capacity;
        int* _route;
        Graph& _graph;
    public:
        Individual(std::vector<int>& customers, int depot, double maxDuration, double capacity, Graph& g);
        // Individual::Individual(const Individual& i);
        void compact(int id);
        void expand(int id);
        int badClient();
        double fitness();
        double duration();
        bool feasible();
        std::vector<int>& customers();
        void debug();
};

#define __INDIVIDUAL_H
#endif