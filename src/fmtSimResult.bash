#!/bin/bash

if [ -z $1 ] 
then
    echo "I need a folder to work on, dummy!!"
    exit
else
    fldr=$1
    rm $fldr/comp.dat
fi

echo "#ToF(ns) Energy(keV) alpha        mu          n           sigma       yield" > $fldr/comp.dat
for file in 0069keV 0113keV 0152 keV 0153keV 0209keV 0298keV 0300keV 0441keV 0613keV 0908keV 1000keV 1373keV 1374keV 2097keV 2098keV 3182keV 5000keV
do
    if [ ! -e $fldr/$file.fit ]
    then
        continue
    fi

    val=`tail -n 6 $fldr/$file.fit | awk '{print $2}'`
    energy=`basename $file keV`
    eMev=`echo $energy/1000. | bc -l`
    tof=`/home/vincent/programs/executables/tofCalc -d 50.5 -e $eMev | awk '{print $3}'`
    echo $tof $energy $val >> $fldr/comp.dat
done
