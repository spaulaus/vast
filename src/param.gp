reset
load '/home/vincent/.gnuplot'
set border lw 3 

set terminal postscript eps enhanced color solid "NimbusSanL-Regu,18"
set output '../../pics/roofit/convSigmaVsTof.eps'

unset key
set xlabel "ToF (ns)"
set ylabel offset 1.25,0 "{/StandardSymL s}\' (ns)"

a=1.
t=0.001
f(x)=a*exp(t*x)
fit f(x) '../results/param.dat' u 1:4:5 via a,t

plot '../results/param.dat' u 1:4:5 w xerrorbars pt 7 ps 3 lc rgb prim3,\
     f(x) lw 3 lc comp3 