#ifndef AVL_h
#define AVL_h

    #include "ABR.h"
    #define MALLOC(x) ((x*)) malloc(sizeof(x))

    int max(int a, int b);
    int min(int a, int b);
    parbre Rotationdroite(parbre a);
    parbre Rotationgauche(parbre a);
    parbre doubleRotationDroite(parbre a);
    parbre doubleRotationGauche(parbre a);
    parbre inserert1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre inserert2(parbre a,double b1,double b2,double b3,double b4,int* h);
    parbre inserert3(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererm(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererm2(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererw(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererp1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
    parbre insererh(parbre a,double b1,double b2,double b3,double b4,int* h);
    parbre fabricationAVLt1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLt2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLt3(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLt32(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLm(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLm2(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLw(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLp1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);
    parbre fabricationAVLh(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);

#endif