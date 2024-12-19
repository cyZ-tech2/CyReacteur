#include "../include/fichier.h"

// Fonction pour lire le fichier et construire l'AVL
Arbre* construireAVL(const char* cheminFichier) {
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
        if (sscanf(ligne, "%d;%lu", &d.id, &d.produc) == 2) {
            a = insertionAVL(a, d, &h);
        } else {
            fprintf(stderr, "Erreur de format : %s\n", ligne);
        }
    }
    fclose(fichier);

    return a;
}

// Fonction pour afficher l'AVL dans un fichier
void AVLDansFichier(Arbre* a, const char* cheminFichier) {
    FILE* fichierSortie = fopen(cheminFichier, "w");
    if (fichierSortie == NULL) {
        perror("Erreur: impossible d'ouvrir le fichier de sortie");
        exit(EXIT_FAILURE);
    }

    afficherAVL(a, fichierSortie);
    fclose(fichierSortie);
}