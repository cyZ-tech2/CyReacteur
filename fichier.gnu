set term png
set output "graphs/graphMinMax.png"
set boxwidth 0.5
set style fill solid
set datafile separator ':'

f(x,y) = x>y ? 0x00FF00 : 0xFF0000

plot "tests/lv_all_minmax.csv" using 0:(abs($2-$3)):(f($2,$3)):xtic(1) with boxes lc rgb variable
