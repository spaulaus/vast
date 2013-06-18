#!/bin/bash

if [ -z $1 ]
then
    echo "I am missing the name of a file to work on"
    exit
else
    file=$1
fi

awk '/./' $file > $file.temp

lc=0
while read line
do 
    if (( $lc <= 4 )) 
    then
        echo "#" $line >> $file.out
    else
        set -- $line
        if echo $1 | grep -q alpha
        then
            pos=${1:5}
            alpha[$pos]=$2
            alphaErr[$pos]=$4
        elif echo $1 | grep -q mu
        then
            pos=${1:2}
            mu[$pos]=$2
            muErr[$pos]=$4
        fi
    fi
    let lc=$lc+1
done < $file.temp

let num=${#alpha[@]}-1
for i in `seq 0 $num`
do
    echo -e "$i  ${mu[$i]} ${muErr[$i]} ${alpha[$i]} ${alphaErr[$i]}" >> $file.out
done

#substitute a line the stupid way
awk '{if(NR == 4) print "# PkNum mu(ns) muErr(ns) Yield YieldErr PkDiff"; else print $0}' $file.out > $file.temp

#compute the difference in positions of the centroids for the peaks
awk '{if(NR<6) print $0; else if ($1 == 0) print $0," ", 0.0; else print $0, " ", ($2-last); last=$2}' $file.temp > $file.out

mv $file.out $file && rm $file.temp
