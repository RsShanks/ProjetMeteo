#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#define MALLOC(x) ((x*)) malloc(sizeof(x))

typedef struct arbre{
    double col1;
    double col2;
    double col3;
    double col4;
    double col5;
    double col6;
    int equilibre;
    struct arbre* doublon;
    struct arbre* fd;
    struct arbre* fg;
}Arbre;

typedef Arbre* parbre;

parbre creationarbre3(double b1,double b2,double b3,double b4,double b5,double b6)
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
    a->equilibre = 0;
    a->fg = NULL;
    a->fd = NULL;
    return a;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int min(int a, int b)
{
    return (a < b)? a : b;
}

parbre Rotationdroite(parbre a)
{
    parbre pivot = a->fg;
    int eq_a,eq_p;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a-min(eq_p,0)+1;
    pivot->equilibre = max(eq_a+2, max(eq_a+eq_p+2,eq_p+1));
    a=pivot;
    return a;
}

parbre Rotationgauche(parbre a)
{
    parbre pivot = a->fd;
    int eq_a,eq_p;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre = eq_a-max(eq_p,0)-1;
    pivot->equilibre = min(eq_a-2, min(eq_a+eq_p-2,eq_p-1));
    a=pivot;
    return a;
}

void prefixefichier(parbre a,FILE * propre)
{
    if(a != NULL)
    {
        prefixefichier(a->fg,propre);
        prefixefichier(a->doublon,propre);
        fprintf(propre,"%.0f;%.0f;%f;%f;%f;%f\n", a->col1,a->col2,a->col3,a->col4,a->col5,a->col6);
        prefixefichier(a->fd,propre);
    }
}

void prefixefichier4(parbre a,FILE * propre)
{
    if(a != NULL)
    {
        prefixefichier4(a->fg,propre);
        prefixefichier4(a->doublon,propre);
        fprintf(propre,"%.0f;%.0f;%f;%f\n", a->col1,a->col2,a->col3,a->col4);
        prefixefichier4(a->fd,propre);
    }
}

