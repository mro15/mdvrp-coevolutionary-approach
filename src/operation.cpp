/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <operation.h>

Operation::Operation(MutationOperator& mutOp,
                     CrossOverOperator& crOp,
                     SelectionOperator& selOp):
                     mutationOperator(mutOp),
                     crossoverOperator(crOp),
                     selectionOperator(selOp) {

}

double Operation::mutationRatio() {
    return mutationOperator.ratio();
}

void Operation::mutate(Individual& i) {
    /*
        Calls the mutatate methos of the MutateOperator.
    */
    mutationOperator.mutate(i);
    return;
}

Individual** Operation::crossover(Individual** i) {
    /*
        Calls the crossover methos of the CrossOverOperator.
    */
    return crossoverOperator.crossover(i);
}

Individual*** Operation::select(Individual** i, int length) {
     /*
        Calls the select methos of the SelectionOperator.
    */
    return selectionOperator.select(i, length);
}
