#include "../include/fichier.h"
#include "../include/maths.h"

int main() {
    const char* fichierStations = "tmp/filtreStation.csv";
    const char* fichierSortie = "tmp/tests/*.csv";

    // Lire le fichier et construire l'AVL
    Arbre* a = construireAVL(fichierStations);

    // Afficher l'AVL dans la console
    printf("Affichage de l'AVL dans la console :\n");
    afficherAVL(a, stdout);

    // Écrire l'AVL dans un fichier de sortie
    printf("Écriture de l'AVL dans %s...\n", fichierSortie);
    AVLDansFichier(a, fichierSortie);

    // Libérer l'arbre AVL
    freeAVL(a);
    printf("Programme terminé avec succès.\n");

    return EXIT_SUCCESS;
}