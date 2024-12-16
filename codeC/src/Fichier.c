#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* modifFichier(FILE* fichier){
    if(fichier == NULL){
        exit(1);
    }
    FILE* fichier_v2 = fopen("c-wire_v00.dat", "w");
    if(fichier_v2 == NULL){
        fclose(fichier);
        exit(2);
    }
    char longueur[100];

    while(fgets(longueur, sizeof(longueur), fichier) != NULL){
    for (int i = 0; longueur[i] != '\0'; i++) {
            if (longueur[i] == '-' && strchr(";\n\0", longueur[i + 1]) && (i == 0 || longueur[i - 1] == ';')) {
                // Si '-' est isolé, remplacer par "-1"
                fputc('-', fichier_v2);
                fputc('1', fichier_v2);
            }else {
                fputc(longueur[i], fichier_v2);
            }
        }   
    }
    fclose(fichier);
    fclose(fichier_v2);

    
    fichier_v2 = fopen("c-wire_v00.dat", "r");
    if (fichier_v2 == NULL) {
        exit(3);
    }

    return fichier_v2;
}


int main(){
FILE* fichier = NULL;
FILE* fichier_v2 = NULL;
}

Donnees* creationTMP(){
    Donnees* tmp = malloc(sizeof(Donnees));
        if(tmp == NULL){
        exit(4);
    }
    
	tmp->centrale = 0;
    tmp->hvb = 0;
    tmp->hvb = 0;
    tmp->lv = 0;
    tmp->entrp = 0;
    tmp->partc = 0;
    tmp->conso = 0;
    tmp->produc = 0;
    return tmp;
}


void ajouterValeur(FILE* fichier, Arbre* racine, char* nom_station){
    if(fichier == NULL || racine == NULL || nom_station == NULL ){
        exit(5);
    }
    FILE* fichier_v2 = modifFichier(fichier);
    char longueur_v2[100];
    Donnees* tmp = creationTMP();
}
 while (fgets(longueur_v2, sizeof(longueur_v2), fichier_v2)) {	

  if(sscanf(longueur, "%lu;%lu;%lu;%lu;%lu;%lu;%lu;%lu", &tmp->centrale, &tmp->hvb, &tmp->hvb, &tmp->lv, &tmp->entrp, &tmp->partc, &tmp->conso, &tmp->produc) == 8){
        insertAVL(racine, nom_station);
        }else {
            printf("Erreur de traitement");
        }
    }
    fclose(fichier);
}


