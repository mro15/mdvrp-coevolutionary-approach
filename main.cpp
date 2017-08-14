/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/

#include<iostream>
#include<fstream>
#include"graph.h"

int main(int argc, char* argv[]){
    int nCustomers, nDepots, nVehicles, maxRouteDuration, capacity;
    std::fstream input;
    char* fileName;
    Graph g;
    Vertex *v;
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
    std::cout << "nCustomers: " << nCustomers << std::endl;
    std::cout << "nDepots: " << nDepots << std::endl;
    std::cout << "nVehicles: " << nVehicles << std::endl;
    std::cout << "maxRouteDuration: " << maxRouteDuration << std::endl;
    std::cout << "capacity: " << capacity << std::endl;
    for(int i=0; i<nCustomers; ++i){
        int id, duration, demand;
        double x, y;
        input >> id >> x >> y >> duration >> demand;
        v = new Vertex(id, duration, demand, x, y);
        g.insertVertex(*v);
    }

    g.debug();
    return 0;
}

