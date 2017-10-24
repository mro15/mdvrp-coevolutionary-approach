/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/

#include <iostream>
#include <fstream>
#include <graph.h>
#include <solver.h>
#include <operators.h>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]){
    int nCustomers, nDepots, nVehicles, nIterations, populationSize, itToMigrate;
    int redundancy; /*Number of multi-populations (populations with the same clients)*/
    int itToInnerMig;
    double maxRouteDuration, capacity, mutationRatio;
    std::fstream input;
    char* fileName;
    bool maxMigrations = false;
    int seed = time(0);
    if(!(argc==9 || argc==10 )){
        std::cout << "Usage is <infile> <n iterations> <n iterations to Migrate> <population size> <mutation ratio> <n_populations> <n iterations to inner Migration> <migration mode>[<seed>]\n";
        return 0;
    }else{
        fileName = argv[1];
        nIterations = atoi(argv[2]);
        itToMigrate = atoi(argv[3]);
        populationSize = atoi(argv[4]);
        mutationRatio = atof(argv[5]);
        redundancy = atof(argv[6]);
        itToInnerMig = atof(argv[7]);
        maxMigrations = (atoi(argv[8]) == 0)? true: false;
        if(argc == 10) {
            seed = atoi(argv[9]);
        }
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
    MutSwap mutOp(mutationRatio);
    CrCut crOp(nCustomers + nDepots);
    SelTour selOp(3);

    Operation op(mutOp, crOp, selOp);
    MDVRPSolver solver(op, g, maxRouteDuration, capacity, populationSize);
    solver.solve(nIterations, itToMigrate, redundancy, itToInnerMig, maxMigrations, seed);
    return 0;
}

