#! /bin/bash

instances=$(ls ../instances)

populationSize="10 50 100"
mutationRatio="0.0625 0.125 0.001"
iterations="1000 10000 100000"
redundancy="1 2 4"

for i in $instances; do
    echo '"Seed";"N° Individuals";"Mutation Ratio";"Iterations";"Duration";"Capacity";"Duration";"N° Routes";"Assignment";"Mutation Operator";"Crossover Operator";"Selection Operator";"Routes";"Graph"' > ../distances/$i.out.csv
    for p in $populationSize; do
        for it in $iterations; do
            for mr in $mutationRatio; do
                for red in $redundancy; do
                    ../main ../instances/$i $it 10 $p $mr $red 5 1| tail -n1 >> ../distances/$i.out.csv
                done
            done
        done
    done
done
