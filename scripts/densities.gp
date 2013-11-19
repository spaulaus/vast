reset
load '/home/vincent/.gnuplot'
set border lw 3
unset key
set xlabel "E_x (MeV)"
set terminal postscript eps enhanced color solid "NimbusSanL-Regu,18"

sn=4.558
qbeta=10.490
res=0.001

set xrange[4:11]
set x2tics ("S_n" sn, "Q_{/StandardSymL b}" qbeta)

ARSTY="nohead lc rgb secB1 lw 5 lt 5"
ARSTY1="nohead lc rgb secA3 lw 5 lt 2"
ARSTY2="nohead lc rgb secB3 lw 5 lt 7"

SENS="'../results/vast/working/working.sens' u 1:($4*res):($5*res) w yerrorbars lc rgb secB1 ps 1.5 lw 2"

#---------- PLOT THE NEUTRON INDIVIDUAL STUFF --------
file0='../results/vast/working/working.dat'
set ylabel offset 1,0 "I_n (/100 decays)"
set arrow 1 from sn,0.0002 to sn,0.002 @ARSTY
set arrow 2 from qbeta,0.0002 to qbeta,0.002 @ARSTY1
set output '../pics/vast/working/working-br.eps'
plot file0 u ($3+sn):7 w impulses lw 5 lc rgb prim3

set ylabel offset 1,0 "B(GT)"
set arrow 1 from sn,0 to sn,0.06 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.06 @ARSTY1
set output '../pics/vast/working/working-bgt.eps'
plot [][0:0.06] file0 u ($3+sn):8 w impulses lw 5 lc rgb prim3, @SENS


#---------- PLOT THE NEUTRON DENSITY STUFF --------
file1='../results/vast/working/working.bgt'
set ylabel offset 1,0 "I_n / (0.001 MeV)"
set arrow 1 from sn,0 to sn,0.0004 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.0004 @ARSTY1
set output '../pics/vast/working/working-nden.eps'
plot [][0:0.0004]file1 u 1:3:4 w filledcurve lc rgb comp5, '' u 1:2 w steps lc rgb prim3 lw 3

set ylabel offset 1,0 "B(GT) / (0.001 MeV)"
set arrow 1 from sn,0 to sn,0.00018 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.00018 @ARSTY1
set output '../pics/vast/working/working-nden-bgt.eps'
plot [4:11][0:0.00018] file1 u 1:6:7 w filledcurve lc rgb comp5, '' u 1:5 w steps lc rgb prim3 lw 3, @SENS