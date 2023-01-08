#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#define MALLOC(x) ((x*)) malloc(sizeof(x))

typedef struct temps
{
    int année;
    int mois;
    int jour;
    int heure;
}TEMPS;

typedef struct arbre{
    float col1;
    float col2;
    float col3;
    float col4;
    float col5;
    float col6;
    int hauteur;
    struct arbre* doublon;
    struct arbre* fd;
    struct arbre* fg;
}Arbre;



typedef Arbre* parbre;

parbre creationarbre3(float b1,float b2,float b3,float b4,float b5,float b6)
{
    parbre a = (parbre) malloc(sizeof(Arbre));
    if (a==NULL)
    {
        exit(1);
    }
    a->col1 = b1;
    a->col2 = b2;
    a->col3 = b3;
    a->col4 = b4;
    a->col5 = b5;
    a->col6 = b6;
    a->hauteur = 0; 
    a->fg = NULL;
    a->fd = NULL;
    return a;
}

parbre creationarbre2(float b1,float b2,float b3,float b4,float b5)
{
    parbre a = (parbre) malloc(sizeof(Arbre));
    if (a==NULL)
    {
        exit(1);
    }
    a->col1 = b1;
    a->col2 = b2;
    a->col3 = b3;
    a->col4 = b4;
    a->col5 = b5;
    a->col6 = 0;
    a->hauteur = 0; 
    a->fg = NULL;
    a->fd = NULL;
    return a;
}

