reset
load "/home/vincent/.gnuplot"
unset key

file='../results/tofs_6keVee/comp.dat'
set xlabel "ToF (ns)"

set terminal postscript eps enhanced color solid "Helvetica,24"
set output '../../pics/roofit/tofs_6keVee/comp/sigma-fit.eps'
set ylabel offset 1,0 "sigma"
sM=1.0
sB=1.0
g(x)=sM*x+sB
fit g(x) file u 1:6 via sM,sB
plot file u 1:6 w points pt 7 ps 3 lc rgb prim3, g(x)
set terminal wxt 0 size 400,300
replot

set terminal postscript eps enhanced color solid "Helvetica,24"
set output '../../pics/roofit/tofs_6keVee/comp/alpha-fit.eps'
set ylabel offset 1,0 "alpha" 
aB=-1.0
aM=-0.0005
f(x)=aM/x+aB
fit f(x) file u 1:3 via aM,aB
plot file u 1:3 w points pt 7 ps 3 lc rgb prim3, f(x)
set terminal wxt 1 size 400,300
replot

set terminal postscript eps enhanced color solid "Helvetica,24"
set output '../../pics/roofit/tofs_6keVee/comp/n-fit.eps'
nB=1.0
nM=-0.0005
g(x)=nM/x+nB
fit g(x) file u 1:5 via nM,nB
set ylabel offset 1,0 "n"
plot file u 1:5 w points pt 7 ps 3 lc rgb prim3, g(x)
set terminal wxt 2 size 400,300
replot

set terminal postscript eps enhanced color solid "Helvetica,24"
set output '../../pics/roofit/tofs_6keVee/comp/yield-fit.eps'
set ylabel offset 1,0 "yield"
plot file u 1:7 w points pt 7 ps 3 lc rgb prim3
set terminal wxt 3 size 400,300
replot

set print '../results/tofs_6keVee/comp.fit'
print "sM = ", sM, "\nsB = ", sB,  "\naM = ", aM,  "\naB = ", aB,  "\nnM = ", nM,  "\nnB = ", nB