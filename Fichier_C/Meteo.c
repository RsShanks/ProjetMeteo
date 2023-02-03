#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "TAB.h"
#include "ABR.h"
#include "Filtre_ZONE.h"
#include "AVL.h"


int main(int argc,char* argv[])
{

//test des arguments
    int j = 0;   // compteur pour le getopt  
    char* entree;
    char* sortie;
    char* zone;
    int tri = 0;
    int nbligne = 0;
    int nbcolonne = 0;
    int nbarg = 0;
    int arg =0;
    int reverse=0;
    while ((j = getopt (argc, argv, "f:o:c:l:t:p:whm:z:k:r:")) != -1) {
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
                    exit(1);
                }
                nbarg += 1;
                break;
            case 'w':
                arg = 4;        //ordre croisant
                nbarg+=1;
                break;
            case 'h':
                arg = 3;
                nbarg+=1;
                break;
            case 'm':
                if (atoi(optarg) == 0) arg = 5;
                else if (atoi(optarg)==1) arg = 51;
                nbarg+=1;
                break;
            case 'k':
                tri = atoi(optarg);
                nbarg+=1;
                break;
            case 'c':
                nbcolonne = atoi(optarg);
                if (nbcolonne <= 0)
                {
                    exit(1);
                }
                nbarg += 1;
                break;
            case 'l':
                nbligne = atoi(optarg);
                if (nbligne <= 0)
                {
                    exit(1);
                }
                nbarg += 1;
                break;
            case 'z': 
                zone = optarg;
                nbarg += 1;
                break;
            case 'r':
                reverse = atoi(optarg);
                break;
            default:
                exit(1);
        }
    }
    puts ("ici");
    if (nbarg != 6)     exit(1);
    FILE *fp = fopen( entree, "rt");               // Ouvre le fichier CSV en lecture
    printf("entree : %s\n",entree);
    FILE * propre = fopen( sortie , "w+"); 
    printf("sortie : %s\n",sortie );                    // Ouvre le fichier CSV en ecriture
    if (fp == NULL )                                 // Verifiez que le fichier a ete ouvert avec succès
    {
        return 2;
    }
    if (propre == NULL )                                 // Verifiez que le fichier a ete ouvert avec succès
    {
        return 3;
    }
    if ( tri == 1 )
    {    parbre a;
        a = creationarbre(0,0,0,0,0,0);
        double b[nbcolonne];   //double car les valeurs sont ingerables en long long    
        if (b == NULL ) return 4;
        char ligne[1024];   

        if (arg==11)a = fabricationAVLt1(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);          //mode : t1 p1
        else if (arg==13 || arg == 23 )a = fabricationAVLt3(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);     //mode : t3 p3
        else if ( arg == 10 ) a = fabricationAVLt32(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);             //mode : 2nd tri du t3 p3 et t2 p2
        else if (arg == 12 || arg == 22 ) a = fabricationAVLt2(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse); 
        else if ( arg == 5 ) a = fabricationAVLm(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if ( arg == 51 ) a = fabricationAVLm2(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if ( arg == 4 ) a = fabricationAVLw(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if (arg == 21) a = fabricationAVLp1(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if (arg == 3) a = fabricationAVLh(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        free(a);}

    else if ( tri == 2 )
    {    parbre a;
        a = creationarbre(0,0,0,0,0,0);
        double b[nbcolonne];   //double car les valeurs sont ingerables en long long    
        if (b == NULL ) return 4;
        char ligne[1024];   

        if (arg==11)a = fabricationABRt1(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);          //mode : t1 p1
        else if (arg==13 || arg == 23 )a = fabricationABRt3(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);     //mode : t3 p3
        else if ( arg == 10 ) a = fabricationABRt32(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);             //mode : 2nd tri du t3 p3 et t2 p2
        else if (arg == 12 || arg == 22 ) a = fabricationABRt2(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse); 
        else if ( arg == 5 ) a = fabricationABRm(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if ( arg == 51 ) a = fabricationABRm2(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if ( arg == 4 ) a = fabricationABRw(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if (arg == 21) a = fabricationABRp1(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        else if (arg == 3) a = fabricationABRh(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);
        free(a);}
    else if ( tri == 3)
    {
        parbre a;
        a = creationarbre(0,0,0,0,0,0);
        double b[nbcolonne];   //double car les valeurs sont ingerables en long long    
        if (b == NULL ) return 4;
        char ligne[1024];  
        if (arg==11)a = fabricationTABt1(ligne,b,a,nbligne,nbcolonne,fp,propre);          //mode : t1 p1
        /*else if (arg==13 || arg == 23 )a = fabricationTABt3(ligne,b,a,nbligne,nbcolonne,fp,propre);     //mode : t3 p3
        else if ( arg == 10 ) a = fabricationTABt32(ligne,b,a,nbligne,nbcolonne,fp,propre,reverse);             //mode : 2nd tri du t3 p3 et t2 p2
        else if (arg == 12 || arg == 22 ) a = fabricationTABt2(ligne,b,a,nbligne,nbcolonne,fp,propre); 
        else if ( arg == 5 ) a = fabricationTABm(ligne,b,a,nbligne,nbcolonne,fp,propre);
        else if ( arg == 51 ) a = fabricationTABm2(ligne,b,a,nbligne,nbcolonne,fp,propre);
        else if ( arg == 4 ) a = fabricationTABw(ligne,b,a,nbligne,nbcolonne,fp,propre);
        else if (arg == 21) a = fabricationTABp1(ligne,b,a,nbligne,nbcolonne,fp,propre);
        else if (arg == 3) a = fabricationTABh(ligne,b,a,nbligne,nbcolonne,fp,propre);*/
        free(a);}
    else if (tri == 4)
        {int X_max;
        int X_min;
        int Y_max;
        int Y_min;
        char ligne[1024];   
        double b[nbcolonne];
        if ( strcmp("F",zone) == 0 )               // on entre chaque valeur de zone 
        {
            X_max = 10;
            X_min = -6;
            Y_max = 52;
            Y_min = 40;
        }
        else if ( strcmp("A",zone) == 0 )
        {
            X_max = -55;
            X_min = -78;
            Y_max = 20;
            Y_min = 8;
        }
        else if ( strcmp("G",zone) == 0 )
        {
            X_max = -50;
            X_min = -60;
            Y_max = 8;
            Y_min = 0;
        }
        else if ( strcmp("O",zone) == 0 )
        {
            X_max = 115;
            X_min = 15;
            Y_max = 10;
            Y_min = -54;
        }
        else exit (1);
        fabrication(ligne,b,nbligne,nbcolonne,fp,propre,X_max,X_min,Y_max,Y_min);}

    puts ("\n");
    fclose(propre);
    fclose(fp);
    return 0;
}