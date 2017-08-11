/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/

#include<iostream>
#include<fstream>

int main(int argc, char* argv[]){
    int nCustomers, nDepots, nVehicles, maxRouteDuration, capacity;
    std::fstream input;
    char* fileName;
    if(argc!=2){
        std::cout << "Usage is <infile>\n";
        return 0;
    }else{
        fileName = argv[1];
    }
    input.open(fileName, std::ifstream::in);
    input >> nCustomers;
    input >> nDepots;
    input >> nVehicles;
    input >> maxRouteDuration;
    input >> capacity;
    std::cout << "nCustomers: " << nCustomers << std::endl;
    std::cout << "nDepots: " << nDepots << std::endl;
    std::cout << "nVehicles: " << nVehicles << std::endl;
    std::cout << "maxRouteDuration: " << maxRouteDuration << std::endl;
    std::cout << "capacity: " << capacity << std::endl;
    return 0;
}

