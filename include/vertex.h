#ifndef __VERTEX_H
#define __VERTEX_H

#include<iostream>
#include<fstream>
#include<vector>
#include <cmath>

#define CUSTOMER 1
#define DEPOT 2

class Vertex {
    private:
        int id, type;
        double x, y, duration, demand;
        std::vector<double> distances;

        int * sortedNeighbors;
        int route;
        int lastRoute;
        int maxVehicles;
        int _nearestDepot;
    public:
        Vertex(int, double, double, double, double, int);
        void debug();
        int rId();
        void calcDistances(std::vector<Vertex>);
        void printDistances();

        void setNeighborhood(Vertex *neighbors, int length);
        double distanceTo(Vertex *vertex);
        int kNeighborsRoute(int k);
        int nearestDepot();
};

#endif
