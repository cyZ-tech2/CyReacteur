#include "../include/avl.h"
#include "../include/maths.h"

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

Arbre* rechercheStation(Arbre* a, int id){
    if(a->donnees.id == id){
        return a;
    }
    else if (a->donnees.id > id){
        return rechercheStation(a->fg,id);
    }
    else if (a->donnees.id < id){
        return rechercheStation(a->fd,id);
    }
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

void afficherAVL(Arbre* a, FILE* fichier) {
    if (a == NULL) {
        return; // Aucun affichage pour un nœud vide
    }
    
    // Parcourir l'arbre en ordre croissant
    afficherAVL(a->fg, fichier); // Affiche le sous-arbre gauche
    
    // Affiche le nœud courant
    if (fichier == stdout) {
        // Affichage dans la console
        printf("%d:%lu:%lu\n", a->donnees.id, a->donnees.produc, a->donnees.conso);
    } else {
        // Écriture dans un fichier
        fprintf(fichier, "%d:%lu:%lu\n", a->donnees.id, a->donnees.produc, a->donnees.conso);
    }
    
    afficherAVL(a->fd, fichier); // Affiche le sous-arbre droit
}

// Fonction qui parcourt le fichier filtreConso et fait la somme des consommateurs pour chaque station
/*void sommeConso(Arbre* AVLstation) {
    FILE* fichier = fopen("tmp/filtreConso.csv", "r");
    if (fichier == NULL) {
        perror("Erreur: fichier filtreConso non ouvert");
        exit(EXIT_FAILURE);
    }

    char ligne[256];
    Arbre* tmpAVL = AVLstation;
    unsigned long tmpId, tmpConso;
    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "%lu;%lu", &tmpId, &tmpConso) == 2) {
            tmpAVL = rechercheStation(AVLstation,tmpId);
            tmpAVL->donnees.conso += tmpConso;
        } else {
            fprintf(stderr, "Erreur de format : %s\n", ligne);
        }
    }
    fclose(fichier);
}*/

void sommeConso(Arbre* AVLstation, Arbre* AVLconso) {
    if(AVLconso != NULL){
        Arbre* tmpAVL = AVLstation;
        tmpAVL = rechercheStation(AVLstation,AVLconso->donnees.id);
        tmpAVL->donnees.conso += AVLconso->donnees.conso;
        sommeConso(AVLstation,AVLconso->fg);
        sommeConso(AVLstation,AVLconso->fd);
    }
}