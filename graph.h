#include<iostream>
#include<fstream>
#include<list>

class Vertex {
    private:
        int id, duration, demand;
            double x, y;
    public:
        Vertex(int, int, int, double, double);
        void debug();
};

class Graph {
    private:
        std::list<Vertex> vertices;
    public:
        Graph();
        bool insertVertex(Vertex v);
        void debug();
};
