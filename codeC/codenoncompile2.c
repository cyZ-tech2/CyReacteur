#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure de données pour l'arbre AVL
typedef struct Donnees {
    unsigned long centrale;
    unsigned long hv_b;
    unsigned long hv_a;
    unsigned long lv;
    unsigned long entrp;
    unsigned long partc;
    unsigned long conso;
    unsigned long produc;
    int id; // Utilisé comme clé pour AVL
} Donnees;

typedef struct Arbre {
    Donnees d;
    struct Arbre* fg;
    struct Arbre* fd;
    int eq; // Facteur d'équilibre
} Arbre;

// Enums pour les types de stations
typedef enum {
    lv, hv_a, hv_b, erreur
} Type;

// Prototypes des fonctions AVL
Arbre* insertionAVL(Arbre* a, Donnees d, int* h);
Type verifStation(Donnees d);

// Fonction pour transformer un fichier (remplacer '-' par '0')
FILE* transformerFichier(FILE* fichier) {
    if (fichier == NULL) {
        perror("Erreur: fichier source non ouvert");
        exit(EXIT_FAILURE);
    }

    // Ouvrir un fichier temporaire pour écrire les modifications
    FILE* fichier_temp = fopen("C:\\Users\\bAdplayer\\Documents\\test\\c-wire_v00_temp.txt", "w");
    if (fichier_temp == NULL) {
        perror("Erreur lors de la création du fichier temporaire");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        for (int i = 0; ligne[i] != '\0'; i++) {
            // Remplacer '-' par '0' si nécessaire
            if (ligne[i] == '-') {
                ligne[i] = '0';
            }
        }

        // Écrire la ligne modifiée dans le fichier temporaire
        fputs(ligne, fichier_temp);
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

// Fonction pour lire les données du fichier et insérer dans l'AVL
void ajouterValeur(FILE* fichier, Arbre** racine, int* h) {
    if (fichier == NULL || racine == NULL) {
        perror("Erreur: paramètres invalides");
        exit(EXIT_FAILURE);
    }

    // Transformer le fichier pour remplacer '-' par '0'
    FILE* fichier_v2 = transformerFichier(fichier);
    if (fichier_v2 == NULL) {
        perror("Erreur lors de la transformation du fichier");
        exit(EXIT_FAILURE);
    }

    Donnees tmp;  // Stocker temporairement les données
    char ligne_v2[200];

    // Lire le fichier ligne par ligne
    while (fgets(ligne_v2, sizeof(ligne_v2), fichier_v2)) {
        // Parse les données à l'aide de sscanf
        if (sscanf(ligne_v2, "%lu;%lu;%lu;%lu;%lu;%lu;%lu;%lu", 
                   &tmp.centrale, &tmp.hv_b, &tmp.hv_a, &tmp.lv, 
                   &tmp.entrp, &tmp.partc, &tmp.conso, &tmp.produc) == 8) {

            // Identifier le type de station
            Type type = verifStation(tmp);

            switch (type) {
                case lv:
                    tmp.id = tmp.lv;  // Utiliser lv comme clé
                    *racine = insertionAVL(*racine, tmp, h);
                    break;

                case hv_a:
                    tmp.id = tmp.hv_a;  // Utiliser hv_a comme clé
                    *racine = insertionAVL(*racine, tmp, h);
                    break;

                case hv_b:
                    tmp.id = tmp.hv_b;  // Utiliser hv_b comme clé
                    *racine = insertionAVL(*racine, tmp, h);
                    break;

                default:
                    printf("Station inconnue ou données invalides : %s\n", ligne_v2);
                    break;
            }
        } else {
            printf("Erreur lors de la lecture de la ligne : %s\n", ligne_v2);
        }
    }

    fclose(fichier_v2);
}

// Fonction pour vérifier le type de station
Type verifStation(Donnees d) {
    if (d.lv > 0) {
        return lv;
    } else if (d.hv_a > 0) {
        return hv_a;
    } else if (d.hv_b > 0) {
        return hv_b;
    }
    return erreur;
}


// Fonction d'insertion dans un AVL (simplifiée)
Arbre* insertionAVL(Arbre* a, Donnees d, int* h) {
    if (a == NULL) {
        Arbre* nouv = malloc(sizeof(Arbre));
        nouv->d = d;
        nouv->fg = NULL;
        nouv->fd = NULL;
        nouv->eq = 0;
        *h = 1;
        return nouv;
    }

    if (d.id < a->d.id) {
        a->fg = insertionAVL(a->fg, d, h);
        *h = -(*h);
    } else if (d.id > a->d.id) {
        a->fd = insertionAVL(a->fd, d, h);
    } else {
        *h = 0;  // Clé déjà existante
        return a;
    }

    if (*h != 0) {
        a->eq += *h;
        // Rééquilibrage AVL
        if (a->eq >= 2 || a->eq <= -2) {
            // Logique de rotation à ajouter ici
        }
        *h = (a->eq == 0) ? 0 : 1;
    }

    return a;
}

// Fonction pour afficher un arbre (in-order traversal)
void afficherArbre(Arbre* a) {
    if (a != NULL) {
        afficherArbre(a->fg);
        printf("ID: %d, Conso: %lu, Produc: %lu\n",
               a->d.id, a->d.conso, a->d.produc);
        afficherArbre(a->fd);
    }
}

// Main pour tester
int main() {
    FILE* fichier = fopen("C:\\Users\\bAdplayer\\Documents\\test\\c-wire_v00.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier source");
        return EXIT_FAILURE;
    }

    Arbre* racine = NULL;
    int h = 0;

    // Ajouter des valeurs dans l'arbre AVL
    ajouterValeur(fichier, &racine, &h);

    // Afficher l'arbre
    if (racine != NULL) {
        printf("Arbre AVL après insertion :\n");
        afficherArbre(racine);
    } else {
        printf("L'arbre est vide.\n");
    }

    fclose(fichier);
    return EXIT_SUCCESS;
}
