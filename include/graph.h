#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>

#include <vertex.h>
#include <cstdlib>

class Graph {
    private:
        double **matrix;
        Vertex **vertices;
        int nCustomers;
        int nDepots;
        int nVertices;
        int* _customers;
        int* _depots;
        int maxVehicles;
    public:
        Graph(int nCustomers, int nDepots, int maxVehicles);
        ~Graph();
        void debug();
        void printDistances();

        bool addVertex(int id, double duration, double demand, double x, double y, int type);
        void buildEdges();
        double distanceTo(int a, int b);
        bool setToRoute(int vertex, int population);
        int kNeighborsRoute(int vertex, int k);
        void resetRoutes();
        int* depots();
        int* customers();
        int** assigment();
};

#endif
