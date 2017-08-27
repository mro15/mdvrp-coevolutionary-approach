#ifndef __OPERATORS_H
#define __OPERATORS_H

#include <individual.h>
#include <iostream>

class MutationOperator {
    public:
        virtual Individual* mutate(Individual& i) = 0;
};

class CrossOverOperator {
    public:
        virtual Individual* crossOver(Individual* i) = 0;
};

class SelectionOperator {
    public:
        virtual Individual* select(Individual* i) = 0;
};

#endif
