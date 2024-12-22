set term png
set output "graphs/graphMinMax.png"
set boxwidth 0.5
set style fill solid
set datafile separator ':'

f(x,y) = x>y ? 0x32c259 : 0xe62c2c

plot "tests/lv_all_minmax.csv" using 0:(abs($2-$3)):(f($2,$3)):xtic(1) with boxes lc rgb variable
