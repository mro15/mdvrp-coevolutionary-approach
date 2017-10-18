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
    bestResult=0;
    this->maxDuration = maxDurationIn;
    this->capacity = maxDurationIn;
    this->nIndividuals = nIndividualsIn;
}

void MDVRPSolver::solve( int iterations,
                         int itToMigrate,
                         int redundancy,
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
    const char* assignment = "furtherCluster";

    int length = g.nDepots()*g.maxVehicles() +1, searchSpace = 3;
    for(int i = 1; i < length; ++i) {
        population[i]->start();
    }

    for(int i = 0; i < iterations; ++i) {
        for(int j = 1; j < length; ++j) {
            population[j]->iterate();
        }
        if (i%itToMigrate == 0) {
            if(bestResult != 0) {
                double result = 0;
                Individual* ind = population[lastMigration.source]->best();
                if(ind != NULL) {
                    result += ind->duration();
                }
                ind = population[lastMigration.target]->best();
                if(ind != NULL) {
                    result += ind->duration();
                }
                if(result > bestResult && population[lastMigration.source]->canReceive(lastMigration.customer)) {
                    population[lastMigration.target]->removeClient(lastMigration.customer);
                    population[lastMigration.target]->compact(lastMigration.customer);
                    population[lastMigration.source]->addClient(lastMigration.customer);
                    population[lastMigration.source]->expand(lastMigration.customer);
                    population[lastMigration.target]->saveHistory(lastMigration);
                }
                searchSpace += (searchSpace < 7)? 1 : 0;
            }
            this->migrate(population, length, searchSpace);
        }
    }

    int capacityFeasible = 0;
    int durationFeasible = 0;
    double fitness = 0.0;
    char header[300];
    char line[300];
    sprintf(header,
        "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
        "Seed",
        "N° Individuals",
        "Mutation Ratio",
        "Iterations",
        "Duration",
        "Capacity",
        "Duration",
        "N° Routes",
        "N° Depots",
        "Assignment",
        "Mutation Operator",
        "Crossover Operator",
        "Selection Operator",
        "Routes",
        "Graph");
    for(int i = 1; i < length; ++i) {
        Individual* best = population[i]->best();
        if(best != NULL) {
            // printf("(%d): %d:", i, population[i]->depot());
            //best->debug();
            bool capacity = population[i]->underCapacity();
            bool duration = best->feasible();
            fitness += best->duration();
            // printf(": %d, %d\n",  capacity, duration);
            if (capacity) {
                ++capacityFeasible;
            }
            if (duration) {
                ++durationFeasible;
            }
        }
    }
    sprintf(line,
        "\"%d\";\"%d\";\"%lf\";\"%d\";\"%lf\";\"%d\";\"%d\";\"%d\";\"%d\";\"%s\";\"%s\";\"%s\";\"%s\";\"[",
        seed,
        nIndividuals,
        operation.mutationRatio(),
        iterations,
        fitness,
        capacityFeasible,
        durationFeasible,
        length -1,
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
    int length = nDepots*nVehicles +1;
    Population** r = new Population*[length];
    int* depots = g.depots();
    int** assignment = g.assignment();
    for (int i = 0; i < nDepots; ++i) {
        for(int j = 0; j < nVehicles; ++j) {
            int index = i*nVehicles + j +1;
            r[index] = new Population(index, g, this->operation, depots[i], maxDuration, capacity, nIndividuals);
            for(int k = 0; k < g.nVertices(); ++k) {
                if(assignment[index -1][k] == 1) {
                    r[index]->addClient(k);
                }
            }
        }
    }

    return r;
}

void MDVRPSolver::migrate(Population **p, int length, int searchSpace) {
    std::vector<Migration> migrations;
    for(int i = 1; i < length; ++i) {
        std::vector<Migration> m = p[i]->migration(searchSpace);
        migrations.insert(migrations.end(), m.begin(), m.end());
    }

    std::sort(migrations.begin(), migrations.end());
    bool did = false;
    bestResult = 0;
    while(!migrations.empty() && !did) {
        Migration& m = *migrations.begin();
        //WARN: ids das rotas como indices
        if(p[m.target]->canReceive(m.customer)) {
            bestResult = p[m.source]->best()->duration() + p[m.target]->best()->duration();
            p[m.source]->removeClient(m.customer);
            p[m.source]->compact(m.customer);
            p[m.target]->addClient(m.customer);
            p[m.target]->expand(m.customer);
            p[m.source]->saveHistory(m);
            lastMigration = m;
            did = true;
        }
        else {
            migrations.erase(migrations.begin());
        }
    }

    return;
}
