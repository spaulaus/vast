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

rm -f $file.temp

let num=${#alpha[@]}-1
for i in `seq 0 $num`
do
    echo -e "$i  ${mu[$i]} ${muErr[$i]} ${alpha[$i]} ${alphaErr[$i]}" >> $file.out
done

mv $file.out $file
