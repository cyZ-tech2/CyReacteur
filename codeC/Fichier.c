FILE* fichier = NULL;
int caractereActuel = EOF+1;
fichier = fopen("test.txt", "r");
if (fichier != NULL)
{
while (caractereActuel != EOF)
{
caractereActuel = fgetc(fichier); // On lit le caractère
printf("%c", caractereActuel); // On l'affiche
} ;

fclose(fichier);
}