void prefixefichierdecroissant(parbre a,FILE * propre)
{
    if(a != NULL)
    {
        prefixefichierdecroissant(a->fd,propre);
        fprintf(propre,"%.0f;%.0f;%f;%f\n", a->col1,a->col2,a->col3,a->col4);
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

parbre inserert1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = inserert1(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = inserert1(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 != 0)    a->col2=(a->col2+b2)/2;
            if (b3 < a->col3 && b3 != 0) a->col3 = b3;
            else if (a->col3 == 0)  a->col3 = b2;
            else if (b2 < a->col3 ) a->col3=b2;
            if (b4 > a->col4) a->col4 = b4;
            else if (b2 > a->col4) a->col4=b2;           
            *h=0;
            return a;
        }
    if (*h != 0)
    {
        a->equilibre = a->equilibre+*h;  
        if (a->equilibre > 1 && b1 < a->fg->col1)
            return Rotationdroite(a);
        else if (a->equilibre < -1 && b1 > a->fd->col1)
            return Rotationgauche(a);
        else if (a->equilibre > 1 && b1 > a->fg->col1)
        {
            a->fg =  Rotationgauche(a->fg);
            return Rotationdroite(a);
        }
        else if (a->equilibre < -1 && b1 < a->fd->col1)
        {
            a->fd = Rotationdroite(a->fd);
            return Rotationgauche(a);
        }
        if (a->equilibre == 0) *h = 0;
        else *h =1; 
    }
    return a;
}

parbre inserert2(parbre a,double b1,double b2,double b3,double b4,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,0,0);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = inserert2(a->fg,b1,b2,b3,b4,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = inserert2(a->fd,b1,b2,b3,b4,h);
        else 
        {
            a->col2=(a->col2+b2)/2;
            *h=0;
            return a;
        }
    if (*h != 0)
    {
        a->equilibre = a->equilibre+*h;  
        if (a->equilibre > 1 && b1 < a->fg->col1)
            return Rotationdroite(a);
        else if (a->equilibre < -1 && b1 > a->fd->col1)
            return Rotationgauche(a);
        else if (a->equilibre > 1 && b1 > a->fg->col1)
        {
            a->fg =  Rotationgauche(a->fg);
            return Rotationdroite(a);
        }
        else if (a->equilibre < -1 && b1 < a->fd->col1)
        {
            a->fd = Rotationdroite(a->fd);
            return Rotationgauche(a);
        }
        if (a->equilibre == 0) *h = 0;
        else *h =1; 
    }
    return a;
}

parbre inserert3(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = inserert3(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = inserert3(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (a->doublon==NULL) a->doublon = creationarbre3(b1,b2,b3,b4,b5,b6);
                else 
                {
                    parbre b = creationarbre3(b1,b2,b3,b4,b5,b6);
                    b->doublon = a->doublon;
                    a->doublon = b;
                }
            *h=0;
            return a;
        }
    if (*h != 0)
    {
        a->equilibre = a->equilibre+*h;  
        if (a->equilibre > 1 && b1 < a->fg->col1)
            return Rotationdroite(a);
        else if (a->equilibre < -1 && b1 > a->fd->col1)
            return Rotationgauche(a);
        else if (a->equilibre > 1 && b1 > a->fg->col1)
        {
            a->fg =  Rotationgauche(a->fg);
            return Rotationdroite(a);
        }
        else if (a->equilibre < -1 && b1 < a->fd->col1)
        {
            a->fd = Rotationdroite(a->fd);
            return Rotationgauche(a);
        }
        if (a->equilibre == 0) *h = 0;
        else *h =1; 
    }
    return a;
}

parbre insererm(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{
        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererm(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererm(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 > a->col2) a->col2 = b2;
            *h=0;
            return a;
        }
    if (*h != 0)
    {
        a->equilibre = a->equilibre+*h;  
        if (a->equilibre > 1 && b1 < a->fg->col1)
            return Rotationdroite(a);
        else if (a->equilibre < -1 && b1 > a->fd->col1)
            return Rotationgauche(a);
        else if (a->equilibre > 1 && b1 > a->fg->col1)
        {
            a->fg =  Rotationgauche(a->fg);
            return Rotationdroite(a);
        }
        else if (a->equilibre < -1 && b1 < a->fd->col1)
        {
            a->fd = Rotationdroite(a->fd);
            return Rotationgauche(a);
        }
        if (a->equilibre == 0) *h = 0;
        else *h =1; 
    }
    return a;
}

parbre insererm2(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererm2(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererm2(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (a->doublon==NULL) a->doublon = creationarbre3(b1,b2,b3,b4,b5,b6);
                else 
                {
                    parbre b = creationarbre3(b1,b2,b3,b4,b5,b6);
                    b->doublon = a->doublon;
                    a->doublon = b;
                }
            *h=0;
            return a;
        }
    if (*h != 0)
    {
        a->equilibre = a->equilibre+*h;  
        if (a->equilibre > 1 && b1 < a->fg->col1)
            return Rotationdroite(a);
        else if (a->equilibre < -1 && b1 > a->fd->col1)
            return Rotationgauche(a);
        else if (a->equilibre > 1 && b1 > a->fg->col1)
        {
            a->fg =  Rotationgauche(a->fg);
            return Rotationdroite(a);
        }
        else if (a->equilibre < -1 && b1 < a->fd->col1)
        {
            a->fd = Rotationdroite(a->fd);
            return Rotationgauche(a);
        }
        if (a->equilibre == 0) *h = 0;
        else *h =1; 
    }
    return a;
}

parbre insererw(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererw(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererw(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 != 0)    a->col2=(a->col2+b2)/2;
            if (b3 != 0)    a->col3=(a->col3+b3)/2;      
            *h=0;
            return a;
        }
    if (*h != 0)
    {
        a->equilibre = a->equilibre+*h;  
        if (a->equilibre > 1 && b1 < a->fg->col1)
            return Rotationdroite(a);
        else if (a->equilibre < -1 && b1 > a->fd->col1)
            return Rotationgauche(a);
        else if (a->equilibre > 1 && b1 > a->fg->col1)
        {
            a->fg =  Rotationgauche(a->fg);
            return Rotationdroite(a);
        }
        else if (a->equilibre < -1 && b1 < a->fd->col1)
        {
            a->fd = Rotationdroite(a->fd);
            return Rotationgauche(a);
        }
        if (a->equilibre == 0) *h = 0;
        else *h =1; 
    }
    return a;
}

parbre fabricationAVLt1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int h=0;
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
    a = creationarbre3(b[0],b[1],b[2],b[3],b[4],b[5]);
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
        a = inserert1(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationAVLt2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int h=0;
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
    a = creationarbre3(b[0]/pow(10,8),b[1],b[2],b[3],b[4],b[5]);
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
        a = inserert2(a,b[0]/pow(10,8),b[1],b[2],b[3],&h);
    }
    prefixefichier4(a,propre);
    return a;
  }

parbre fabricationAVLt3(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int h=0;
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
    a = creationarbre3(b[0],b[1]/pow(10,8),b[2],b[3],b[4],b[5]);
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
        a = inserert3(a,b[0],b[1]/pow(10,8),b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationAVLt32(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int h=0;
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
    a = creationarbre3(b[0],b[1],b[2],b[3],b[4],b[5]);
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
        a = inserert3(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationAVLm(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int h=0;
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
    a = creationarbre3(b[0],b[1],b[2],b[3],b[4],b[5]);
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
        a = insererm(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationAVLm2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int h=0;
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
    a = creationarbre3(b[0],b[1],b[2],b[3],b[4],b[5]);
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
        a = insererm2(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichierdecroissant(a,propre);
    return a;
  }

parbre fabricationAVLw(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
  { 
    int h=0;
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
    a = creationarbre3(b[0],b[1],b[2],b[3],b[4],b[5]);
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
        a = insererw(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

int main(int argc,char* argv[])
{

//test des arguments
    int j = 0;   // compteur pour le getopt  
    char* entree;
    char* sortie;
    int nbligne = 0;
    int nbcolonne = 0;
    int nbarg = 0;
    int arg =0;
    while ((j = getopt (argc, argv, "f:o:c:l:t:p:whm:")) != -1) {
        switch (j) {
            case 'f':
                entree = optarg;
                nbarg += 1;
                break;
            case 'o':
                sortie = optarg;
                nbarg += 1;
                break;
            case 't':
                nbarg+= 1;
                if (atoi(optarg)==1) arg = 11;
                else if(atoi(optarg)==2) arg = 12;
                else if(atoi(optarg)==3) arg = 13;
                else if(atoi(optarg)==0) arg = 10;
                else{
                    puts("numéro de mode incorrect");
                    exit(1);
                }
                break;                      
            case 'p':
                if (atoi(optarg)==1)
                {
                    arg = 21;
                }
                else if(atoi(optarg)==2){
                    arg = 22;
                }
                else if(atoi(optarg)==3){
                    arg = 23;
                }
                else if(atoi(optarg)==0){
                    arg = 20;
                }
                else{
                    puts("numéro de mode incorrect");
                    exit(1);
                }
                nbarg += 1;
                break;
            case 'w':
                arg = 4;        //ordre croisant
                nbarg+=1;
                break;
            case 'h':
            case 'm':
                if (atoi(optarg) == 0) arg = 5;
                else if (atoi(optarg)==1) arg = 51;
                nbarg+=1;
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
    if (nbarg != 5)
    {
        puts("nombre d'option invalide");
        exit(1);
    }
    FILE *fp = fopen( entree, "rt");               // Ouvre le fichier CSV en lecture
    printf("entree : %s\n",entree);
    FILE * propre = fopen( sortie , "w+"); 
    printf("sortie : %s\n",sortie );                    // Ouvre le fichier CSV en lecture
    if (fp == NULL )                                 // Verifiez que le fichier a ete ouvert avec succès
    {
        puts("Erreur lors de l'ouverture du fichier d'entree");
        return 2;
    }
    if (propre == NULL )                                 // Verifiez que le fichier a ete ouvert avec succès
    {
        puts("Erreur lors de l'ouverture du fichier de sortie");
        return 3;
    }
    parbre a;
    a = creationarbre3(0,0,0,0,0,0);
    double b[nbcolonne];   //double car les valeurs sont ingerables en long long    
    if (b == NULL ) return 4;
    char ligne[1024];   

    if (arg==11 || arg == 21 )a = fabricationAVLt1(ligne,b,a,nbligne,nbcolonne,fp,propre);          //mode : t1 p1
    else if (arg==13 || arg == 23 )a = fabricationAVLt3(ligne,b,a,nbligne,nbcolonne,fp,propre);     //mode : t3 p3
    else if ( arg == 10 ) a = fabricationAVLt32(ligne,b,a,nbligne,nbcolonne,fp,propre);             //mode : 2nd tri du t3 p3 et t2 p2
    else if (arg == 12 || arg == 22 ) a = fabricationAVLt2(ligne,b,a,nbligne,nbcolonne,fp,propre); 
    else if ( arg == 5 ) a = fabricationAVLm(ligne,b,a,nbligne,nbcolonne,fp,propre);
    else if ( arg == 51 ) a = fabricationAVLm2(ligne,b,a,nbligne,nbcolonne,fp,propre);
    else if ( arg == 4 ) a = fabricationAVLw(ligne,b,a,nbligne,nbcolonne,fp,propre);
    puts ("\n");
    fclose(propre);
    fclose(fp);
    return 0;
}