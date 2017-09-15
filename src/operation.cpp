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

void Operation::mutate(Individual& i) {
    /*
        Calls the mutatate methos of the MutateOperator.
    */
    return;
}

Individual** Operation::crossover(Individual** i) {
    /*
        Calls the crossover methos of the CrossOverOperator.
    */
    return NULL;
}

Individual*** Operation::select(Individual** i) {
     /*
        Calls the select methos of the SelectionOperator.
    */
    return NULL;
}
