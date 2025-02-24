reset
load '/home/vincent/.gnuplot'
set border lw 3
unset key
set xlabel "E_x (MeV)"
set terminal postscript eps enhanced color solid "NimbusSanL-Regu,18"

sn=4.5575
qbeta=10.49
res=0.001

set xrange[4:11]
set x2tics ("S_n" sn, "Q_{/StandardSymL b}" qbeta)

ARSTY="nohead lc rgb secB1 lw 5 lt 5"
ARSTY1="nohead lc rgb secA3 lw 5 lt 2"
ARSTY2="nohead lc rgb secB3 lw 5 lt 7"

SENS="'../results/vast/working-bkp/working.sens' u 1:($4*res):($5*res) w yerrorbars lc rgb secB1 ps 1.5 lw 2"

#---------- PLOT THE NEUTRON INDIVIDUAL STUFF --------
file0='../results/vast/working-bkp/working.dat'
set ylabel offset 1,0 "I_n (/100 decays)"
set arrow 1 from sn,0.002 to sn,0.014 @ARSTY
set arrow 2 from qbeta,0.002 to qbeta,0.014 @ARSTY1
set terminal wxt 0
#set output '../pics/vast/working-bkp/working-br.eps'
plot file0 u ($3):7 w impulses lw 5 lc rgb prim3

set ylabel offset 1,0 "B(GT)"
set arrow 1 from sn,0 to sn,0.06 @ARSTY
set arrow 2 from qbeta,0 to qbeta,0.06 @ARSTY1
set terminal wxt 1
#set output '../pics/vast/working-bkp/working-bgt.eps'
set auto yx
plot file0 u 3:9 w impulses lw 5 lc rgb prim3#, @SENS

#---------- PLOT THE NEUTRON DENSITY STUFF --------
highRange=0.0004

file1='../results/vast/working-bkp/working.bgt'
set ylabel offset 1,0 "I_n / (0.5 MeV)"
set arrow 1 from sn,0 to sn,highRange @ARSTY
set arrow 2 from qbeta,0 to qbeta,highRange @ARSTY1
#set output '../pics/vast/working-bkp/working-nden.eps'
set terminal wxt 2
plot file1 u ($1+res*0.5):2:3:4 w yerrorbars ls 2 ps 0,\
     '' u 1:2 w steps ls 1

set ylabel offset 1,0 "B(GT) / (0.5 MeV)"
set arrow 1 from sn,0 to sn,highRange @ARSTY
set arrow 2 from qbeta,0 to qbeta,highRange @ARSTY1
#set output '../pics/vast/working-bkp/working-nden-bgt.eps'
set terminal wxt 3
plot file1 u ($1+res*0.5):5:6:7 w yerrorbars ls 2 ps 0,\
     '' u 1:5 w steps ls 1#, @SENS
