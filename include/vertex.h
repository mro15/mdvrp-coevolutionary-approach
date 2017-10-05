#ifndef __VERTEX_H
#define __VERTEX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>

#include <structs.h>

#define CUSTOMER 0
#define DEPOT 1

class Vertex {
    private:
        int _id, _type, _nRoutes;
        double x, y, _duration, _demand;
        std::vector<double> distances;

        Vertex ** sortedNeighbors;
        int nNeighbors;
        int route;
        int lastRoute;
        int _nearestDepot;
        int* workSpace;
    public:
        Vertex(int, double, double, double, double, int, int);
        ~Vertex();
        void debug();
        int id();
        void calcDistances(std::vector<Vertex>);
        void printDistances();

        void setNeighborhood(Vertex **neighbors, double* distances, int length);
        double distanceTo(Vertex *vertex);
        std::vector<RouteImportance> nearRoutes(int k);
        int nearestDepot();
        void changeToRoute(int k);
        int type();
        int furthest(int depot, int index);
        int nearest(int depot);
        double demand();
        double duration();
        void streamTo(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif
