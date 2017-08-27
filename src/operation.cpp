#include <operation.h>

Operation::Operation(MutationOperator* mutOp,
                     CrossOverOperator* crOp,
                     SelectionOperator* selOp) {

}

Individual* Operation::mutate(Individual& i) {
    /*
        Calls the mutatate methos of the MutateOperator.
    */
    return NULL;
}

Individual* Operation::crossOver(Individual* i) {
    /*
        Calls the crossOver methos of the CrossOverOperator.
    */
    return NULL;
}

Individual* Operation::select(Individual* i) {
     /*
        Calls the select methos of the SelectionOperator.
    */
    return NULL;
}
