#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define MALLOC(x) ((x*)) malloc(sizeof(x))

typedef struct arbre{
    float col1;
    float col2;
    float col3;
    float col4;
    float col5;
    struct arbre* doublon;
    struct arbre* fd;
    struct arbre* fg;
}Arbre;

typedef Arbre* parbre;

parbre creationarbre3(float b1,float b2,float b3)
{
    parbre a = (parbre) malloc(sizeof(Arbre));
    if (a==NULL)
    {
        exit(1);
    }
    a->col1 = b1;
    a->col2 = b2;
    a->col3 = b3;
    a->col4 = 0;
    a->col5 = 0;
    a->fg = NULL;
    a->fd = NULL;
    a->doublon = NULL;
    return a;
}

parbre creationarbre4(float b1,float b2,float b3,float b4)
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
    a->fg = NULL;
    a->fd = NULL;
    a->doublon = NULL;
    return a;
}

parbre creationarbre5(float b1,float b2,float b3,float b4,float b5)
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
    a->fg = NULL;
    a->fd = NULL;
    a->doublon = NULL;
    return a;
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

parbre insertABR5(parbre a,float b1, float b2, float b3,float b4,float b5)
{
    if(a == NULL){
        a = creationarbre5(b1,b2,b3,b4,b5);
        return a;
    }
    else{
        if(a->col1 < b1) a->fd =  insertABR5(a->fd, b1,b2,b3,b4,b5);   
        else if(a->col1 > b1) a->fg = insertABR5(a->fg,b1,b2,b3,b4,b5);
        else a->doublon = insertABR5(a->doublon,b1,b2,b3,b4,b5);
    }
    return a;
}

parbre insertABR4(parbre a,float b1, float b2, float b3,float b4)
{
    if(a == NULL){
        a = creationarbre4(b1,b2,b3,b4);
        return a;
    }
    else{
        if(a->col1 < b1) a->fd =  insertABR4(a->fd, b1,b2,b3,b4);   
        else if(a->col1 > b1) a->fg = insertABR4(a->fg,b1,b2,b3,b4);
        else a->doublon = insertABR4(a->doublon,b1,b2,b3,b4);
    }
    return a;
}

parbre insertABR3(parbre a,float b1, float b2, float b3)
{
    if(a == NULL){
        a = creationarbre3(b1,b2,b3);
        return a;
    }
    else{
        if(a->col1 < b1) a->fd =  insertABR3(a->fd, b1,b2,b3);   
        else if(a->col1 > b1) a->fg = insertABR3(a->fg,b1,b2,b3);
        else a->doublon = insertABR3(a->doublon,b1,b2,b3);
    }
    return a;
}

void prefixefichier(parbre a,FILE * propre)
{
    if(a != NULL)
    {
        prefixefichier(a->fg,propre);
        fprintf(propre,"%f;%f;%f;%f;%f\n", a->col1,a->col2,a->col3,a->col4,a->col5);
        prefixefichier(a->doublon,propre);
        prefixefichier(a->fd,propre);
    }
}

parbre fabricationABR5(char *ligne, float b[],parbre a,int nbligne,char * nbcolonne,FILE * fp)
  { int l =1;  
    fgets(ligne, 1024, fp);
    char *val = strtok(ligne, ";");
    int c = 0;                                  //variable pour compter le nombre de colonnes
    for (int i = 0 ; i < atoi(nbcolonne) ; i++) b[i] = 0;
    while (val != NULL)                         //pour initialiser l'arbre
    {         
        b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
        val = strtok(NULL, ";");                //Passez à la prochaine valeur
        c++;
    }
    l++;
    a = creationarbre5(b[0],b[1],b[2],b[3],b[4]);
    while (fgets(ligne, 1024, fp) != NULL)
    {
        int temps = clock()/CLOCKS_PER_SEC;
        printf("temps : %d s", temps);
        int pourcent = (l*100.0)/nbligne;
        printf(" avancement : %d  %%\r", pourcent);                //permet dafficher les lignes pour voir lavancement du traitement
        char *val = strtok(ligne, ";");             //permet de stocker ce qui il y a entre les points virgule dans un char
        int c = 0;                                  //variable pour compter le nombre de colonnes
        for (int i = 0 ; i < atoi(nbcolonne) ; i++) b[i] = 0;
        while (val != NULL)                         //quand il arrive en fin de ligne
        {         
           b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
           val = strtok(NULL, ";");                //Passez à la prochaine valeur
           c++;
        }
        l++;
        a = insertABR5(a,b[0],b[1],b[2],b[3],b[4]);
    }
    return a;
  }

