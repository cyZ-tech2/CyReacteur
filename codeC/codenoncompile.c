#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des types
typedef enum {
    hv_b,
    hv_a,
    lv,
    erreur = -1
} Type;

// Structure pour stocker les données
typedef struct donnees {
    int id;
    unsigned long centrale;
    unsigned long hv_b;
    unsigned long hv_a;
    unsigned long lv;
    unsigned long entrp;
    unsigned long partc;
    unsigned long conso;
    unsigned long produc;
} Donnees;

// Structure pour l'arbre AVL
typedef struct arbre {
    Donnees d;
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

// Fonction pour créer un nouvel arbre avec une donnée
Arbre* creerArbre(Donnees e) {
    Arbre* nouv = malloc(sizeof(Arbre));
    nouv->d = e;
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


// Fonction pour vérifier le type de station
Type verifStation(Donnees d) {
    if (d.lv > 0) {
        return lv;  // Poste basse tension (LV)
    } else if (d.hv_a > 0 && d.lv == 0) {
        return hv_a;  // Poste haute tension de type A (HV_A)
    } else if (d.hv_b > 0 && d.lv == 0 && d.hv_a == 0) {
        return hv_b;  // Poste haute tension de type B (HV_B)
    } else {
        return erreur;  // Type inconnu ou données invalides
    }
}


// Fonction d'insertion dans l'arbre AVL avec message de débogage
Arbre* insertionAVL(Arbre* a, Donnees d, int* h) {
    if (a == NULL) {
        *h = 1;  
        return creerArbre(d);  
    }

    // Utiliser l'ID de la donnée pour comparer
    if (d.id < a->d.id) { 
        a->fg = insertionAVL(a->fg, d, h);
        *h = -*h;  
    } else if (d.id > a->d.id) { 
        a->fd = insertionAVL(a->fd, d, h);
    } else {
        *h = 0;  
        return a;
    }

    
    if (*h != 0) {
        a->eq = a->eq + *h;

       
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


// Fonction pour afficher l'arbre (in-order)
void afficherArbre(Arbre* a) {
    if (a != NULL) {
        afficherArbre(a->fg); 
        printf("Nœud : ID=%d, conso=%lu\n", a->d.id, a->d.conso);
        afficherArbre(a->fd); 
        printf("Aucun nœud à cet emplacement (NULL).\n");
    }
}

// Fonction pour afficher toutes les valeurs du fichier
void afficherValeursFichier(FILE* fichier) {
    if (fichier == NULL) {
        perror("Erreur: fichier non ouvert pour affichage");
        exit(EXIT_FAILURE);
    }

    rewind(fichier);  

    char ligne[200];
    printf("Contenu du fichier :\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        unsigned long centrale, hv_b, hv_a, lv, entrp, partc, conso, produc;
        if (sscanf(ligne, "%lu;%lu;%lu;%lu;%lu;%lu;%lu;%lu", 
                   &centrale, &hv_b, &hv_a, &lv, &entrp, &partc, &conso, &produc) == 8) {
            printf("centrale: %lu, hv_b: %lu, hv_a: %lu, lv: %lu, entrp: %lu, partc: %lu, conso: %lu, produc: %lu\n",
                   centrale, hv_b, hv_a, lv, entrp, partc, conso, produc);
        }
    }
}

// Fonction pour modifier les données du fichier (remplacer les `-` par `0`)
FILE* modifFichier(FILE* fichier) {
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
            if (ligne[i] == '-' && strchr(";\n\0", ligne[i + 1]) && (i == 0 || ligne[i - 1] == ';')) {
                ligne[i] = '0';  // Remplacer le `-` par `0`
            }
        }

        // Écrire la ligne modifiée dans le fichier temporaire
        fputs(ligne, fichier_temp);
    }

    // Fermer les fichiers
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

// Fonction principale pour ajouter des valeurs dans l'arbre AVL
void ajouterValeur(FILE* fichier, Arbre** racine, int* h) {
    if (fichier == NULL || racine == NULL) {
        exit(5);
    }

    FILE* fichier_v2 = modifFichier(fichier);  // Modifier le fichier et obtenir le pointeur
    if (fichier_v2 == NULL) {
        perror("Erreur d'ouverture du fichier modifié");
        exit(6);
    }

    Donnees tmp;  // Stocker temporairement les données
    char ligne_v2[200];

    while (fgets(ligne_v2, sizeof(ligne_v2), fichier_v2)) {
        // Lire les données depuis le fichier
        if (sscanf(ligne_v2, "%lu;%lu;%lu;%lu;%lu;%lu;%lu;%lu", 
                   &tmp.centrale, &tmp.hv_b, &tmp.hv_a, &tmp.lv, 
                   &tmp.entrp, &tmp.partc, &tmp.conso, &tmp.produc) == 8) {
            
            // Vérifier le type de station
            Type type = verifStation(tmp);
            switch (type) {
                case lv:
                    tmp.id = tmp.lv;  
                    *racine = insertionAVL(*racine, tmp, h);
                    break;

                case hv_a:
                    tmp.id = tmp.hv_a;  
                    *racine = insertionAVL(*racine, tmp, h);
                    break;

                case hv_b:
                    tmp.id = tmp.hv_b; 
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


int main() {
    FILE* fichier = fopen("C:\\Users\\bAdplayer\\Documents\\test\\c-wire_v00.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier source");
        return EXIT_FAILURE;
    }

    // Modifier le fichier et obtenir un pointeur vers le fichier modifié
    FILE* fichier_modifie = modifFichier(fichier);
    if (fichier_modifie == NULL) {
        perror("Erreur lors de la modification du fichier");
        return EXIT_FAILURE;
    }

    // Afficher les valeurs du fichier modifié
    afficherValeursFichier(fichier_modifie);

    // Construire l'arbre AVL avec les données du fichier
    Arbre* racine = NULL;
    int h = 0;
    ajouterValeur(fichier_modifie, &racine, &h);

    // Vérifier si l'arbre est vide avant de l'afficher
    if (racine == NULL) {
        printf("L'arbre est vide.\n");
    } else {
        // Afficher l'arbre AVL
        printf("\nArbre après insertion des valeurs :\n");
        afficherArbre(racine);
    }

    // Fermer le fichier
    fclose(fichier_modifie);
    return EXIT_SUCCESS;
}
