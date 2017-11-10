#! /bin/bash

instances=$(ls ../instances)

populationSize="10 50 100"
mutationRatio="0.0625 0.125"
iterations="10 100 1000"
redundancy="1 2 4"

migIterations=("10 5" "20 10" "100 50")

keys="seed,nIndividuals,mutRatio,iterations,duration,crtCapacity"
keys=$(echo "$keys,crtDuration,nRoutes,nMigrations,nUndoMigrations,nDepots")
keys=$(echo "$keys,minSearchSpace,maxSearchSpace,assignment,mutOp,crOp")
keys=$(echo "$keys,selOp,tournamentPool,maxMigrations,routes,graph,instance,id")

#mkfifo tmp.fifo
#psql -d experiments -U experiments -h localhost -p 5433 -c "\copy experiments ($keys) FROM './tmp.fifo' WITH DELIMITER ';'"&


#exec 3> tmp.fifo

id=0
date
for i in $instances; do
    echo "\"$keys\"" | sed -e 's/,/";"/g' > ../distances/$i.out.csv
    for p in $populationSize; do
        for it in $iterations; do
            for mr in $mutationRatio; do
                for red in $redundancy; do
                    for mode in $(seq 0 1); do
                        for (( j = 0; j < ${#migIterations[@]}; j++ )); do
                            mig=${migIterations[$j]}
                            for seed in $(seq 1 10); do
                                out=$(../main ../instances/$i $it $p $mr $red ${mig} $mode $seed| tail -n1)
                                echo "$out;\"$i\";\"$id\"" >> ../distances/$i.out.csv
                                id=$(( $id +1 ))
                            done
                        done
                    done
                done
            done
        done
    done
    echo -n "END $i - "
    date
done

#exec 3>&-
#rm tmp.fifo
