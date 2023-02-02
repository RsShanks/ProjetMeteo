#ifndef Filtre_ZONE_h
#define Filtre_ZONE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

void fabrication(char *ligne, double b[],int nbligne,int nbcolonne,FILE * fp,FILE * propre,int X_max,int X_min,int Y_max,int Y_min);

#endif