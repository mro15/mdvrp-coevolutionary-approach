#ifndef __VERTEX_H
#define __VERTEX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>

#define CUSTOMER 0
#define DEPOT 1

class Vertex {
    private:
        int _id, type;
        double x, y, duration, demand;
        std::vector<double> distances;

        Vertex ** sortedNeighbors;
        int nNeighbors;
        int route;
        int lastRoute;
        int _nearestDepot;
        int* workSpace;
    public:
        Vertex(int, double, double, double, double, int);
        ~Vertex();
        void debug();
        int id();
        void calcDistances(std::vector<Vertex>);
        void printDistances();

        void setNeighborhood(Vertex **neighbors, double* distances, int length);
        double distanceTo(Vertex *vertex);
        int kNeighborsRoute(int k);
        int nearestDepot();
        void changeToRoute(int k);
};

#endif
