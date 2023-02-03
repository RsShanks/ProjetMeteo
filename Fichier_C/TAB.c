#include "TAB.h"

void parcoursfichier(parbre a,FILE * propre,int nbcolonne)
{
    while (a != NULL)
    {
        traiter(a,propre,nbcolonne);
        a=a->fd;
    }
}

parbre insererTABt1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h)
{
    parbre q = a;
    while (q->fd != NULL )
    {
        if (q->fd->col1 > b1)
        {
            parbre k = creationarbre(b1,b2,b3,b4,b5,b6);
            k->fd = q->fd;
            q->fd = k;
            return a;
        }
        else if (q->fd->col1 == b1)
        {
            q=q->fd;
            if (b2 != 0) q->col2=(q->col2+b2)/2;
            if (b3 < q->col3 && b3 != 0) q->col3 = b3;
            else if (q->col3 == 0)  q->col3 = b2;
            else if (b2 < q->col3 ) q->col3=b2;
            if (b4 > q->col4) q->col4 = b4;
            else if (b2 > q->col4) q->col4=b2;
            return a;
        }
        a=a->fd;      
    }
    parbre k = creationarbre(b1,b2,b3,b4,b5,b6);
    q->fd = k;
    return a;
}

parbre fabricationTABt1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre)
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
        a = insererTABt1(a,b[0],b[1],b[2],b[3],b[4],b[5],&h);
    }
    parcoursfichier(a,propre,nbcolonne);
    return a;
  }

