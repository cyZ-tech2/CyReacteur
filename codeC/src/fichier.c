#include "../include/fichier.h"

// Fonction pour lire le fichier et construire l'AVL
Arbre* lireFichierEtConstruireAVL(const char* cheminFichier) {
    FILE* fichier = fopen(cheminFichier, "r");
    if (fichier == NULL) {
        perror("Erreur: fichier source non ouvert");
        exit(EXIT_FAILURE);
    }

    Arbre* a = NULL;
    char ligne[256];
    int h = 0;

    // Lire et ignorer la première ligne (en-tête)
    if (fgets(ligne, sizeof(ligne), fichier) == NULL) {
        perror("Erreur: fichier vide");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier)) {
        Donnees d;
        if (sscanf(ligne, "%d:%lu:%lu", &d.id, &d.conso, &d.produc) == 3) {
            printf("Insertion réussie pour ID: %d, Conso: %lu, Produc: %lu\n", d.id, d.conso, d.produc);
            a = insertionAVL(a, d, &h);
        } else {
            fprintf(stderr, "Erreur de format : %s\n", ligne);
        }
    }
    fclose(fichier);

    return a;
}

// Fonction pour afficher l'AVL dans un fichier
void ecrireAVLDansFichier(Arbre* a, const char* cheminFichier) {
    FILE* fichierSortie = fopen(cheminFichier, "w");
    if (fichierSortie == NULL) {
        perror("Erreur: impossible d'ouvrir le fichier de sortie");
        exit(EXIT_FAILURE);
    }

    afficherAVL(a, fichierSortie);
    fclose(fichierSortie);
}