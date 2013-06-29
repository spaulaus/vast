reset
load '/home/vincent/.gnuplot'
set xlabel "E_x (MeV)"
set ylabel offset 1,0 "B(GT)"
plot 'results/077cu-ban4-lower.dat' w linespoints