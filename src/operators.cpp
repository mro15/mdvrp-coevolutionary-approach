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

CrCut::CrCut(int nCustomers) {
    this->length = nCustomers;
    this->workSpace = new int[nCustomers];
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
    Individual** offspring = new Individual*[2];
    offspring[0] = new Individual(*i[0]);
    offspring[1] = new Individual(*i[1]);

    std::vector<int> cpy0 = std::vector<int>(offspring[0]->customers());
    std::vector<int> cpy1 = std::vector<int>(offspring[1]->customers());

    std::vector<int>& customer0 = offspring[0]->customers();
    std::vector<int>& customer1 = offspring[1]->customers();
    int cutPos = rand()%cpy0.size();
    std::vector<int>::iterator erasePos = customer0.begin() + cutPos;
    customer0.erase(erasePos, customer0.end());
    erasePos = customer1.begin() + cutPos;
    customer1.erase(erasePos, customer1.end());
    for(int j = 0; j < this->length; ++j) {
        workSpace[j] = 0;
    }

    for(std::vector<int>::iterator it = customer0.begin(); it != customer0.end(); ++it) {
        workSpace[*it] = 1;
    }

    for(std::vector<int>::iterator it = cpy1.begin(); it != cpy1.end(); ++it) {
        if(workSpace[*it] == 0) {
            customer0.push_back(*it);
            workSpace[*it] = 1;
        }
    }

    for(int j = 0; j < this->length; ++j) {
        workSpace[j] = 0;
    }

    for(std::vector<int>::iterator it = customer1.begin(); it != customer1.end(); ++it) {
        workSpace[*it] = 1;
    }

    for(std::vector<int>::iterator it = cpy0.begin(); it != cpy0.end(); ++it) {
        if(workSpace[*it] == 0) {
            customer1.push_back(*it);
            workSpace[*it] = 1;
        }
    }

    return offspring;
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

        while(id2 == -1 ||  id2 == id1) {
            id2 = rand()%length;
        }

        r[i][0] = individuals[id1];
        r[i][1] = individuals[id2];

        if(id1 == id2) {
            printf("Deu RUIM\n");
        }
    }

    delete[] prop;
    return r;
}
