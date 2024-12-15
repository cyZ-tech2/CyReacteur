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

