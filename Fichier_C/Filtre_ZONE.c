#include "Filtre_ZONE.h"

void fabrication(char *ligne, double b[],int nbligne,int nbcolonne,FILE * fp,FILE * propre,int X_max,int X_min,int Y_max,int Y_min)
  { 
    int l =1;  
    fgets(ligne, 1024, fp);
    char *val = strtok(ligne, ";");
    int c = 0;                                  //variable pour compter le nombre de colonnes
    while (val != NULL)                         //pour initialiser l'arbre
    {         
        b[c]= strtod(val,NULL);                 //stockez la dans la matrice en transformant la valeur en double
        val = strtok(NULL, ";");                //Passez à la prochaine valeur
        c++;
    }
    l++;
    while (fgets(ligne, 1024, fp) != NULL)
    {
        int pourcent = (l*100.0)/nbligne;
        printf("avancement : %d  %%\r", pourcent);                //permet dafficher les lignes pour voir lavancement du traitement
        char *val = strtok(ligne, ";");             //permet de stocker ce qui il y a entre les points virgule dans un char
        int c = 0;                                  //variable pour compter le nombre de colonnes
        while (val != NULL)                         //quand il arrive en fin de ligne
        {         
            b[c]= strtod(val,NULL);                 //stockez la dans un tableau en transformant la valeur en double
            val = strtok(NULL, ";");                //Passez à la prochaine valeur
            c++;
        }
        l++;
        if (b[nbcolonne-1] < X_max && b[nbcolonne-1] > X_min )                  //test la les coordonnees en X
        {   if (b[nbcolonne-2] < Y_max && b[nbcolonne-2] > Y_min )          //test la les coordonnees en Y
            {
                fprintf(propre,"%.0f;",b[0]);  
                for (int i = 1; i < nbcolonne-1; i++) fprintf(propre,"%f;",b[i]);
                fprintf(propre,"%f\n", b[nbcolonne-1]);
            }
        }
    }
}
