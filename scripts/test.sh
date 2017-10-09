#! /bin/bash

(cd ..; make)
instances=$(ls ../instances)

populationSize="10 50 100"
mutationRatio="0.0625 0.125"
iterations="10 100 1000"

id=0

declare -A idx

../main ../instances/cluster.in 1 1 2 0.125 1 > tmp.csv
cols=$(head -n1 tmp.csv | sed -e 's/\ /_/g' | sed -e 's/\;/ /g' | sed -e 's/\"//g')
k=0
keys="nRoutes,nIndividuals,mutationRatio,iterations,duration,constCapacity"
keys=$(echo "$keys,constDuration,nRoutes,assignment,mutOp,crOp,selOp,routes,graph")
####for c in $cols; do
####    if [[ $c == "Seed" ]]; then
####        idx["nRoutes"]=$k
####    elif [[ $c == "N°_Individuals" ]]; then
####        idx["nIndividuals"]=$k
####    elif [[ $c == "Mutation_Ratio" ]]; then
####        idx["mutationRatio"]=$k
####    elif [[ $c == "Iterations" ]]; then
####        idx["iterations"]=$k
####    elif [[ $c == "Duration" ]]; then
####        idx["duration"]=$k
####    elif [[ $c == "Capacity_Const" ]]; then
####        idx["constCapacity"]=$k
####    elif [[ $c == "Duration_Const" ]]; then
####        idx["constDuration"]=$k
####    elif [[ $c == "N°_Routes" ]]; then
####        idx["nRoutes"]=$k
####    elif [[ $c == "Assignment" ]]; then
####        idx["assignment"]=$k
####    elif [[ $c == "Mutation_Operator" ]]; then
####        idx["mutOp"]=$k
####    elif [[ $c == "Crossover_Operator" ]]; then
####        idx["crOp"]=$k
####    elif [[ $c == "Selection_Operator" ]]; then
####        idx["selOp"]=$k
####    elif [[ $c == "Routes" ]]; then
####        idx["routes"]=$k
####    elif [[ $c == "Graph" ]]; then
####        idx["graph"]=$k
####    fi
####    k=$(( $k +1))
####done

####idx["instance"]=$k
####k=$(( $k +1))
####idx["id"]=$k

mkfifo tmp.fifo
exec 3 > tmp.fifo

psql -f "COPY experiments ($keys) FROM tmp.fifo WITH DELIMITER ';'"

for i in $instances; do
    for p in $populationSize; do
        for it in $iterations; do
            for mr in $mutationRatio; do
                #for j in $(seq 1 10); do
                out=$(../main ../instances/$i $it 10 $p $mr 1 | tail -n1)
                echo "$out;\"$i\";\"$id\"" >&3
                #done
            done
        done
    done
done

exec 3 >&-
rm tmp.fifo
rm.tmp.csv
