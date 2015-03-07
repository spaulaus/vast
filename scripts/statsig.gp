reset
load '~/.gnuplot'
unset key

file="../results/tof/working/working.fit"

set xlabel "Peak Number"
set ylabel "Yield / YieldError"

plot file u 1:($4/$5) w linespoints ls 1 