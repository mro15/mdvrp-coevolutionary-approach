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
    public:
        Vertex(int, double, double, double, double, int);
        void debug();
        int rId();
        void calcDistances(std::vector<Vertex>);
        void printDistances();
};

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
};