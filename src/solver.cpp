/*  Universidade Federal do Paraná
    Trabalho de Graduação
    Orientador: Eduardo j. Spinosa
    Implementação:  Lucas Fernandes de Oliveira
                    Marcela Ribeiro de Oliveira
    (NÃO SEI MAIS O QUE TEM QUE POR AQUI (?))
*/
#include <solver.h>

MDVRPSolver::MDVRPSolver(Operation& op,
                         Graph& gIn,
                         double maxDurationIn,
                         double capacityIn,
                         int nIndividualsIn):
                         operation(op),
                         g(gIn) {
    /*
        Creates a instance of the solver
    */
    this->maxDuration = maxDurationIn;
    this->capacity = capacityIn;
    this->nIndividuals = nIndividualsIn;
}

void MDVRPSolver::solve( int iterations,
                         int itToMigrate,
                         int redundancy,
                         int itToInnerMig,
                         int seed ) {
    /*
        Solve the MDVRP.
        Parameters: g, Graph that represents clients and depots
                    maxDuration, max duration of a route
                    iterations, number of iterations of the method
                    itToMigrate, iterations to create a migration

        returns an array with the ids of the vertices, orderered in the routes
        with the format: d1, c1, c2, ..., cn d1 d1, cn+1, ..., d1, d2, ...

        Routes start and finish with the same depor, the routes are
        concatenated in this array.

        returns NULL in error or impossibility to solve.
    */
    srand(seed);
    Population ** population = this->initPopulations(redundancy);
    std::vector<Migration> migrations;
    std::vector<double> results;

    int segment = g.nDepots()*g.maxVehicles() +1;
    int searchSpace = 3;
    for(int i = 1; i < segment; ++i) {
        for(int r = 0; r < redundancy; ++r) {
            population[i + r*segment]->start();
        }
    }

    this->workSpace = new bool[segment];

    for(int i = 0; i < iterations; ++i) {
        for(int j = 1; j < segment; ++j) {
            for(int r = 0; r < redundancy; ++r) {
                population[j + r*segment]->iterate();
            }
        }
        if (i%itToInnerMig == 0) {
            this->innerRouteMigration(population, segment, redundancy);
        }
        if (i%itToMigrate == 0) {
            for(unsigned int j = 0; j < migrations.size(); ++j) {
                Migration& m = migrations[j];
                double bestResult = results[j];
                double result = 0;
                for (int r = 0; r < redundancy; ++ r ) {
                    Individual* ind = population[m.source + r*segment]->best();
                    if(ind != NULL) {
                        result += ind->duration();
                    }
                    ind = population[m.target + r*segment]->best();
                    if(ind != NULL) {
                        result += ind->duration();
                    }
                }
                if ( result < bestResult &&
                     population[m.source]->canReceive(m.customer)) {

                    this->undoMigration(population, m, segment, redundancy);
                }
                searchSpace += (searchSpace < 7)? 1 : 0;
            }
            this->migrate(population, segment, redundancy, searchSpace, migrations, results);
        }
    }

    this->output(population, segment, redundancy, iterations, itToMigrate, itToInnerMig, seed);
    delete[] this->workSpace;
}

Population** MDVRPSolver::initPopulations(int redundancy) {
    /*
        Creates a set of Populations and initializes it with some clients
        but 0 individuals.
        Parameters: g, Graph that represents clients and depots
                    nDepots, the number of depots of the problem
                    nVehicles, max number of vehicles in each depot

        This member function creates the instances of Populations and add the
        clients to it.
    */
    int nDepots = g.nDepots();
    int nVehicles = g.maxVehicles();
    int segment = nDepots*nVehicles +1;
    int length = segment*redundancy;
    Population** p = new Population*[length];
    int* depots = g.depots();
    int** assignment = g.assignment();
    for (int r = 0; r < redundancy; ++r) {
        for (int i = 0; i < nDepots; ++i) {
            for(int j = 0; j < nVehicles; ++j) {
                int segIndex = i*nVehicles + j +1;
                int index = segIndex + (segment*r);
                p[index] = new Population( segIndex,
                                           g,
                                           this->operation,
                                           depots[i],
                                           maxDuration,
                                           capacity,
                                           nIndividuals);
                for(int k = 0; k < g.nVertices(); ++k) {
                    if(assignment[segIndex -1][k] == 1) {
                        p[index]->addClient(k);
                    }
                }
            }
        }
    }

    return p;
}

