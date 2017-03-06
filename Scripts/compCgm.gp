reset
load '/home/vincent/.gnuplot'
set border lw 3
set ylabel "I_n (arb)"
set xlabel "E_n (MeV)"
set key spacing 1.5
set xrange[0:5]
#set terminal postscript eps enhanced color solid "NimbusSanL-Regu, 26"

sn=4.5575

fileA='../results/vast/working/working.bgt'
fileB='../data/theory/bertolli/working.mgb.spectra1'

stats fileA u 2 name 'exp' nooutput
stats fileB u 5 name 'theory' nooutput

f(x, low, high) = (x - low) / (high - low)

#set output '../pics/theory/compMgb.eps'
plot fileB u (($2+$3)*0.5):(f($5,theory_min,theory_max)) w steps lw 5 lc rgb prim3 t "Theory",\
     fileA u ($1-sn):(f($2,exp_min,exp_max)) w steps lw 5 lc rgb secB5 t "Exp"

