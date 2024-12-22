#include "../include/fichier.h"
#include "../include/maths.h"
#include <string.h>

int main(int argc, char * argv[]) {
    // On déclare les variables nécessaires
    const char* fichierStations = "tmp/filtreStation.csv";
    const char* fichierSortie = argv[1];
    const char* typeStation = argv[2];
    const char* typeConso = argv[3];

    // On lit les fichiers temporaires et on construits les AVL
    Arbre* Stations = construireAVLStation(fichierStations);
    Arbre* Conso = construireAVLConso("tmp/filtreConso.csv");

    // On fait la somme des consommations de chaque consommateur
    sommeConso(Stations,Conso);

    // Écrire l'AVL dans un fichier de sortie
    printf("Écriture de l'AVL dans %s...\n", fichierSortie);
    AVLDansFichier(Stations, fichierSortie, typeStation, typeConso);

    if(strcmp(typeStation,"lv")==0 && strcmp(typeConso,"all")==0 && argc == 4){
        diffCapConso(fichierSortie);
    }

    // Libérer les AVL
    freeAVL(Stations);
    freeAVL(Conso);

    return 0;
}
