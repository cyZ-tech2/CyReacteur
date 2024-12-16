#include <avl.h>

Arbre* creerArbre(Donnees e){
	Arbre* nouv = malloc(sizeof(Arbre));
	nouv->donnees = e;
	nouv->fg = NULL;
	nouv->fd = NULL;
	nouv->eq = 0;
	return nouv;	
}

Arbre* rotationGauche(Arbre* a){
	Arbre* pivot = a->fd;
	int eq_a, eq_p;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->eq;
	eq_p = pivot->eq;
	a->eq = eq_a - max(eq_p,0) - 1;
	pivot->eq = min(eq_a-2, eq_a + eq_p-2, eq_p-1);
	a = pivot;
	return a;
}

Arbre* rotationDroite(Arbre* a){
	Arbre* pivot = a->fg;
	int eq_a, eq_p;
	a->fg = pivot->fd;
	pivot->fd = a;
	eq_a = a->eq;
	eq_p = pivot->eq;
	a->eq = eq_a - min(eq_p,0) + 1;
	pivot->eq = max(eq_a+2, eq_a + eq_p+2, eq_p+1);
	a = pivot;
	return a;
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

Arbre* insertionAVL(Arbre* a, Donnees e, int* h){
	if(a==NULL){
		*h=1;
		return creerArbre(e);
	}
	else if(e.id < a->e.id){
		a->fg = insertionAVL(a->fg, e, h);
		*h=-*h;
	}
	else if(e.id > a->e.id){
		a->fd = insertionAVL(a->fd, e, h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h != 0){
		a->eq = a->eq + *h;
		a = equilibrerAVL(a);
		if(a->eq == 0){
			*h=0
		}
		else{
			*h=1;
		}
	}
	return a;
}

Type verifStation(Donnees d) {
    // Vérifier les conditions basées sur les champs des données
    if (d.lv > 0 && d.hv_a == -1 && d.hv_b == -1) {
        return lv;
    } else if (d.hv_a > 0 && d.lv == -1 && d.hv_b != -1) {
        return hv_a;
    } else if (d.hv_b > 0 && d.hv_a == -1 && d.lv == -1) {
        return hv_b; 
    }
    return -1; 
}


// Fonction (somme tous les fils)

int sommeConso(Node* racine) {
    if (racine == NULL){
        return 0; 
    }
    return sommeConso(racine->fg) + sommeConso(racine->fd) + racine->id;
}
