#! /bin/bash

instances=$(ls ../instances)

populationSize="10 50 100"
mutationRatio="0.0625 0.125 0.001"
iterations="1000 10000 100000"
migIterations=("10 5" "20 10" "100 50")
redundancy="1 2 4"


keys="seed,nIndividuals,nPops,mutRatio,iterations,duration,crtCapacity"
keys=$(echo "$keys,crtDuration,nRoutes,nMigrations,nUndoMigrations,nDepots")
keys=$(echo "$keys,minSearchSpace,maxSearchSpace,assignment,mutOp,crOp")
keys=$(echo "$keys,selOp,tournamentPool,maxMigrations,routes,graph,instance,id")

#mkfifo tmp.fifo
#psql -d experiments -U experiments -h localhost -p 5433 -c "\copy experiments  FROM '/tmp/p04.in.out.csv' WITH CSV DELIMITER ';' HEADER"


#exec 3> tmp.fifo

instances0="cluster.in p01.in p02.in p03.in"
instances1="p04.in p05.in p06.in p07.in p08.in p09.in p10.in p11.in p12.in"
instances2="p13.in p14.in p15.in p16.in p17.in p18.in p19.in"
instances3="p20.in p21.in p22.in p23.in pr01.in pr02.in pr03.in pr04.in"
instances4="pr05.in pr06.in pr07.in pr08.in pr09.in pr10.in pfbo.in"

instances0="cluster.in p01.in p02.in p03.in"
instances1="p04.in p05.in p06.in p07.in"
instances2="p08.in p09.in p10.in p11.in p12.in"
instances3="p13.in p14.in p15.in p16.in"
instances4="p17.in p18.in p19.in"
instances5="p20.in p21.in p22.in p23.in"
instances6="pr01.in pr02.in pr03.in pr04.in"
instances7="pr05.in pr06.in pr07.in"
instances8="pr08.in pr09.in pr10.in pfbo.in"

id0=0
id1=12960
id2=25920
id3=42120
id4=55080
id5=64800
id6=77760
id7=90720
id8=100440

id=$id0
instances=$instances0


if [[ $1 == "1" ]]; then
    id=$id1
    instances=$instances1
elif [[ $1 == "2" ]]; then
    id=$id2
    instances=$instances2
elif [[ $1 == "3" ]]; then
    id=$id3
    instances=$instances3
elif [[ $1 == "4" ]]; then
    id=$id4
    instances=$instances4
elif [[ $1 == "5" ]]; then
    id=$id5
    instances=$instances5
elif [[ $1 == "6" ]]; then
    id=$id6
    instances=$instances6
elif [[ $1 == "7" ]]; then
    id=$id7
    instances=$instances7
elif [[ $1 == "8" ]]; then
    id=$id8
    instances=$instances8
fi

echo $id $instances
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
