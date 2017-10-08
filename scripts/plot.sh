#! /bin/bash

instances=$(ls ../instances)

declare -a r
declare -a g
declare -a b

r[0]=0
g[0]=0
b[0]=0
r[1]=127
g[1]=0
b[1]=0
r[2]=0
g[2]=127
b[2]=0
r[3]=0
g[3]=0
b[3]=127
r[4]=127
g[4]=127
b[4]=0
r[5]=127
g[5]=0
b[5]=127
r[6]=0
g[6]=127
b[6]=127
r[7]=102
g[7]=51
b[7]=0
r[8]=102
g[8]=0
b[8]=204
r[9]=0
g[9]=254
b[9]=153

for i in $instances; do
    echo "set title \"$i\"" > ../plot/$i.plot
    echo "set terminal png size 1200,900" >> ../plot/$i.plot
    echo "set output \"$i.png\"" >> ../plot/$i.plot
    echo "set xzeroaxis" >> ../plot/$i.plot
    echo "set yzeroaxis" >> ../plot/$i.plot
    echo "plot \\" >> ../plot/$i.plot
    ../main ../instances/$i 100 10 100 0.125 1> tmp.csv
    cols=$(head -n1 tmp.csv | sed -e 's/\ /_/g' | sed -e 's/\;/ /g' | sed -e 's/\"//g')
    max=0
    k=1
    depots=0
    data=""
    for c in $cols; do
        if [[ $c == "N°_Routes" ]]; then
            max=$(tail -n1 tmp.csv | cut -f$k -d';' | sed -e 's/\"//g');
        fi
        if [[ $c == "N°_Depots" ]]; then
            depots=$( tail -n1 tmp.csv | cut -f$k -d';' | sed -e 's/\"//g');
        fi
        if [[ $c == "Graph" ]]; then
            data=$k
        fi
        k=$(( $k +1))
    done

    vehicles=$(($max/$depots))
    inc=0
    count=0
    colorid=0
    rvalue=$((${r[0]} + $inc))
    gvalue=$((${g[0]} + $inc))
    bvalue=$((${b[0]} + $inc))
    color=$(printf "#%02X%02X%02X" $rvalue $gvalue $bvalue)
    echo "'-' using 1 : 2 with points lc rgbcolor \"$color\" lw \"3px\" title 'Depots', \\"\
     >> ../plot/$i.plot
    colorid=1
    for j in $(seq 1 $max); do
        rvalue=$((${r[$colorid]} + $inc))
        gvalue=$((${g[$colorid]} + $inc))
        bvalue=$((${b[$colorid]} + $inc))
        color=$(printf "#%02X%02X%02X" $rvalue $gvalue $bvalue)
        echo -n "'-' using 1 : 2 with points lc rgbcolor \"$color\" lw \"3px\" title 'route $j'"\
             >> ../plot/$i.plot
        if [[ $j -eq $max ]]; then
            echo "" >> ../plot/$i.plot
        else
            echo ",  \\"     >> ../plot/$i.plot
        fi
        inc=$(( $inc + 32))
        count=$(( $count + 1))
        if [[ $count -eq $vehicles ]]; then
            inc=0
            count=0
            colorid=$(($colorid +1))
        fi
        #cat tmp.out | grep "route: $j" | sed -e "s/x:\ //" | \
        #   sed -e "s/y:\ //" | sed -e "s/route: $j//"
    done
    echo >> ../plot/$i.plot
    for j in $(seq 0 $max); do
        tail -n1 tmp.csv | cut -d';' -f$data | sed -e 's/\"\[\|,\ \]//g' | sed -e 's/\}\,/}\n/g' \
        | grep "route: $j " | sed -e "s/x:\ //" | \
           sed -e "s/y:\ //" | cut -d',' -f2-3 | sed -e 's/^\ //'  >> ../plot/$i.plot
        if [[ $j -ne $max ]]; then
            echo "e" >> ../plot/$i.plot
        fi
    done

done

rm tmp.csv

####cat tmp.out | cut -d';' -f14 | sed -e 's/\"\[\|,\ \]//g' | sed -e 's/\}\,/}\n/g'
