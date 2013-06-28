#!/bin/bash

if [ -z $1 ]
then
    echo "I am missing the name of a file to work on"
    exit
else
    file=$1
fi

dir=`dirname $1`
file=`basename $1 .fit`
name="$dir/$file"

awk '/./' $name.fit > $name.temp

lc=0
while read line
do 
    if (( $lc <= 4 )) 
    then
        echo "#" $line >> $name.out
    else
        set -- $line
        if echo $1 | grep -q yield
        then
            pos=`echo ${1:5} | bc`
            yield[$pos]=$2
            yieldErr[$pos]=$4
        elif echo $1 | grep -q mu
        then
            pos=`echo ${1:2} | bc`
            mu[$pos]=$2
            muErr[$pos]=$4
        fi
    fi
    let lc=$lc+1
done < $name.temp

let num=${#yield[@]}-1
for i in `seq 0 $num`
do
    echo -e "$i  ${mu[$i]} ${muErr[$i]} ${yield[$i]} ${yieldErr[$i]}" >> $name.out
done

#substitute a line the stupid way
awk '{if(NR == 4) print "# PkNum mu(ns) muErr(ns) Yield YieldErr PkDiff"; else print $0}' $name.out > $name.temp

#compute the difference in positions of the centroids for the peaks
awk '{if(NR<6) print $0; else if ($1 == 0) print $0," ", 0.0; else print $0, " ", ($2-last); last=$2}' $name.temp > $name.out

rm $name.temp