parbre fabricationABR4(char *ligne, float b[],parbre a,int nbligne,char * nbcolonne,FILE * fp)
  { int l =1;  
    fgets(ligne, 1024, fp);
    char *val = strtok(ligne, ";");
    int c = 0;                                  //variable pour compter le nombre de colonnes
    for (int i = 0 ; i < atoi(nbcolonne) ; i++) b[i] = 0;
    while (val != NULL)                         //pour initialiser l'arbre
    {         
        b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
        val = strtok(NULL, ";");                //Passez à la prochaine valeur
        c++;
    }
    l++;
    a = creationarbre4(b[0],b[1],b[2],b[3]);
    while (fgets(ligne, 1024, fp) != NULL)
    {
        int temps = clock()/CLOCKS_PER_SEC;
        printf("temps : %d s", temps);
        int pourcent = (l*100.0)/nbligne;
        printf(" avancement : %d  %%\r", pourcent);                //permet dafficher les lignes pour voir lavancement du traitement
        char *val = strtok(ligne, ";");             //permet de stocker ce qui il y a entre les points virgule dans un char
        int c = 0;                                  //variable pour compter le nombre de colonnes
        for (int i = 0 ; i < atoi(nbcolonne) ; i++) b[i] = 0;
        while (val != NULL)                         //quand il arrive en fin de ligne
        {         
           b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
           val = strtok(NULL, ";");                //Passez à la prochaine valeur
           c++;
        }
        l++;
        a = insertABR4(a,b[0],b[1],b[2],b[3]);
    }
    prefixe(a);
    return a;
  }

parbre fabricationABR3(char *ligne, float b[],parbre a,int nbligne,char * nbcolonne,FILE * fp)
  { int l =1;  
    fgets(ligne, 1024, fp);
    char *val = strtok(ligne, ";");
    int c = 0;                                  //variable pour compter le nombre de colonnes
    for (int i = 0 ; i < atoi(nbcolonne) ; i++) b[i] = 0;
    while (val != NULL)                         //pour initialiser l'arbre
    {         
        b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
        val = strtok(NULL, ";");                //Passez à la prochaine valeur
        c++;
    }
    l++;
    a = creationarbre3(b[0],b[1],b[2]);
    while (fgets(ligne, 1024, fp) != NULL)
    {
        int temps = clock()/CLOCKS_PER_SEC;
        printf("temps : %d s", temps);
        int pourcent = (l*100.0)/nbligne;
        printf(" avancement : %d  %%\r", pourcent);                //permet dafficher les lignes pour voir lavancement du traitement
        char *val = strtok(ligne, ";");             //permet de stocker ce qui il y a entre les points virgule dans un char
        int c = 0;                                  //variable pour compter le nombre de colonnes
        for (int i = 0 ; i < atoi(nbcolonne) ; i++) b[i] = 0;
        while (val != NULL)                         //quand il arrive en fin de ligne
        {         
           b[c]= strtof(val,NULL);                 //stockez la dans la matrice en transformant la valeur en float
           val = strtok(NULL, ";");                //Passez à la prochaine valeur
           c++;
        }
        l++;
        a = insertABR3(a,b[0],b[1],b[2]);
    }
    prefixe(a);
    return a;
  }
int main(int argc,char *argv[])
{   
    printf("%d", atoi(argv[6]));
    FILE *fp = fopen(argv[2], "rt");                                   // Ouvre le fichier CSV en lecture
    printf("entre : %s\n",argv[2]);
    FILE * propre = fopen( argv[4] , "w+"); 
    printf("sortie : %s\n",argv[4]);                                   // Ouvre le fichier CSV en lecture
    if (fp == NULL || propre == NULL )                                 // Vérifiez que le fichier a été ouvert avec succès
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return 4;
    }
    parbre a;
    a = creationarbre5(0,0,0,0,0);
    float b[atoi(argv[6])-1];   //Float car les valeurs sont ingerables en long long    
    if (b == NULL ) return 4;
    char ligne[1024];   
    
    if (atoi(argv[6]) == 5)   a = fabricationABR5(ligne,b,a,atoi(argv[5]),argv[6],fp);
    if (atoi(argv[6]) == 4)   a = fabricationABR4(ligne,b,a,atoi(argv[5]),argv[6],fp);
    if (atoi(argv[6]) == 3)   a = fabricationABR3(ligne,b,a,atoi(argv[5]),argv[6],fp);
    puts ("fini");
    prefixefichier(a,propre);
    fclose(propre);
    fclose(fp);
    return 0;
}