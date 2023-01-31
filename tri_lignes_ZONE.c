#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


void fabrication(char *ligne, float b[],int nbligne,int nbcolonne,FILE * fp,FILE * propre,int X_max,int X_min,int Y_max,int Y_min)
  { 
    int l =1;  
    fgets(ligne, 1024, fp);
    char *val = strtok(ligne, ";");
    int c = 0;                                  //variable pour compter le nombre de colonnes
    while (val != NULL)                         //pour initialiser l'arbre
    {         
        b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
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
            b[c]= strtof(val,NULL);                 //stockez la dans un tableau en transformant la valeur en float
            val = strtok(NULL, ";");                //Passez à la prochaine valeur
            c++;
        }
        l++;
        if (b[nbcolonne-1] < X_max && b[nbcolonne-1] > X_min )                  //test la les coordonnees en X
        {   if (b[nbcolonne-2] < Y_max && b[nbcolonne-2] > Y_min )          //test la les coordonnees en Y
            {
                fprintf(propre,"%.0f;",b[0]);  
                for (int i = 1; i < nbcolonne-1; i++) fprintf(propre,"%f;",b[i]);
                fprintf(propre,"%f\n", b[nbcolonne]);
            }
        }
    }
}

int main(int argc,char* argv[])
{
    //test des arguments
    int j = 0;   // compteur pour le getopt  
    char* entree;
    char* sortie;
    char* zone;
    int nbligne = 0;
    int nbcolonne = 0;
    int nbarg = 0;
    while ((j = getopt (argc, argv, "f:o:c:l:z:")) != -1) {
        switch (j) {
            case 'f':
                entree = optarg;
                nbarg += 1;
                break;
            case 'o':
                sortie = optarg;
                nbarg += 1;
                break;
            case 'c':
                nbcolonne = atoi(optarg);
                if (nbcolonne <= 0)
                {
                    puts("nombre de colonne invalide");
                    exit(1);
                }
                nbarg += 1;
                break;
            case 'l':
                nbligne = atoi(optarg);
                if (nbligne <= 0)
                {
                    puts("nombre de ligne invalide");
                    exit(1);
                }
                nbarg += 1;
                break;
            case 'z': 
                zone = optarg;
                nbarg += 1;
                break;
            default:
                puts("mauvaise option");
                exit(1);
        }
    }
    if (nbarg != 5)
    {
        puts("nombre d'option invalide");
        exit(1);
    }
    int X_max;
    int X_min;
    int Y_max;
    int Y_min;
    FILE *fp = fopen( entree, "rt");                            // Ouvre le fichier CSV en lecture
    FILE * propre = fopen( sortie , "w+");                     // Ouvre le fichier CSV en ecriture
    // Vérifiez que le fichier a été ouvert avec succès 
    if (fp == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier d'entrée\n");
        return 1;
    }
    if (propre == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de sortie\n");
        return 1;
    }
    printf("%s",zone);
    char ligne[1024];   
    int l =1;                             // variable pour compter le nombre de lignes
    float b[nbcolonne];
    if ( strcmp("F",zone) == 0 )               // on entre chaque valeur de zone 
    {
        X_max = 10;
        X_min = -6;
        Y_max = 40;
        Y_min = 50;
    }
    else if ( strcmp("A",zone) == 0 )
    {
        X_max = -55;
        X_min = -78;
        Y_max = 20;
        Y_min = 8;
    }
    else if ( strcmp("G",zone) == 0 )
    {
        X_max = -50;
        X_min = -60;
        Y_max = 8;
        Y_min = 0;
    }
    else if ( strcmp("O",zone) == 0 )
    {
        X_max = 115;
        X_min = 15;
        Y_max = 10;
        Y_min = -54;
    }
    fabrication(ligne,b,nbligne,nbcolonne,fp,propre,X_max,X_min,Y_max,Y_min);
    fclose(fp);
    fclose(propre);
    return 0;
}