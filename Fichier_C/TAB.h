#ifndef Filtre_ZONE_h
#define Filtre_ZONE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "ABR.h"

void parcoursfichier(parbre a,FILE * propre,int nbcolonne);
parbre insererTABt1(parbre a,double b1,double b2,double b3,double b4,double b5,double b6,int* h);
parbre fabricationTABt1(char *ligne, double b[],parbre a,int nbligne,int nbcolonne,FILE * fp,FILE * propre);

#endif