#ifndef __OPERATORS_H
#define __OPERATORS_H

#include <individual.h>
#include <iostream>
#include <cstdlib>

class Operator {
    protected:
        const char* _name;
    public:
        const char* name();
};

class MutationOperator: public Operator {
    public:
        virtual void mutate(Individual& i) = 0;
        virtual double ratio() = 0;
};

class CrossOverOperator: public Operator {
    public:
        virtual Individual** crossover(Individual** i) = 0;
};

class SelectionOperator: public Operator {
    public:
        virtual Individual*** select(Individual** i, int length) = 0;
};

class MutSwap : public MutationOperator {
    private:
        double _probability;
        double _ratio;
    public:
        MutSwap(double probability);
        void mutate(Individual& i);
        double ratio();
};

class CrCut : public CrossOverOperator {
    private:
        int* workSpace;
        int length;
    public:
        CrCut(int nCustomers);
        Individual** crossover(Individual** i);
};

class SelRol : public SelectionOperator {
    public:
        SelRol();
        Individual*** select(Individual** i, int length);
};
#endif
