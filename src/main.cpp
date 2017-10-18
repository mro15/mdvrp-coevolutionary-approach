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
    int seed = time(0);
    if(!(argc==8 || argc==9 )){
        std::cout << "Usage is <infile> <n iterations> <n iterations to Migrate> <population size> <mutation ratio> <n_populations> <n iterations to inner Migration> [<seed>]\n";
        return 0;
    }else{
        fileName = argv[1];
        nIterations = atoi(argv[2]);
        itToMigrate = atoi(argv[3]);
        populationSize = atoi(argv[4]);
        mutationRatio = atof(argv[5]);
        redundancy = atof(argv[6]);
        itToInnerMig = atof(argv[7]);
        if(argc == 9) {
            seed = atoi(argv[8]);
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
    SelTour selOp(10);

    Operation op(mutOp, crOp, selOp);
    MDVRPSolver solver(op, g, maxRouteDuration, capacity, populationSize);
    solver.solve(nIterations, itToMigrate, redundancy, itToInnerMig, seed);
    return 0;
}

