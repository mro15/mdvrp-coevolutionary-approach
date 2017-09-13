#ifndef __OPERATION_H

#include <iostream>
#include <operators.h>
#include <individual.h>

class Operation {
    private:
        MutationOperator& mutationOperator;
        CrossOverOperator& crossOverOperator;
        SelectionOperator& selectionOperator;
    public:
        Operation(  MutationOperator& mutOp,
                    CrossOverOperator& crOp,
                    SelectionOperator& selOp);
        void mutate(Individual& i);
        Individual** crossOver(Individual** i);
        Individual*** select(Individual** i);
};

#define __OPERATION_H
#endif
