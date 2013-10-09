reset
load '/home/vincent/.gnuplot'
set border lw 3
unset key
set xlabel "E_x (MeV)"
set terminal postscript eps enhanced color "NimbusSanL-Regu,18"

sn=4.558

ARSTY="nohead lc rgb comp5 lw 3 lt 5"

#---------- PLOT THE NEUTRON INDIVIDUAL STUFF --------
file0='../results/vast/working/working.bgt'
set ylabel offset 1,0 "B(GT)"
set arrow 1 from sn,0 to sn,0.06 @ARSTY
set output '../pics/vast/working/working-bgt.eps'
plot file0 u 1:2 w impulses lw 3 lc rgb prim3 

set ylabel offset 1,0 "log(ft)"
set arrow 1 from sn,4.5 to sn,7 @ARSTY
set output '../pics/vast/working/working-logft.eps'
plot file0 u 1:3 w impulses lw 3 lc rgb prim3

#---------- PLOT THE NEUTRON DENSITY STUFF --------
file1='../results/vast/working/working-nden.bgt'
set ylabel offset 1,0 "B(GT) / (0.01 MeV)"
set arrow 1 from sn,0 to sn,0.6 @ARSTY
set output '../pics/vast/working/working-nden-bgt.eps'
plot[4.5:8.5] file1 u 1:2 w steps lw 3 lc rgb prim3

set yrange [3.5:7.5] reverse
set ylabel "log(ft)"
set arrow 1 from sn,3.5 to sn,7.5 @ARSTY
set output '../pics/vast/working/working-nden-logft.eps'
plot[4.5:8.5] file1 u ($2 > 1e-4 ? $1 : 1/0):3 w steps lw 3 lc rgb prim3
