#include "ABR.h"

parbre creationarbre(double b1,double b2,double b3,double b4,double b5,double b6)
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

void traiter(parbre a,FILE * propre, int nbcolonne)
{
    double b[6];
    b[0]=a->col1;
    b[1]=a->col2;
    b[2]=a->col3;
    b[3]=a->col4;
    b[4]=a->col5;
    b[5]=a->col6;
    fprintf(propre,"%.0f",b[0]);  
    for (int i = 1; i <= nbcolonne-1; i++) fprintf(propre,";%f",b[i]);
    fprintf(propre,"\n");
}

void prefixefichier(parbre a,FILE * propre,int nbcolonne)
{
    if(a != NULL)
    {
        prefixefichier(a->fg,propre,nbcolonne);
        prefixefichier(a->doublon,propre,nbcolonne);
        traiter(a,propre,nbcolonne);
        prefixefichier(a->fd,propre,nbcolonne);
    }
}

void prefixefichierdecroissant(parbre a,FILE * propre,int nbcolonne)
{
    if(a != NULL)
    {
        prefixefichierdecroissant(a->fd,propre,nbcolonne);
        traiter(a,propre,nbcolonne);
        prefixefichierdecroissant(a->doublon,propre,nbcolonne);
        prefixefichierdecroissant(a->fg,propre,nbcolonne);
    }
}

parbre insererABRt1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRt1(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRt1(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            if (b2 != 0)    a->col2=(a->col2+b2)/2;
            if (b3 < a->col3 && b3 != 0) a->col3 = b3;
            else if (a->col3 == 0) a->col3 = b2;
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
        {   return creationarbre(b1,b2,b3,b4,0,0);
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
        {   return creationarbre(b1,b2,b3,b4,b5,b6);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRt3(a->fg,b1,b2,b3,b4,b5,b6,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRt3(a->fd,b1,b2,b3,b4,b5,b6,h);
        else 
        {
            parbre b = creationarbre(b1,b2,b3,b4,b5,b6);
            b->doublon = a;
            b->fd = a->fd;
            b->fg = a->fg;
            a->fg = NULL;
            a->fd = NULL;
            a = b;
            *h=0;
        }
    return a;
}

parbre insererABRm(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{
        if (a == NULL) 
        {   return creationarbre(b1,b2,b3,b4,b5,b6);
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

parbre insererABRw(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{

        if (a == NULL) 
        {   return creationarbre(b1,b2,b3,b4,b5,b6);
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
        {   return creationarbre(b1,b2,b3,b4,b5,b6);
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
        {   return creationarbre(b1,b2,b3,b4,0,0);
            *h=1;   }
        else if (b1 < a->col1) 
        {   a->fg  = insererABRh(a->fg,b1,b2,b3,b4,h);
            *h=-*h; }
        else if (b1 > a->col1) a->fd = insererABRh(a->fd,b1,b2,b3,b4,h);
        else 
        {    
            if (b2 != a->col2 ) 
            {
                if (a->doublon==NULL) a->doublon = creationarbre(b1,b2,b3,b4,0,0);
                else insererABRh(a->doublon,b1,b2,b3,b4,h);
            }
            *h=0;
        }
        return a;
}

parbre fabricationABRt1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1],b[2],b[3],b[4],b[5]);
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
    if (reverse == 0) prefixefichier(a,propre,nbcolonne);
    else prefixefichierdecroissant(a,propre,nbcolonne);
    return a;
  }

parbre fabricationABRt2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0]/pow(10,8),b[1],b[2],b[3],b[4],b[5]);
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
    if (reverse == 0) prefixefichier(a,propre,nbcolonne);
    else prefixefichierdecroissant(a,propre,nbcolonne);
    return a;
  }

parbre fabricationABRt3(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1]/pow(10,8),b[2],b[3],b[4],b[5]);
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
    if (reverse == 0) prefixefichier(a,propre,nbcolonne);
    else prefixefichierdecroissant(a,propre,nbcolonne);
    return a;
  }

parbre fabricationABRt32(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1],b[2],b[3],b[4],b[5]);
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
    if (reverse == 0) prefixefichier(a,propre,nbcolonne);
    else prefixefichierdecroissant(a,propre,nbcolonne);
    return a;
  }

parbre fabricationABRm(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1],b[2],b[3],b[4],b[5]);
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
    if (reverse == 0) prefixefichier(a,propre,nbcolonne);
    else prefixefichierdecroissant(a,propre,nbcolonne);
    return a;
  }

parbre fabricationABRm2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1],b[2],b[3],b[4],b[5]);
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
    if (reverse == 0) prefixefichierdecroissant(a,propre,nbcolonne);
    else prefixefichier(a,propre,nbcolonne);
    return a;
  }

parbre fabricationABRw(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1],b[2],b[3],b[4],b[5]);
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
    if (reverse == 0) prefixefichier(a,propre,nbcolonne);
    else prefixefichierdecroissant(a,propre,nbcolonne);
    return a;
  }

parbre fabricationABRp1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1],0,0,b[2],b[3]);
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
    if (reverse == 0) prefixefichier(a,propre,nbcolonne+2);
    else prefixefichierdecroissant(a,propre,nbcolonne+2);
    return a;
  }

parbre fabricationABRh(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre,int reverse)
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
    a = creationarbre(b[0],b[1],b[2],b[3],0,0);
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
    if (reverse == 0) prefixefichierdecroissant(a,propre,nbcolonne);
    else prefixefichier(a,propre,nbcolonne);
    return a;
  }
