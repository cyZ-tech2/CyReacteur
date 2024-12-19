#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour les données
typedef struct donnees {
    int id;
    unsigned long conso;
    unsigned long produc;
} Donnees;

// Structure pour l'arbre AVL
typedef struct arbre {
    Donnees donnees;
    struct arbre* fg;
    struct arbre* fd;
    int eq; // équilibre de l'arbre
} Arbre;

// Fonctions auxiliaires
int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

Arbre* creerArbre(Donnees d) {
    Arbre* nouv = malloc(sizeof(Arbre));
    if (nouv == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    nouv->donnees = d;
    nouv->fg = NULL;
    nouv->fd = NULL;
    nouv->eq = 0;
    return nouv;
}

Arbre* rotationGauche(Arbre* a) {
    Arbre* pivot = a->fd;  
    int eq_a, eq_p;
    a->fd = pivot->fg;     
    pivot->fg = a;        
    eq_a = a->eq;
    eq_p = pivot->eq;
    
    a->eq = eq_a - max(eq_p, 0) - 1;          
    pivot->eq = min(eq_a - 2, eq_a + eq_p - 2); 
    
    return pivot;
}

Arbre* rotationDroite(Arbre* a) {
    Arbre* pivot = a->fg;  
    int eq_a, eq_p;
    a->fg = pivot->fd;     
    pivot->fd = a;         
    eq_a = a->eq;
    eq_p = pivot->eq;
    
    a->eq = eq_a - min(eq_p, 0) + 1;          
    pivot->eq = max(eq_a + 2, eq_a + eq_p + 2); 
    
    return pivot; 
}

Arbre* doubleRotationGauche(Arbre* a){
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

Arbre* doubleRotationDroite(Arbre* a){
    a->fg = rotationGauche(a->fg);   
    return rotationDroite(a);
}

Arbre* insertionAVL(Arbre* a, Donnees d, int* h) {
    if (a == NULL) {
        *h = 1;
        return creerArbre(d);
    }

    if (d.id < a->donnees.id) {
        a->fg = insertionAVL(a->fg, d, h);
        *h = -*h;
    } else if (d.id > a->donnees.id) {
        a->fd = insertionAVL(a->fd, d, h);
    } else {
        *h = 0;
        return a;
    }

    if (*h != 0) {
        a->eq += *h;

        if (a->eq >= 2) {
            if (a->fd->eq >= 0) {
                return rotationGauche(a);
            } else {
                return doubleRotationGauche(a);
            }
        } else if (a->eq <= -2) {
            if (a->fg->eq <= 0) {
                return rotationDroite(a);
            } else {
                return doubleRotationDroite(a);
            }
        }

        *h = (a->eq == 0) ? 0 : 1;
    }

    return a;
}

void freeAVL(Arbre* a) {
    if (a == NULL) {
        return;
    }
    freeAVL(a->fg);
    freeAVL(a->fd);
    free(a);
}

void afficherAVL(Arbre* a, FILE* fichier) {
    if (a == NULL) {
        return; // Aucun affichage pour un nœud vide
    }
    
    // Parcourir l'arbre en ordre croissant
    afficherAVL(a->fg, fichier); // Affiche le sous-arbre gauche
    
    // Affiche le nœud courant
    if (fichier == stdout) {
        // Affichage dans la console
        printf("ID: %d, Conso: %lu, Produc: %lu\n", a->donnees.id, a->donnees.conso, a->donnees.produc);
    } else {
        // Écriture dans un fichier
        fprintf(fichier, "ID: %d, Conso: %lu, Produc: %lu\n", a->donnees.id, a->donnees.conso, a->donnees.produc);
    }
    
    afficherAVL(a->fd, fichier); // Affiche le sous-arbre droit
}


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

// Fonction principale
int main() {
    const char* fichierEntree = "C:\\Users\\bAdplayer\\Documents\\test\\output.txt";
    const char* fichierSortie = "C:\\Users\\bAdplayer\\Documents\\test\\output_avl.txt";

    // Lire le fichier et construire l'AVL
    Arbre* a = lireFichierEtConstruireAVL(fichierEntree);

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
