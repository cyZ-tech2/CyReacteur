#!/bin/bash

aide(){
	#message d'aide
	return 0
}

for i in $*; do # aide
	if [ "$i" = "-h" ] ; then
		aide
		exit 0
	fi
done

if [[ "$1" != *.csv ]] ; then # verif fichier de donnees
	echo "fichier d'entrée invalide"
	aide
	exit 1

elif [ "$2" != "hvb" ] && [ "$2" != "hva" ] && [ "$2" != "lv" ] ; then   # verif type de station
	echo "type de station invalide"
	aide
	exit 1

elif [ "$3" != "comp" ] && [ "$3" != "indiv" ] && [ "$3" != "all" ] ; then # verif type de consommateur
	echo "type de consommateur invalide"
	aide
	exit 1

elif [[ "$*" = *hv?' 'all* ]] || [[ "$*" = *hv?' 'indiv* ]] ; then # verif option authorisée
	echo "option non autorisée"
	aide
	exit 1
fi

if [ ! -d tmp ] ; then # verif dossier tmp
	mkdir tmp
else
	rm -r tmp/*
fi

case $2 in #filtrage
	hvb) grep '^[^-;]*;[^-;]*;-;-;-;-' "$1" > "tmp/filtreStation.csv" 
	grep '^[^-;]*;[^-;]*;-;-;[^-;]*;-' "$1" > "tmp/filtreConso.csv" 
	;;
	hva) grep '^[^-;]*;[^-;]*;[^-;]*;-;-;-' "$1" > "tmp/filtreStation.csv" 
	grep '^[^-;]*;-;[^-;]*;-;[^-;]*;-' "$1" > "tmp/filtreConso.csv" 
	;;
	lv) grep '^[^-;]*;-;[^-;]*;[^-;]*;-;-' "$1" > "tmp/filtreStation.csv" 
	case $3 in
		all) grep '^[^-;]*;-;-;[^-;]*;' "$1" > "tmp/filtreConso.csv" 
		;;
		comp) grep '^[^-;]*;-;-;[^-;]*;[^-;]*;-' "$1" > "tmp/filtreConso.csv" 
		;;
		indiv) grep '^[^-;]*;-;-;[^-;]*;-;[^-;]*;' "$1" > "tmp/filtreConso.csv" 
		;;
	esac
	;;
esac

#if [ -x 'codeC/exec' ] ; then #verif executable C
#	./codeC/exec
#else
#	make -C codeC
#	./codeC/exec
#fi

