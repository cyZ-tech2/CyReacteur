#include "../include/avl.h"
#include "../include/fichier.h"

// Fonction pour transformer un fichier CSV en remplaçant les '-' par '0' (fonctionne)
FILE* transformerFichierCSV(const char* chemin_fichier) {
    FILE* fichier = fopen(chemin_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur: fichier source non ouvert");
        exit(EXIT_FAILURE);
    }

    // Créer un fichier temporaire pour les modifications
    FILE* fichier_temp = fopen("C:\\Users\\bAdplayer\\Documents\\test\\c-wire_v00_temp.txt", "w");
    if (fichier_temp == NULL) {
        perror("Erreur lors de la création du fichier temporaire");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        for (int i = 0; ligne[i] != '\0'; i++) {
            if (ligne[i] == '-') {
                ligne[i] = '0';  // Remplacer '-' par '0'
            }
        }
        fputs(ligne, fichier_temp);  // Écrire la ligne modifiée
    }

    fclose(fichier);
    fclose(fichier_temp);

    // Réouvrir le fichier temporaire en mode lecture
    fichier_temp = fopen("C:\\Users\\bAdplayer\\Documents\\test\\c-wire_v00_temp.txt", "r");
    if (fichier_temp == NULL) {
        perror("Erreur lors de la réouverture du fichier temporaire");
        exit(EXIT_FAILURE);
    }

    return fichier_temp;
}

