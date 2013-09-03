reset
load '/home/vincent/.gnuplot'
set terminal postscript eps enhanced color solid "NimbusSanL-Regu,18"

e1=0.59856
e2=0.69772

set key left top

set arrow 1 from 4.558,0 to 4.558,2000 nohead lc -1
set label 1 "S_n" at 4.6,1800 font "NimbusSanL-Regu,18"

set xlabel "E_x (MeV)"
set ylabel offset 1,0 "Yield/{/StandardSymL e_g}"
set output '../pics/bgt/comp-S-02-04-noConv.eps'
plot 'results/077cu-ban4-lower-noConv.dat' u 3:7:4 w boxes t "Singles",\
     'results/077cu-ban4-lower-02Plus-noConv.dat' u 3:7:4 w boxes t "2+",\
     'results/077cu-ban4-lower-04Plus-noConv.dat' u 3:7:4 w boxes t "4+"\

set output '../pics/bgt/comp-S-02-04-Base-noConv.eps'
plot 'results/077cu-ban4-lower-noConv.dat' u 3:7:4 w boxes t "Singles",\
     'results/077cu-ban4-lower-02Plus-noConv.dat' u ($3-e1):7:4 w boxes t "2+",\
     'results/077cu-ban4-lower-04Plus-noConv.dat' u ($3-e1-e2):7:4 w boxes t "4+"\

unset arrow 1
unset label 1
set key inside right top
set output '../pics/bgt/comp-S-02-04-tof-noConv.eps'
plot 'results/077cu-ban4-lower-noConv.dat' u 1:7:2 w boxes t "Singles",\
     'results/077cu-ban4-lower-02Plus-noConv.dat' u 1:7:2 w boxes t "2+",\
     'results/077cu-ban4-lower-04Plus-noConv.dat' u 1:7:2 w boxes t "4+"\

     

     