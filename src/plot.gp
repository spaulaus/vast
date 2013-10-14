reset
load '/home/vincent/.gnuplot'
set border lw 3
unset key
set xlabel "E_x (MeV)"
set terminal postscript eps enhanced color "NimbusSanL-Regu,18"

sn=4.558
qbeta=10.490

set xrange[4:11]
set x2tics ("S_n" sn, "Q_{/StandardSymL b}" qbeta)

ARSTY="nohead lc rgb comp5 lw 5 lt 5"
ARSTY1="nohead lc rgb secA3 lw 5 lt 2"
ARSTY2="nohead lc rgb secB3 lw 5 lt 7"

#---------- PLOT THE NEUTRON INDIVIDUAL STUFF --------
file0='../results/vast/working/working.dat'
set ylabel offset 1,0 "B(GT)"
set arrow 1 from sn,0 to sn,0.06 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.06 @ARSTY1
set output '../pics/vast/working/working-bgt.eps'
plot file0 u ($3+sn):8 w impulses lw 5 lc rgb prim3

set ylabel offset 1,0 "log(ft)"
set arrow 1 from sn,4.5 to sn,0.14 @ARSTY
set arrow 2 from qbeta,4.5 to qbeta,0.14 @ARSTY1
set output '../pics/vast/working/working-logft.eps'
plot file0 u ($3+sn):9 w impulses lw 5 lc rgb prim3

#---------- PLOT THE NEUTRON DENSITY STUFF --------
file1='../results/vast/working/working-nden.bgt'
set ylabel offset 1,0 "Branching Ratio / (0.001 MeV)"
set arrow 1 from sn,0 to sn,0.35 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.35 @ARSTY1
set output '../pics/vast/working/working-nden.eps'
plot file1 u 1:2 w steps lw 5 lc rgb prim3

set ylabel offset 1,0 "B(GT) / (0.001 MeV)"
set arrow 1 from sn,0 to sn,0.14 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.14 @ARSTY1
set output '../pics/vast/working/working-nden-bgt.eps'
plot file1 u 1:3 w steps lw 5 lc rgb prim3

set yrange [3.5:7.5] reverse
set ylabel "log(ft) / (0.001 MeV)"
set arrow 1 from sn,3.5 to sn,7.5 @ARSTY
set arrow 2 from qbeta,3.5 to qbeta,7.5 @ARSTY1
set output '../pics/vast/working/working-nden-logft.eps'
plot file1 u ($2 > 1e-4 ? $1 : 1/0):3 w steps lw 5 lc rgb prim3