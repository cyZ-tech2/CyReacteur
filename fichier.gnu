set term png size 960,720
set output "graphs/graphMinMax.png"
set boxwidth 0.5
set style fill solid
set datafile separator ':'
set xlabel "Stations LV"
set ylabel "Différence capacité-consommation"
set key noautotitle

# Cette fonction retourne le code hexa de la couleur rouge si la capacité est inférieure à la consommation (sousproduction) et celui de la couleur verte sinon

f(x,y) = x<y ? 0xe62c2c : 0x32c259 # Utilisée pour les couleurs

# On créé le graphique : every ::1 permet d'ignorer l'en-tête ; la hauteur des colonnes représente la valeur absolue de la différence entre capacité et consommation

plot "tests/lv_all_minmax.csv" every ::1 using 0:(abs($2-$3)):(f($2,$3)):xtic(1) with boxes lc rgb variable
