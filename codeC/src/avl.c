#include "../include/avl.h"
#include "../include/maths.h"

//Creation de l'arbre
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

// Double rotation de l'arbre (à gauche)
Arbre* doubleRotationGauche(Arbre* a){
	a->fd = rotationDroite(a->fd);
	return rotationGauche(a);
}

// Double rotation de l'arbre (à droite)
Arbre* doubleRotationDroite(Arbre* a){
	a->fg = rotationGauche(a->fg);   
	return rotationDroite(a);
}

//Equilibrage de l'arbre
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

//Insertion des données dans l'arbre
Arbre* insertionAVL(Arbre* a, Donnees d, int* h) {
    if (a == NULL) {
        *h = 1;
        return creerArbre(d);
    }

    /* (Pour les consommateurs) 
    Quand plusieurs consommateurs sont reliés à la même station (même id) on somme leur consommation*/
    if(d.id == a->donnees.id){ 
        a->donnees.conso += d.conso;
        *h = 0;
        return a;
    } 
    if (d.id < a->donnees.id) {
        a->fg = insertionAVL(a->fg, d, h);
        *h = -*h;
    } else if (d.id > a->donnees.id) {
        a->fd = insertionAVL(a->fd, d, h);
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

// liberer la memoire
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

// Afficher l'arbre
void afficherAVL(Arbre* a, FILE* fichier) {
    if (a == NULL) {
        return; // Aucun affichage pour un nœud vide
    }
    
    // Parcourir l'arbre en ordre croissant
    afficherAVL(a->fg, fichier); // Affiche le sous-arbre gauche
    
    // Affiche le nœud courant
    if (fichier == stdout) {
        // Affichage dans la console
        printf("%lu:%lu:%lu\n", a->donnees.id, a->donnees.produc, a->donnees.conso);
    } else {
        // Écriture dans un fichier
        fprintf(fichier, "%lu:%lu:%lu\n", a->donnees.id, a->donnees.produc, a->donnees.conso);
    }
    
    afficherAVL(a->fd, fichier); // Affiche le sous-arbre droit
}

// Fonction qui ajoute les valeurs de consommation de l'AVL des conso dans l'AVL des stations
void ajoutConso(Arbre* a, unsigned long id, unsigned long conso) {  
    if(id == a->donnees.id){ 
        a->donnees.conso += conso;
    } else if (id < a->donnees.id) {
        ajoutConso(a->fg, id,conso);
    } else if (id > a->donnees.id) {
        ajoutConso(a->fd, id,conso);
    } 
}
