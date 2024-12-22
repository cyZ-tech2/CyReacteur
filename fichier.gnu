set term png size 960,720
set output "graphs/graphMinMax.png"
set boxwidth 0.5
set style fill solid
set datafile separator ':'
set xlabel "Stations LV"
set ylabel "Différence capacité-consommation"
set key noautotitle

f(x,y) = x>y ? 0x32c259 : 0xe62c2c

plot "tests/lv_all_minmax.csv" every ::1 using 0:(abs($2-$3)):(f($2,$3)):xtic(1) with boxes lc rgb variable
