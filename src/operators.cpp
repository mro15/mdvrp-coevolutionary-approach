/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <operators.h>

MutSwap::MutSwap(double probability) {
    this->_probability = 100*probability;
}


void MutSwap::mutate(Individual& i) {
    int chance = rand()%100;
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

Individual*** SelRol::select(Individual** individuals, int length) {
    Individual *** r = new Individual**[length/2];
    int* prop = new int[length];
    double sum = 0.0;
    for(int i = 0; i < length; ++i) {
        sum += individuals[i]->fitness();
    }

    for(int i = 0; i < length; ++i) {
        prop[i] = 100*individuals[i]->fitness()/sum;
    }


    for(int i = 0; i < length/2; ++i) {
        r[i] = new Individual*[2];
        int p1 = rand()%100;
        int p2 = rand()%100;
        int id1 = -1, id2 = -1;

        int propAcc = 0;
        for(int j = 0; j < length; ++j) {
            if(p1 < (prop[j] + propAcc) && id1 != -1) {
                id1 = i;
            }

            if(p2 < (prop[j] + propAcc) && id2 != -1) {
                if(i != id1) {
                    id2 = i;
                }
            }

            propAcc += prop[j];
        }

        if(id1 == -1) {
            id1 = rand()%length;
        }

        if(id2 == -1) {
            id2 = rand()%length;
        }

        r[i][0] = individuals[id1];
        r[i][1] = individuals[id2];
    }

    delete[] prop;
    return r;
}
