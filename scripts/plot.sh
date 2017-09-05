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
    ../main ../instances/$i > tmp.out
    max=$(cat tmp.out | cut -d: -f4 | sort -n | sed -e "s/^ //"| tail -n1)
    depots=$(cat tmp.out | cut -d: -f4 | grep "0" | wc -l)
    vehicles=$(( $max/$depots))
    inc=0
    count=0
    for j in $(seq 0 $max); do
        rvalue=$((${r[j]} + $inc))
        gvalue=$((${g[j]} + $inc))
        bvalue=$((${b[j]} + $inc))
        color=$(printf "#%02X%02X%02X" $rvalue $gvalue $bvalue)
        echo -n "'-' using 1 : 2 with points lc rgbcolor \"$color\" lw \"2px\" title 'route $j'"\
             >> ../plot/$i.plot
        if [[ $j -eq $max ]]; then
            echo "" >> ../plot/$i.plot
        else
            echo ",  \\"     >> ../plot/$i.plot
        fi
        inc=$(( $inc + 16))
        count=$(( $count + 1))
        if [[ $j -eq $max ]]; then
            inc=0
            count=0
        fi
        #cat tmp.out | grep "route: $j" | sed -e "s/x:\ //" | \
        #   sed -e "s/y:\ //" | sed -e "s/route: $j//" 
    done
    echo >> ../plot/$i.plot
    for j in $(seq 0 $max); do
        cat tmp.out | grep "route: $j:" | sed -e "s/x:\ //" | \
           sed -e "s/y:\ //" | sed -e "s/ route: $j://"  >> ../plot/$i.plot
        if [[ $j -ne $max ]]; then
            echo "e" >> ../plot/$i.plot
        fi
    done

done
