#!/bin/bash
cgm=../cgm_exec/cgm

#user must define the values for the following
#4 variables (see readme)
file="working-cut.mgb"
Z="029"
A="077"
number=1

cp $file ../data/bstrength/strint"$Z""$A".dat

for i in `seq 1 $number`; do
    cp GSinp"$i".dat ../data/levels/GSinp.dat

    $cgm -z$Z -a$A -b > "$file".spectra"$i"

    rm -f ../data/levels/GSinp.dat
done

rm -f ../data/bstrength/*

exit $?