parbre creationarbre1(float b1,float b2,float b3,float b4)
{
    parbre a = (parbre) malloc(sizeof(Arbre));
    if (a==NULL)
    {
        exit(1);
    }
    a->col1 = b1;
    a->col2 = b2;
    a->col3 = b3;
    a->col4 = b4;
    a->col5 = 0;
    a->col6 = 0;
    a->hauteur = 0; 
    a->fg = NULL;
    a->fd = NULL;
    return a;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int hauteur(parbre a)
{
    if (a == NULL) return 0;
    return 1+(max(hauteur(a->fd),hauteur(a->fg)));
}

int equilibre(parbre a)
{
    if (a == NULL) return 0;
    return hauteur(a->fg) - hauteur(a->fd);
}

parbre Rotationdroite(parbre a)
{
    parbre b = a->fg;
    parbre c = b->fd;

    b->fd = a;
    a->fg = c;

    a->hauteur = max(hauteur(a->fg), hauteur(a->fd))+1;
    b->hauteur = max(hauteur(b->fg), hauteur(b->fd))+1;

    return b;
}

parbre Rotationgauche(parbre a)
{
    parbre b = a->fd;
    parbre c = b->fg;

    b->fg = a;
    a->fd = c;

    a->hauteur = max(hauteur(a->fg), hauteur(a->fd))+1;
    b->hauteur = max(hauteur(b->fg), hauteur(b->fd))+1;

    return b;
}
void prefixe(parbre a)
{
    if(a != NULL)
    {
        prefixe(a->fg);
        printf("%f,%f,%f,%f,%f\n", a->col1,a->col2,a->col3,a->col4,a->col5);
        prefixe(a->fd);
    }
}

void prefixefichier(parbre a,FILE * propre)
{
    if(a != NULL)
    {
        prefixefichier(a->fg,propre);
        fprintf(propre,"%.0f;%.0f;%f;%f;%f;%.0f\n", a->col1,a->col2,a->col3,a->col4,a->col5,a->col6);
        prefixefichier(a->doublon,propre);
        prefixefichier(a->fd,propre);
    }
}

void prefixefichierdecroissant(parbre a,FILE * propre)
{
    if(a != NULL)
    {
        prefixefichierdecroissant(a->fd,propre);
        fprintf(propre,"%.0f;%.0f;%f;%f;%f;%.0f\n", a->col1,a->col2,a->col3,a->col4,a->col5,a->col6);
        prefixefichierdecroissant(a->doublon,propre);
        prefixefichierdecroissant(a->fg,propre);
    }
}
parbre doubleRotationDroite(parbre a)
{
    a->fg =  Rotationgauche(a->fg);
    return Rotationdroite(a);
}
parbre doubleRotationGauche(parbre a)
{
    a->fd = Rotationdroite(a->fd);
    return Rotationgauche(a);
}

parbre inserer3(parbre a,float b1,float b2,float b3,float b4,float b5,float b6)
{
    if (b1 < 1)
    {
        if (a == NULL) return creationarbre3(b1,b2,b3,b4,b5,b6);
        else if (b1 < a->col1) a->fg  = inserer3(a->fg,b1,b2,b3,b4,b5,b6);
        else if (b1 > a->col1) a->fd = inserer3(a->fd,b1,b2,b3,b4,b5,b6);
        else 
        {
            if ( a->col2 < b2 ) a->col2 = b2 ; 
            if ( a->col3 > b3 ) a->col3 = b3 ;
            if ( a->col4 < b4 ) a->col4 = b4 ;  
            return a;
        }
    }
    else 
    {
        if (a == NULL) return creationarbre3(b1,b2,b3,b4,b5,b6);
        else if (b1 < a->col1) a->fg = inserer3(a->fg,b1,b2,b3,b4,b5,b6);
        else if (b1 > a->col1) a->fd = inserer3(a->fd,b1,b2,b3,b4,b5,b6);
        else 
        {
        a->doublon = inserer3(a->doublon,b1,b2,b3,b4,b5,b6);
        return a;
        }
    }
    a->hauteur = 1 + max(hauteur(a->fg), hauteur(a->fd));
    int eq = equilibre(a);   
    if (eq > 1 && b1 < a->fg->col1)
        return Rotationdroite(a);
    else if (eq < -1 && b1 > a->fd->col1)
        return Rotationgauche(a);
    else if (eq > 1 && b1 > a->fg->col1)
    {
        a->fg =  Rotationgauche(a->fg);
        return Rotationdroite(a);
    }
    else if (eq < -1 && b1 < a->fd->col1)
    {
        a->fd = Rotationdroite(a->fd);
        return Rotationgauche(a);
    }
    return a;
}

parbre inserer2(parbre a,float b1,float b2,float b3,float b4,float b5)
{
    if (a == NULL)
        return creationarbre2(b1,b2,b3,b4,b5);
    else if (b1 < a->col1) a->fg  = inserer2(a->fg,b1,b2,b3,b4,b5);
    else if (b1 > a->col1) a->fd = inserer2(a->fd,b1,b2,b3,b4,b5);
    else 
    {
        if ( a->col2 < b2 ) a->col2 = b2 ; 
        if ( a->col3 < b3 ) a->col3 = b3 ;
        return a;
    }
    a->hauteur = 1 + max(hauteur(a->fg), hauteur(a->fd));
    int eq = equilibre(a);   
    if (eq > 1 && b1 < a->fg->col1)
        return Rotationdroite(a);
    else if (eq < -1 && b1 > a->fd->col1)
        return Rotationgauche(a);
    else if (eq > 1 && b1 > a->fg->col1)
    {
        a->fg =  Rotationgauche(a->fg);
        return Rotationdroite(a);
    }
    else if (eq < -1 && b1 < a->fd->col1)
    {
        a->fd = Rotationdroite(a->fd);
        return Rotationgauche(a);
    }
    return a;
}

parbre inserer1(parbre a,float b1,float b2,float b3,float b4)
{
    if (a == NULL)
        return creationarbre1(b1,b2,b3,b4);
    else if (b1 < a->col1) a->fg  = inserer1(a->fg,b1,b2,b3,b4);
    else if (b1 > a->col1) a->fd = inserer1(a->fd,b1,b2,b3,b4);
    else 
    {
        a->doublon = inserer1(a->doublon,b1,b2,b3,b4);
        return a;
    }
    a->hauteur = 1 + max(hauteur(a->fg), hauteur(a->fd));
    int eq = equilibre(a);   
    if (eq > 1 && b1 < a->fg->col1)
        return Rotationdroite(a);
    else if (eq < -1 && b1 > a->fd->col1)
        return Rotationgauche(a);
    else if (eq > 1 && b1 > a->fg->col1)
    {
        a->fg =  Rotationgauche(a->fg);
        return Rotationdroite(a);
    }
    else if (eq < -1 && b1 < a->fd->col1)
    {
        a->fd = Rotationdroite(a->fd);
        return Rotationgauche(a);
    }
    return a;
}

parbre fabricationAVL3(char *ligne, float b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int l =1;  
    fgets(ligne, 1024, fp);
    char *val = strtok(ligne, ";");
    int c = 0;                                  //variable pour compter le nombre de colonnes
    for (int i = 0 ; i < nbcolonne ; i++) b[i] = 0;
    while (val != NULL)                         //pour initialiser l'arbre
    {         
        b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
        val = strtok(NULL, ";");                //Passez à la prochaine valeur
        c++;
    }
    l++;
    a = creationarbre3(b[0],b[1],b[2],b[3],b[4],b[5]);
    if (b[0]<=1000)
    {
        while (fgets(ligne, 1024, fp) != NULL)
        {
            int pourcent = (l*100.0)/nbligne;
            printf("avancement : %d  %%\r", pourcent);                //permet dafficher les lignes pour voir lavancement du traitement
            char *val = strtok(ligne, ";");             //permet de stocker ce qui il y a entre les points virgule dans un char
            int c = 0;                                  //variable pour compter le nombre de colonnes
            for (int i = 0 ; i < nbcolonne ; i++) b[i] = 0;
            while (val != NULL)                         //quand il arrive en fin de ligne
            {         
            b[c]= strtof(val,NULL);                 //stockez la dans un tableau en transformant la valeur en float
            val = strtok(NULL, ";");                //Passez à la prochaine valeur
            c++;
            }
            l++;
            a = inserer1(a,b[0],b[1],b[2],b[3]);
        }
        prefixefichierdecroissant(a,propre);
    }
    else 
    {
        while (fgets(ligne, 1024, fp) != NULL)
        {
            int pourcent = (l*100.0)/nbligne;
            printf("avancement : %d  %%\r", pourcent);                //permet dafficher les lignes pour voir lavancement du traitement
            char *val = strtok(ligne, ";");             //permet de stocker ce qui il y a entre les points virgule dans un char
            int c = 0;                                  //variable pour compter le nombre de colonnes
            for (int i = 0 ; i < nbcolonne ; i++) b[i] = 0;
            while (val != NULL)                         //quand il arrive en fin de ligne
            {         
            b[c]= strtof(val,NULL);                 //stockez la dans un tableau en transformant la valeur en float
            val = strtok(NULL, ";");                //Passez à la prochaine valeur
            c++;
            }
            l++;
            a = inserer3(a,b[0],b[1],b[2],b[3],b[4],b[5]);
        }
        prefixefichier(a,propre);
    }
    return a;
  }

int main(int argc,char* argv[])
{

//test des arguments
    int j = 0;   // compteur pour le getopt  
    char* entrée;
    char* sortie;
    int nbligne = 0;
    int nbcolonne = 0;
    int nbarg = 0;
    while ((j = getopt (argc, argv, "f:o:c:l:")) != -1) {
        switch (j) {
            case 'f':
                entrée = optarg;
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
            default:
                puts("mauvaise option");
                exit(1);
        }
    }
    if (nbarg != 4)
    {
        puts("nombre d'option invalide");
        exit(1);
    }
    FILE *fp = fopen( entrée, "rt");               // Ouvre le fichier CSV en lecture
    printf("entrée : %s\n",entrée);
    FILE * propre = fopen( sortie , "w+"); 
    printf("sortie : %s\n",sortie );                    // Ouvre le fichier CSV en lecture
    if (fp == NULL )                                 // Vérifiez que le fichier a été ouvert avec succès
    {
        printf("Erreur lors de l'ouverture du fichier d'entrée\n");
        return 2;
    }
    if (propre == NULL )                                 // Vérifiez que le fichier a été ouvert avec succès
    {
        printf("Erreur lors de l'ouverture du fichier de sortie\n");
        return 3;
    }
    parbre a;
    a = creationarbre3(0,0,0,0,0,0);
    float b[nbcolonne];   //Float car les valeurs sont ingerables en long long    
    if (b == NULL ) return 4;
    char ligne[1024];   
    a = fabricationAVL3(ligne,b,a,nbligne,nbcolonne,fp,propre);
    puts ("\nfini");
    fclose(propre);
    fclose(fp);
    return 0;
}