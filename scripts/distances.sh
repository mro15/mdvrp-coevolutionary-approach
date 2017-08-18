#! /bin/bash

instances=$(ls ../instances)

for i in $instances; do
    ../main ../instances/$i > ../distances/$i
done
