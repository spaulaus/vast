reset
load "/home/vincent/.gnuplot"
unset key

set terminal postscript eps enhanced color solid "Helvetica,24"
file='../results/tofSim-gated/comp.dat'
set xlabel "ToF (ns)"

set output '../../pics/roofit/tofSim-gated/comp/sigma-fit.eps'
set ylabel offset 1,0 "sigma"
m=1.0
b=1.0
g(x)=m*x+b
fit g(x) file u 1:6 via m,b
plot file u 1:6 w points pt 7 ps 3 lc rgb prim3, g(x)

set output '../../pics/roofit/tofSim-gated/comp/alpha-fit.eps'
set ylabel offset 1,0 "alpha" 
y0=-1.0
a=-0.0005
f(x)=a/x+y0
fit f(x) file u 1:3 via a,y0
plot file u 1:3 w points pt 7 ps 3 lc rgb prim3, f(x)

set output '../../pics/roofit/tofSim-gated/comp/n-fit.eps'
y1=1.0
a1=-0.0005
g(x)=a1/x+y1
fit g(x) file u 1:5 via a1,y1
set ylabel offset 1,0 "n"
plot file u 1:5 w points pt 7 ps 3 lc rgb prim3, g(x)

print m, b, a, y0, a1, y1