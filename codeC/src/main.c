#include "../include/fichier.h"
#include "../include/maths.h"

int main() {
    const char* fichierEntree = "C:\\Users\\bAdplayer\\Documents\\test\\output.txt";
    const char* fichierSortie = "C:\\Users\\bAdplayer\\Documents\\test\\output_avl.txt";

    // Lire le fichier et construire l'AVL
    Arbre* a = construireAVL(fichierEntree);

    // Afficher l'AVL dans la console
    printf("Affichage de l'AVL dans la console :\n");
    afficherAVL(a, stdout);

    // Écrire l'AVL dans un fichier de sortie
    printf("Écriture de l'AVL dans %s...\n", fichierSortie);
    ecrireAVLDansFichier(a, fichierSortie);

    // Libérer l'arbre AVL
    freeAVL(a);
    printf("Programme terminé avec succès.\n");

    return EXIT_SUCCESS;
}