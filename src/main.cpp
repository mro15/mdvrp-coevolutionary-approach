/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/

#include <iostream>
#include <fstream>
#include "graph.h"
#include <solver.h>
#include <operators.h>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]){
    int nCustomers, nDepots, nVehicles;
    double maxRouteDuration, capacity;
    std::fstream input;
    char* fileName;
    if(argc!=2){
        std::cout << "Usage is <infile>\n";
        return 0;
    }else{
        fileName = argv[1];
    }
    input.open(fileName, std::ifstream::in);
    input >> nVehicles;
    input >> nCustomers;
    input >> nDepots;
    input >> maxRouteDuration;
    input >> capacity;
    Graph g(nCustomers, nDepots, nVehicles);
    for(int i=0; i<nCustomers; ++i){
        int id, duration, demand;
        double x, y;
        input >> id >> x >> y >> duration >> demand;
        if(!g.addVertex(id, duration, demand, x, y, CUSTOMER)){
            printf("\nO vertice %d ja foi inserido", id);
            return(0);
        }
    }
    for(int i=0; i<nDepots; ++i){
        int id, duration, demand;
        double x, y;
        input >> id >> x >> y >> duration >> demand;
        g.addVertex(id, duration, demand, x, y, DEPOT);
    }
    g.buildEdges();
    //g.assignment();
    //debug function
    //g.debug();
    MutSwap mutOp(0.1);
    CrCut crOp(nCustomers + nDepots);
    SelRol selOp;

    Operation op(mutOp, crOp, selOp);
    srand(time(0));
    MDVRPSolver solver(op);
    solver.solve(g, maxRouteDuration, capacity, 10, 1000, 10);
    return 0;
}

