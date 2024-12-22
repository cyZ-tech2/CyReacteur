#include "../include/fichier.h"
#include "../include/maths.h"

// Fonction pour lire le fichier et construire l'AVL
Arbre* construireAVLStation(const char* cheminFichier) {
    FILE* fichier = fopen(cheminFichier, "r");
    if (fichier == NULL) {
        perror("Erreur: fichier source non ouvert");
        exit(EXIT_FAILURE);
    }

    Arbre* a = NULL;
    char ligne[256];
    int h = 0;
    Donnees d;
    d.conso = 0;

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier)!=NULL) {
        if (sscanf(ligne, "%lu;%lu", &d.id, &d.produc) == 2) {
            a = insertionAVL(a, d, &h);
        } else {
            fprintf(stderr, "Erreur de format : %s\n", ligne);
        }
    }
    fclose(fichier);

    return a;
}

// Fonction pour construire l'arbre
Arbre* construireAVLConso(const char* cheminFichier) {
    FILE* fichier = fopen(cheminFichier, "r");
    if (fichier == NULL) {
        perror("Erreur: fichier source non ouvert");
        exit(EXIT_FAILURE);
    }

    Arbre* a = NULL;
    char ligne[256];
    int h = 0;
    Donnees d;
    d.produc = 0;

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier)!=NULL) {
        if (sscanf(ligne, "%lu;%lu", &d.id, &d.conso) == 2) {
            a = insertionAVL(a, d, &h);
        } else {
            fprintf(stderr, "Erreur de format : %s\n", ligne);
        }
    }
    fclose(fichier);

    return a;
}

// Fonction pour afficher l'AVL dans un fichier
void AVLDansFichier(Arbre* a, const char* cheminFichier, const char* typeStation, const char* typeConso) {
    FILE* fichierSortie = fopen(cheminFichier, "w");
    if (fichierSortie == NULL) {
        perror("Erreur: impossible d'ouvrir le fichier de sortie");
        exit(EXIT_FAILURE);
    }
    fprintf(fichierSortie, "Station %s:Capacité:Consommation (%s)\n",typeStation,typeConso);
    afficherAVL(a, fichierSortie);
    fclose(fichierSortie);
}

// Fonction qui calcule la différence (production/conso)
void diffCapConso(const char* cheminFichier){
    FILE* fichier = fopen(cheminFichier, "r");
    if (fichier == NULL) {
        perror("Erreur: impossible d'ouvrir le fichier de sortie");
        exit(EXIT_FAILURE);
    }
    char ligne[256];
    FILE* fichierMinMax = fopen("tmp/minmaxTmp.csv","w");
    if (fichierMinMax == NULL) {
        perror("Erreur: le fichier minmaxTmp.csv n'a pas pu être créé");
        exit(EXIT_FAILURE);
    }
    Donnees d;
    
    fgets(ligne, sizeof(ligne), fichier);

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "%lu:%lu:%lu", &d.id, &d.produc, &d.conso) == 3) {
            fprintf(fichierMinMax, "%lu:%lu:%lu:%li\n",d.id, d.produc, d.conso, d.produc-d.conso);
        } else {
            fprintf(stderr, "Erreur de format : %s\n", ligne);
        }
    }
    fclose(fichier);
    fclose(fichierMinMax);
}
