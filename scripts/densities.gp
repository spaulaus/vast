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

set ylabel offset 1,0 "Branching Ratio (/100 decays)"
set arrow 1 from sn,0.0002 to sn,0.002 @ARSTY
set arrow 2 from qbeta,0.0002 to qbeta,0.002 @ARSTY1
set output '../pics/vast/working/working-br.eps'
plot file0 u ($3+sn):7 w impulses lw 5 lc rgb prim3

set ylabel offset 1,0 "log(ft)"
set arrow 1 from sn,4.5 to sn,7 @ARSTY
set arrow 2 from qbeta,4.5 to qbeta,7 @ARSTY1
set output '../pics/vast/working/working-logft.eps'
plot file0 u ($3+sn):10 w impulses lw 5 lc rgb prim3

#---------- PLOT THE NEUTRON DENSITY STUFF --------
file1='../results/vast/working/working.bgt'
set ylabel offset 1,0 "Branching Ratio / (0.001 MeV)"
set arrow 1 from sn,0 to sn,0.0004 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.0004 @ARSTY1
set output '../pics/vast/working/working-nden.eps'
plot file1 u 1:3:4 w filledcurve lc rgb comp5, '' u 1:2 w steps lc rgb prim3 lw 3

set ylabel offset 1,0 "B(GT) / (0.001 MeV)"
set arrow 1 from sn,0 to sn,0.00018 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.00018 @ARSTY1
set output '../pics/vast/working/working-nden-bgt.eps'
plot file1 u 1:6:7 w filledcurve lc rgb comp5, '' u 1:5 w steps lc rgb prim3 lw 3