#ifndef __GRAPH_H
#define __GRAPH_H

#include<iostream>
#include<fstream>
#include<vector>
#include <cmath>

#include <vertex.h>

class Graph {
    private:
        std::vector<Vertex> vertices;
    public:
        Graph();
        bool insertVertex(Vertex v);
        void debug();
        void printElem(int);
        void calcDistances();
        void printDistances();

        bool addVertex();
        void buildEdges();
        double distanceTo(int a, int b);
        bool setToRoute(int vertex, int population);
        int kNeighborsRoute(int vertex, int k);
        void resetRoutes();
};

#endif