void MDVRPSolver::migrate(Population **p, int segment, int redundancy, int searchSpace, std::vector<Migration>& effective, std::vector<double>& results) {
    std::vector<Migration> migrations;
    effective.clear();
    results.clear();
    // This consider only the first segment, because migration is based in the
    // clients not in the indvividuals itself, in case migration
    // change reviw this code
    for(int i = 1; i < segment; ++i) {
        std::vector<Migration> m = p[i]->migration(searchSpace);
        migrations.insert(migrations.end(), m.begin(), m.end());
        workSpace[i] = false;
    }

    std::sort(migrations.begin(), migrations.end());
    while(!migrations.empty()) {
        Migration& m = *migrations.begin();
        //WARN: ids das rotas como indices
        if(workSpace[m.source] && workSpace[m.target] && p[m.target]->canReceive(m.customer)) {
            double bestResult = 0;
            for (int r = 0; r < redundancy; ++ r ) {
                double sourceDur = p[m.source + segment*r]->best()->duration();
                double targetDur = p[m.target + segment*r]->best()->duration();
                double result = sourceDur + targetDur;
                if (bestResult == 0) {
                    bestResult = result;
                }

                else if(result > bestResult) {
                    bestResult = result;
                }
                p[m.source + segment*r]->removeClient(m.customer);
                p[m.source + segment*r]->compact(m.customer);
                p[m.target + segment*r]->addClient(m.customer);
                p[m.target + segment*r]->expand(m.customer);
                p[m.source + segment*r]->saveHistory(m);
            }
            results.push_back(bestResult);
            effective.push_back(m);
        }
        else {
            migrations.erase(migrations.begin());
        }
    }

    return;
}

void MDVRPSolver::undoMigration(Population **p, const Migration& m, int segment, int redundancy) {
    for (int r = 0; r < redundancy; ++ r ) {
        p[m.target + segment*r]->removeClient(m.customer);
        p[m.target + segment*r]->compact(m.customer);
        p[m.source + segment*r]->addClient(m.customer);
        p[m.source + segment*r]->expand(m.customer);
        p[m.target + segment*r]->saveHistory(m);
    }
}

void MDVRPSolver::innerRouteMigration(Population ** p, int segment, int redundancy) {
    Individual* aux1 = NULL;
    Individual* aux2 = NULL;
    for(int i = 1; i < segment; ++i) {
        int firstIndex = rand()%this->nIndividuals;
        aux1 = p[i]->getIndividual(firstIndex);
        for(int r = 1; r < redundancy; ++r) {
            int index = rand()%this->nIndividuals;
            aux2 = p[i + segment*r]->getIndividual(index);
            p[i + segment*r]->setIndividual(aux1, index);
            aux1 = aux2;
        }
        p[i]->setIndividual(aux1, firstIndex);
    }

}

void MDVRPSolver::output(Population** population, int segment, int redundancy, int iterations, int itToMigrate, int itToInnerMig, int seed) {
    const char* assignment = "furtherCluster";
    int capacityFeasible = 0;
    int durationFeasible = 0;
    double fitness = 0.0;
    char header[300];
    char line[300];
    sprintf(header,
        "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
        "Seed",
        "N° Individuals",
        "Mutation Ratio",
        "Iterations",
        "Duration",
        "Capacity",
        "Duration",
        "N° Depots",
        "Assignment",
        "Mutation Operator",
        "Crossover Operator",
        "Selection Operator",
        "Routes",
        "Graph");
    for(int i = 1; i < segment; ++i) {
        bool capacity = true;
        bool duration = true;
        double bestFitness = 0;
        for(int r = 0; r < redundancy; ++r) {
            Individual* best = population[i + r*segment]->best();
            if(best != NULL) {
                // printf("(%d): %d:", i, population[i]->depot());
                //best->debug();
                double result = best->duration();
                if(bestFitness == 0) {
                    bestFitness = result;
                    capacity = population[i + r*segment]->underCapacity();
                    duration = best->feasible();
                }

                else if(bestFitness > result) {
                    bestFitness = result;
                    capacity = population[i + r*segment]->underCapacity();
                    duration = best->feasible();
                }
            }
        }
        fitness += bestFitness;
        // printf(": %d, %d\n",  capacity, duration);
        if (capacity) {
            ++capacityFeasible;
        }
        if (duration) {
            ++durationFeasible;
        }
    }
    sprintf(line,
        "\"%d\";\"%d\";\"%lf\";\"%d\";\"%lf\";\"(%d/%d)\";\"(%d/%d)\";\"%d\";\"%s\";\"%s\";\"%s\";\"%s\";\"[",
        seed,
        nIndividuals,
        operation.mutationRatio(),
        iterations,
        fitness,
        capacityFeasible,
        segment -1,
        durationFeasible,
        segment -1,
        g.nDepots(),
        assignment,
        operation.mutName(),
        operation.crName(),
        operation.selName());

    std::cout << header << line;
    /*for(int i = 1; i < length; ++i) {
        Individual* best = population[i]->best();
        if(best != NULL) {
            std::cout << *best << ",";
        }

        else {
            std::cout << "[],";
        }
    }*/
    std::cout << "]\";\"" /*<< g*/ << "\"\n";
}
