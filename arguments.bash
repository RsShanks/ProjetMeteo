#!/bin/bash

#on élimine notre fichier erreur en début de programme

if [ -e erreur.txt ]; then
    rm erreur.txt
fi 

#--help

args=("$@")
for (( k=0; k <= $#; k++ )); do
    if [ "${args[$k]}" == --help ]; then
        cat help.txt
        exit 3
    fi
done

#Protocole d'utilisation qui apparait après une erreur dans l'entrée de la commande

usage()
{
    echo "Usage : ./script_meteo [parametre] [Zone] -f [fichier.csv] -o [fichier de sortie.csv]
        --help pour voir les options
        'cat erreur.txt' pour afficher l'erreur"
    exit 10
}

#on teste si il y a des arguments

if [ $# = 0 ]; then
    echo "une option au moins doit être spécifiée." 2>&1 >> erreur.txt
    usage
fi

#on teste si il y a 2 fois les mêmes paramètres

args=("$@")
for (( i=0; i <= $#-2; i++ )); do
    for (( k=i+1; k <= $#-1; k++ )); do
        if [ "${args[$i]}" = "${args[$k]}" ]; then 
            echo "une option ne peut être mise qu'une seule fois." 2>&1 >> erreur.txt
            usage
        fi
    done
done

#initialisations des variables 

sortie=out.csv
ZONE=0

#fonction qui permet de gerer les paramètres que l'on veut en entrée

PARSED_ARGUMENTS=$(getopt -a -n parametre -o t:hp:wmFAQGSOf: -- "$@")

#si la fonction précédentes retourne autre chose que 0 alors il 

if [ $? != 0 ]; then 
    echo "Option inconnu: $1." >&2 >> erreur.txt
    usage
fi

#tant que l'on a pas fait passer tous les arguments dans le case on boucle jusqu'au '--' qui est le dernier élément

echo "les arguments sont : $PARSED_ARGUMENTS"
while getopts t:hp:wmFAQGSOf: name
do
    case "${name}" in
       t)   if [[ $OPTARG = 1 ]]; then      #on teste quel mode est choisi
                TEMPERATURE=1
            elif [[ $OPTARG = 2 ]]; then 
                TEMPERATURE=2
            elif [[ $OPTARG = 3 ]]; then 
                TEMPERATURE=3
            else 
                echo "mauvais mode activer pour la temperature">&2 >>erreur.txt
            fi ;;                                                             
       h)   ALTITUDE=1;;
       m)   HUMIDITE=1;; 
       p)   if [[ $OPTARG = 1 ]]; then 
                PRESSION=1
            elif [[ $OPTARG = 2 ]]; then 
                PRESSION=2
            elif [[ $OPTARG = 3 ]]; then 
                PRESSION=3
            else 
                echo "mauvais mode activer pour la pression">&2 >>erreur.txt
            fi;;
       w)   VENT=1;;
       F)   ZONE=$((1+$ZONE))   #la variable compte combien de zone sont dans les arguments
            zone=F;; 
       G)   ZONE=$((1+$ZONE)) 
            zone=G;;
       A)   ZONE=$((1+$ZONE))
            zone=A;;
       S)   ZONE=$((1+$ZONE))
            zone=S;;
       Q)   ZONE=$((1+$ZONE))
            zone=Q;;
       O)   ZONE=$((1+$ZONE))
            zone=O;;
       f)   if [[ "$OPTARG" != *.csv ]]; then #on regarde si on a bien un fichier .csv en entrée
                echo "mauvais format de fichier .csv requis en entrée">&2 >> erreur.txt
                usage
            fi                              
            tab=$OPTARG;;       #tab est le tableau d'entrée du programme
       --)  break;;
    esac
done

#on ne peut avoir que une seule Zone 

if [[ $ZONE -gt 1 ]]; then 
    echo "il ne peut y avoir que 1 seule zone.">&2 >> erreur.txt
    usage
fi

#test si un fichier d'entreé a bien été indiqué

if [[ $tab != *.csv ]]; then 
    echo "nécessite un fichier d'entrée">&2 >> erreur.txt
    usage
fi    

#Ce que fait le programme en fonction des arguments 

if [[ $TEMPERATURE -eq 1 ]]; then #temperature mode 1
    cut -d ";" -f1,11,12,13 $tab > $sortie  #trier en fonction du numeros de station (colonne 1)
                                    
                                    
elif [[ $TEMPERATURE -eq 2 ]]; then #temperature mode 2
    cut -d ";" -f1,2,11 $tab > $sortie    #trier en fonction de la date (colonne 2)


elif [[ $TEMPERATURE -eq 3 ]]; then #temperature mode 3
    cut -d ";" -f1,2,11 $tab > $sortie    #trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)


fi
if [[ $ALTITUDE -eq 1 ]]; then 
    cut -d ";" -f1,14 $tab > $sortie    #trier en fonction de l'altitude par ordre décroissant (colonne 14)


fi
if [[ $HUMIDITE -eq 1 ]]; then 
    cut -d ";" -f1,6 $tab > $sortie    #trier en fonction de l'humidité par ordre décroissant (colonne 6)


fi
if [[ $PRESSION -eq 1 ]]; then #pression mode 1
    cut -d ";" -f1,7 $tab > $sortie  #trier en fonction du numeros de station (colonne 1)

    
elif [[ $PRESSION -eq 2 ]]; then #pression mode 2
    cut -d ";" -f1,2,7 $tab > $sortie    #trier en fonction de la date (colonne 2)


elif [[ $PRESSION -eq 3 ]]; then #pression mode 3
    cut -d ";" -f1,2,7 $tab > $sortie    #trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)


fi
if [[ $VENT -eq 1 ]]; then 
    cut -d ";" -f1,4,5 $tab > $sortie   #trouver laxe x et y et faire une moyenne pour la direction trier en fonction de la station (colonne 1)
fi
if [[ $zone = F ]]; then 
    echo "france"
fi
if [[ $zone = A ]]; then 
    echo "Antilles"
fi
if [[ $zone = G ]]; then 
    echo "Guyane"
fi
if [[ $zone = Q ]]; then 
    echo "Antartique"
fi
if [[ $zone = S ]]; then 
    echo "SP&M"
fi
if [[ $zone = O ]]; then 
    echo "Ocean Indien"
fi


