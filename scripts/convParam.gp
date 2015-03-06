reset
load '/home/vincent/.gnuplot'
set border lw 3 
#set terminal postscript eps enhanced color solid "Helvetica,18"
#file='../results/sim/8keVee-06-06-2014/convParms.dat'
file='../results/sim/working/convParms.dat'
unset key
set xlabel "ToF (ns)"

a=1.
b=1.
c=1.
d=1.
e=1.
f(x)=e*x**4+d*x**3+c*x**2+b*x+a
fit f(x) file u 2:3:4 via a,b,c,d,e
#set output '../../pics/roofit/convSigmaVsTof.eps'
set terminal wxt enhanced noraise 0
set ylabel offset 1.25,0 "{/StandardSymL s}\' (ns)"
plot file u 2:3:4 w yerrorbars pt 7 ps 3 lc rgb prim3,\
    f(x) lw 3 lc rgb comp3 lt 3

f=1.
g=-0.5
h=1.
i=1.
g(x)=i*x**3+h*x**2+g*x+f
fit g(x) file u 2:5:6 via f,g,h,i
set ylabel offset 1.25,0 "{/StandardSymL a}\'"
set terminal wxt enhanced noraise 1
#set output '../../pics/roofit/convAlphaVsTof.eps'
plot file u 2:5:6 w yerrorbars pt 7 ps 3 lc rgb prim3,\
     g(x) lw 3 lt 1 lc rgb comp3

j=1.
k=1.
l=1.
m=1.
n=1.
h(x)=j/x+k*x+l
fit h(x) file u 2:7:8 via j,k,l
set ylabel offset 1.25,0 "n\'"
#set output '../../pics/roofit/convNVsTof.eps'
set auto y
set terminal wxt enhanced noraise 2
plot file u 2:7:8 w yerrorbars pt 7 ps 3 lc rgb prim3,\
     h(x) lw 3 lt 1 lc rgb comp3

set print '../results/sim/8keVee-06-06-2014/convParam.fit'
print "alpha(tof)=i*x**3+h*x**2+g*x+f"
print "f_ = Variable(",f,", ",f_err,", \"\");"
print "g_ = Variable(",g,", ",g_err,", \"\");"
print "h_ = Variable(",h,", ",h_err,", \"\");"
print "i_ = Variable(",i,", ",i_err,", \"\");"
print ""
print "n(tof)=j/x+k*x+l"
print "j_ = Variable(",j,", ",j_err,", \"\");"
print "k_ = Variable(",k,", ",k_err,", \"\");"
print "l_ = Variable(",l,", ",l_err,", \"\");"
print ""
print "sigma(tof)=e*x**4+d*x**3+c*x**2+b*x+a"
print "a_ = Variable(",a,", ",a_err,", \"\");"
print "b_ = Variable(",b,", ",b_err,", \"\");"
print "c_ = Variable(",c,", ",c_err,", \"\");"
print "d_ = Variable(",d,", ",d_err,", \"\");"
print "e_ = Variable(",e,", ",e_err,", \"\");"
