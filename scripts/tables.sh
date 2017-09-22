#! /bin/bash

instances=$(ls ../instances)

populationSize="10 100 1000"
mutationRatio="0.125 0.25 0.5"
iterations="1 10 100 1000 10000"

for i in $instances; do
    echo '"N° Individuals";"Mutation Ratio";"Iterations";"Duration";"Capacity";"Duration"' > ../distances/$i.out.csv
    for p in $populationSize; do
        for it in $iterations; do
            for mr in $mutationRatio; do
                ../main ../instances/$i $it $p $mr | tail -n1 >> ../distances/$i.out.csv
            done
        done
    done
done
