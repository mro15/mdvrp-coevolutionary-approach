/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <operators.h>

MutSwap::MutSwap(double probability) {
    this->_probability = 1000*probability;
}


void MutSwap::mutate(Individual& i) {
    int chance = rand()%1000;
    if(chance <= this->_probability) {
        int pos1 = rand()%i.customers().size();
        int pos2 = rand()%i.customers().size();
        int value1 = i.customers().at(pos1);
        int value2 = i.customers().at(pos2);
        i.customers().at(pos1) = value2;
        i.customers().at(pos2) = value1;
    }
}

Individual** CrCut::crossover(Individual** i) {
    return i;
}

Individual*** SelRol::select(Individual** population, int length) {
    Individual *** r = new Individual**[length];
    int* prop = new int[2*length];

    for(int i = 0; i < length; ++i) {
        r[i] = new Individual*[2];
        //TODO: Selection
        r[i][0] = population[2*i];
        r[i][1] = population[(2*i)+1];
    }

    return r;
}
