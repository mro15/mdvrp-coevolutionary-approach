#ifndef __POPULATION_H
#define __POPULATION_H

#include <iostream>
#include <individual.h>
#include <operation.h>
#include <vector>
#include <algorithm>

class Migration {
    public:
        int customer;
        int source;
        int target;
        int importance; // Se a rota está estourada é grande (conta mágica)
        bool operator<(const Migration& b) {
            return this->importance < b.importance;
        }
};

class Population {
    private:
        Individual** individuals;
        Operation& operation;
        Graph& graph;
        std::vector<int> customers;
        int _depot, _id, _nIndividuals;
        double maxDuration, maxCapacity;
        double capacity;
    public:
        Population(int id, Graph& g, Operation& op, int depot, double maxDuration, double maxCapacity, int nIndividuals);
        void iterate();
        bool addClient(int id);
        bool removeClient(int id);
        void start();
        void restart();
        void clear();
        int badClient();
        Individual* best();
        bool underCapacity();
        int depot();
        std::vector<Migration> migration();
};


#endif
