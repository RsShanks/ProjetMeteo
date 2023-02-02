#ifndef ABR_h
#define ABR_h
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
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
    parbre creationarbre3 (double b1,double b2,double b3,double b4,double b5,double b6);
    void prefixefichier(parbre a,FILE * propre);
    void prefixefichier4(parbre a,FILE * propre);
    void prefixefichierdecroissant(parbre a,FILE * propre);
    parbre insererABRt1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererABRt2(parbre a,double b1,double b2,double b3,double b4,int* h);
    parbre insererABRt3(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererABRm(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererABRm2(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererABRw(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererABRp1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererABRh(parbre a,double b1,double b2,double b3,double b4,int* h);
    parbre fabricationABRt1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRt2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRt3(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRt32(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRm(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRm2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRw(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRp1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationABRh(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);

#endif