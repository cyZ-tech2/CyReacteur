#!/bin/bash

aide(){
	#message d'aide
	return 0
}

if [[ "$*" = *-h* ]] ; then # aide
	aide
	exit 0

elif [[ "$1" != *.csv ]] ; then # verif fichier de donnees
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

if [ ! -x 'codeC/exec' ] ; then #verif executable C
	codeC/make
fi

