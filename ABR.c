#include "ABR.h"

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

parbre insererABRt1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRt1(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRt1(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 != 0)    a->col2=(a->col2+b2)/2;
            if (b3 < a->col3 && b3 != 0) a->col3 = b3;
            else if (a->col3 == 0)  a->col3 = b2;
            else if (b2 < a->col3 ) a->col3=b2;
            if (b4 > a->col4) a->col4 = b4;
            else if (b2 > a->col4) a->col4=b2;           
            *h=0;
        }
    return a;
}

parbre insererABRt2(parbre a,double b1,double b2,double b3,double b4,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,0,0);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRt2(a->fg,b1,b2,b3,b4,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRt2(a->fd,b1,b2,b3,b4,h);
        else 
        {
            a->col2=(a->col2+b2)/2;
            *h=0;
        }
    return a;
}

parbre insererABRt3(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRt3(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRt3(a->fd,b1,b2,b3,b4,b5,b6,h);
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
        }
    return a;
}

parbre insererABRm(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{
        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRm(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRm(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 > a->col2) a->col2 = b2;
            *h=0;
        }
    return a;
}

parbre insererABRm2(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRm2(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRm2(a->fd,b1,b2,b3,b4,b5,b6,h);
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
        }
    return a;
}

parbre insererABRw(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRw(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRw(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 != 0)    a->col2=(a->col2+b2)/2;
            if (b3 != 0)    a->col3=(a->col3+b3)/2;      
            *h=0;
        }
    return a;
}

parbre insererABRp1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRp1(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRp1(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 != 0)    a->col2=(a->col2+b2)/2;
            if ((b2 < a->col3 && b2 != 0) || a->col3 == 0) a->col3 = b2;
            if ((b2 < a->col4 && b2 != 0) || a->col4 == 0) a->col4 = b2;         
            *h=0;
        }
    return a;
}

parbre insererABRh(parbre a,double b1,double b2,double b3,double b4,int* h)
{

        if (a == NULL) 
        {   return creationarbre3(b1,b2,b3,b4,0,0);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRh(a->fg,b1,b2,b3,b4,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRh(a->fd,b1,b2,b3,b4,h);
        else 
        {    
            if (b2 != a->col2 ) 
            {
                if (a->doublon==NULL) a->doublon = creationarbre3(b1,b2,b3,b4,0,0);
                else insererABRh(a->doublon,b1,b2,b3,b4,h);
            }
            *h=0;
        }
        return a;
}

parbre fabricationABRt1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererABRt1(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationABRt2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererABRt2(a,b[0]/pow(10,8),b[1],b[2],b[3],&h);
    }
    prefixefichier4(a,propre);
    return a;
  }

parbre fabricationABRt3(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererABRt3(a,b[0],b[1]/pow(10,8),b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationABRt32(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererABRt3(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationABRm(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererABRm(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationABRm2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererABRm2(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichierdecroissant(a,propre);
    return a;
  }

parbre fabricationABRw(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererABRw(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationABRp1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
    a = creationarbre3(b[0],b[1],0,0,b[2],b[3]);
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
        a = insererABRp1(a,b[0],b[1],0,0,b[2],b[3],&h);
    }
    prefixefichier(a,propre);
    return a;
  }

parbre fabricationABRh(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
    a = creationarbre3(b[0],b[1],b[2],b[3],0,0);
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
        a = insererABRh(a,b[0],b[1],b[2],b[3],&h);
    }
    prefixefichierdecroissant(a,propre);
    return a;
  }
