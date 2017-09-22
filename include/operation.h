#ifndef __OPERATION_H

#include <iostream>
#include <operators.h>
#include <individual.h>

class Operation {
    private:
        MutationOperator& mutationOperator;
        CrossOverOperator& crossoverOperator;
        SelectionOperator& selectionOperator;
    public:
        Operation(  MutationOperator& mutOp,
                    CrossOverOperator& crOp,
                    SelectionOperator& selOp);
        void mutate(Individual& i);
        double mutationRatio();
        Individual** crossover(Individual** i);
        Individual*** select(Individual** i, int length);
};

#define __OPERATION_H
#endif
