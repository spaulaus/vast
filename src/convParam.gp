reset
load '/home/vincent/.gnuplot'
set border lw 3 
set terminal postscript eps enhanced color solid "NimbusSanL-Regu,18"
file='../results/tofSim/convParams.dat'
unset key
set xlabel "ToF (ns)"

a=1.
b=1.
c=1.
d=1.
e=1.
f(x)=e*x**4+d*x**3+c*x**2+b*x+a
fit f(x) file u 1:2:3 via a,b,c,d,e
set output '../../pics/roofit/convSigmaVsTof.eps'
set ylabel offset 1.25,0 "{/StandardSymL s}\' (ns)"
plot file u 1:2:3 w yerrorbars pt 7 ps 3 lc rgb prim3,\
    f(x) lw 3 lc rgb comp3 lt 3

f=1.
g=-0.5
h=1.
i=1.
g(x)=i*x**3+h*x**2+g*x+f
fit g(x) file u 1:4:5 via f,g,h,i
set ylabel offset 1.25,0 "{/StandardSymL a}\'"
set output '../../pics/roofit/convAlphaVsTof.eps'
plot file u 1:4:5 w yerrorbars pt 7 ps 3 lc rgb prim3,\
     g(x) lw 3 lt 1 lc rgb comp3

j=1.
k=1.
h(x)=j/x+k
fit h(x) file u 1:6:7 via j,k
set ylabel offset 1.25,0 "n\'"
set output '../../pics/roofit/convNVsTof.eps'
plot file u 1:6:7 w yerrorbars pt 7 ps 3 lc rgb prim3,\
     h(x) lw 3 lt 1 lc rgb comp3

set print '../results/tofSim/convParam.fit'
print "sigma(tof)=e*x**4+d*x**3+c*x**2+b*x+a\n","a=",a
print "b=",b,"\nc=",c,"\nd=",d,"\ne=",e
print "alpha(tof)=i*x**3+h*x**2+g*x+f","\nf=",f
print "g=",g,"\nh=",h,"\ni=",i
print "n(tof)=j/x+k","\nj=",j,"\nk=",k