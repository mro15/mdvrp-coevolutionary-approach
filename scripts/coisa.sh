#! /bin/bash

####instances0="cluster.in p01.in p02.in p03.in"
####instances1="p04.in p05.in p06.in p07.in"
####instances2="p08.in p09.in p10.in p11.in p12.in"
####instances3="p13.in p14.in p15.in p16.in"
####instances4="p17.in p18.in p19.in"
####instances5="p20.in p21.in p22.in p23.in"
####instances6="pr01.in pr02.in pr03.in pr04.in"
####instances7="pr05.in pr06.in pr07.in"
####instances8="pr08.in pr09.in pr10.in pfbo.in"

####id0=0
####id1=12960
####id2=25920
####id3=42120
####id4=55080
####id5=64800
####id6=77760
####id7=90720
####id8=100440

####id=$id0
####instances=$instances0


####if [[ $1 == "1" ]]; then
####    id=$id1
####    instances=$instances1
####elif [[ $1 == "2" ]]; then
####    id=$id2
####    instances=$instances2
####elif [[ $1 == "3" ]]; then
####    id=$id3
####    instances=$instances3
####elif [[ $1 == "4" ]]; then
####    id=$id4
####    instances=$instances4
####elif [[ $1 == "5" ]]; then
####    id=$id5
####    instances=$instances5
####elif [[ $1 == "6" ]]; then
####    id=$id6
####    instances=$instances6
####elif [[ $1 == "7" ]]; then
####    id=$id7
####    instances=$instances7
####elif [[ $1 == "8" ]]; then
####    id=$id8
####    instances=$instances8
####fi

####echo $id $instances

./test.sh 1 &
./test.sh 2 &
./test.sh 3 &
./test.sh 4 &
./test.sh 5 &
./test.sh 6 &
./test.sh 7 &
./test.sh 8 &

wait
