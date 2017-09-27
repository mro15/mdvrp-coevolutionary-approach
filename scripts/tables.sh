#! /bin/bash

instances=$(ls ../instances)

populationSize="10 50 100"
mutationRatio="0.0625 0.125"
iterations="10 100 1000"

for i in $instances; do
    echo '"N° Individuals";"Mutation Ratio";"Iterations";"Duration";"Capacity";"Duration"' > ../distances/$i.out.csv
    for p in $populationSize; do
        for it in $iterations; do
            for mr in $mutationRatio; do
                for j in $(seq 1 10); do
                ../main ../instances/$i $it $p $mr | tail -n1 >> ../distances/$i.out.csv
                done
            done
        done
    done
done
