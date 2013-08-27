reset
load '/home/vincent/.gnuplot'
set terminal postscript eps enhanced color solid "NimbusSanL-Regu,18"

e1=0.59856
e2=0.69772

set arrow 1 from 4.558,0 to 4.558,2000 nohead lc -1
set label 1 "S_n" at 4.6,1800 font "NimbusSanL-Regu,18"

set yrange [0:2000]
set xrange [4.5:7.5]

set xlabel "E_x (MeV)"
set ylabel offset 1,0 "Yield/{/StandardSymL e_g}"
set output '../pics/bgt/comp-S-02-04.eps'
plot 'results/077cu-ban4-lower.dat' u 1:5:2 w boxerrorbars t "Singles",\
     'results/077cu-ban4-lower-02Plus.dat' u 1:5:2 w boxerrorbars t "2+",\
     'results/077cu-ban4-lower-04Plus.dat' u 1:5:2 w boxerrorbars t "4+"\

set output '../pics/bgt/comp-S-02-04-Base.eps'
plot 'results/077cu-ban4-lower.dat' u 1:5:2 w xerrorbars t "Singles",\
     'results/077cu-ban4-lower-02Plus.dat' u ($1-e1):5:2 w boxerrorbars t "2+",\
     'results/077cu-ban4-lower-04Plus.dat' u ($1-e1-e2):5:2 w boxerrorbars t "4+"\

     