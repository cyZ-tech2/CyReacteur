#include <CyReacteur.h>

Arbre* creerArbre(int e, int a, b){
	Arbre* nouv = malloc(sizeof(Arbre));
	nouv->id = e;
	nouv->fg = NULL;
	nouv->fd = NULL;
	nouv->eq = 0;
	nouv->capacite = a;
	nouv->conso = b;
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
	a->fg = rotationDroite(a->fg);
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

Arbre* insertionAVL(Arbre* a, int e, int* h){
	if(a==NULL){
		*h=1;
		return creerArbre(e);
	}
	else if(e < a->el){
		a->fg = insertionAVL(a->fg, e,h);
		*h=-*h;
	}
	else if(e > a->el){
		a->fd = insertionAVL(a->fd, e,h);
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


