#ifndef __OPERATORS_H
#define __OPERATORS_H

#include <individual.h>
#include <iostream>
#include <cstdlib>

class MutationOperator {
    public:
        virtual void mutate(Individual& i) = 0;
};

class CrossOverOperator {
    public:
        virtual Individual** crossover(Individual** i) = 0;
};

class SelectionOperator {
    public:
        virtual Individual*** select(Individual** i, int length) = 0;
};

class MutSwap : public MutationOperator {
    double _probability;
    public:
        MutSwap(double probability);
        void mutate(Individual& i);
};

class CrCut : public CrossOverOperator {
    double _probability;
    public:
        Individual** crossover(Individual** i);
};

class SelRol : public SelectionOperator {
    public:
        Individual*** select(Individual** i, int length);
};
#endif
