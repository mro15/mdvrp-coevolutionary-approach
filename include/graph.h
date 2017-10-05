#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include <vertex.h>
#include <structs.h>

class Graph {
    private:
        double **matrix;
        Vertex **vertices;
        int nCustomers;
        int _nDepots;
        int _nVertices;
        int* _customers;
        int* _depots;
        int _maxVehicles;
        int** assignment1();
        int** assignment2();
    public:
        Graph(int nCustomers, int nDepots, int _maxVehicles);
        ~Graph();
        void debug();
        void printDistances();

        bool addVertex(int id, double duration, double demand, double x, double y, int type);
        void buildEdges();
        double distanceTo(int a, int b);
        bool setToRoute(int vertex, int population);
        std::vector<RouteImportance> nearRoutes(int vertex, int k);
        void resetRoutes();
        int* depots();
        int* customers();
        int** assignment();
        int nVertices();
        int nDepots();
        int maxVehicles();
        double demand(int vertex);
};

#endif
