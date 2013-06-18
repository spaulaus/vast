reset
load "/home/vincent/.gnuplot"
unset key

file="../results/tofSim/comp.dat"

set xlabel "Energy (MeV)"
set terminal postscript eps enhanced solid color "Helvetica, 24"

#---------- PLOTTING VS. E ----------
set ylabel offset 1,0 "alpha"
set output "../../pics/roofit/tofSim/comp/alpha-e.eps"
plot file u 2:3 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "mu"
set output "../../pics/roofit/tofSim/comp/mu-e.eps"
plot file u 2:4 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "n"
set output "../../pics/roofit/tofSim/comp/n-e.eps"
plot file u 2:5 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "sigma"
set output "../../pics/roofit/tofSim/comp/sigma-e.eps"
plot file u 2:6 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "Yield"
set output "../../pics/roofit/tofSim/comp/yield-e.eps"
plot file u 2:7 w points pt 7 ps 3 lc rgb prim3

#---------- PLOTTING VS. T ----------
set ylabel offset 1,0 "alpha"
set xlabel "ToF (ns)"
set output "../../pics/roofit/tofSim/comp/alpha-t.eps"
plot file u 1:3 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "mu"
set output "../../pics/roofit/tofSim/comp/mu-t.eps"
plot file u 1:4 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "n"
set output "../../pics/roofit/tofSim/comp/n-t.eps"
plot file u 1:5 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "sigma"
set output "../../pics/roofit/tofSim/comp/sigma-t.eps"
plot file u 1:6 w points pt 7 ps 3 lc rgb prim3

set ylabel offset 1,0 "Yield"
set output "../../pics/roofit/tofSim/comp/yield-t.eps"
plot file u 1:7 w points pt 7 ps 3 lc rgb prim3

