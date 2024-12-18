#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
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

// Fonction utilitaire pour obtenir le maximum entre deux entiers
int max(int a, int b) {
    return a > b ? a : b;
}

// Fonction utilitaire pour obtenir le minimum entre deux entiers
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

// Rotation gauche de l'arbre (à gauche)
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

// Rotation droite de l'arbre (à droite)
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

Arbre* equilibrerAVL(Arbre* a){
	if(a->eq >= 2){
		if(a->fd->eq >= 0){
			return rotationGauche(a);
		}
		else{
			return doubleRotationGauche(a);
		}
	}
	else if(a->eq <= -2){
		if(a->fg->eq <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);	
		} 
	}
	return a;
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

    // Libérer les sous-arbres gauche et droit
    freeAVL(a->fg);
    freeAVL(a->fd);

    // Libérer le nœud courant
    free(a);
}



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

void afficherAVL(Arbre* a, FILE* fichier) {
    if (a == NULL) {
        return;
    }
    afficherAVL(a->fg, fichier);
    fprintf(fichier, "ID: %d, Conso: %lu, Produc: %lu\n", a->donnees.id, a->donnees.conso, a->donnees.produc);
    afficherAVL(a->fd, fichier);
}

int main() {
    // Transformer le fichier CSV
    FILE* fichier = transformerFichierCSV("C:\\Users\\bAdplayer\\Documents\\test\\c-wire_v00.txt");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier transformé.\n");
        return EXIT_FAILURE;
    }

    // Initialiser un arbre vide
    Arbre* arbre = NULL;


    // Fermer le fichier
    fclose(fichier);

    // Libérer l'arbre après utilisation
    freeAVL(arbre);

    return EXIT_SUCCESS;
}
