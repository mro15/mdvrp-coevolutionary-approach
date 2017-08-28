#ifndef __GRAPH_H
#define __GRAPH_H

#include<iostream>
#include<fstream>
#include<vector>
#include <cmath>

#include <vertex.h>

class Graph {
    private:
        double **matrix;
        Vertex **vertices;
        int nCustomers;
        int nDepots;
        int nVertex;
    public:
        Graph(int nCustomers, int nDepots);
        bool insertVertex(Vertex v);
        void debug();
        void printElem(int);
        void calcDistances();
        void printDistances();

        bool addVertex(int id, double duration, double demand, double x, double y, int type);
        void buildEdges();
        double distanceTo(int a, int b);
        bool setToRoute(int vertex, int population);
        int kNeighborsRoute(int vertex, int k);
        void resetRoutes();
};

#endif
