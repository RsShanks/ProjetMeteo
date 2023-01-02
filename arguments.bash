#!/bin/bash

#on elimine les fichiers residuels du dernier lancement

#rm Paramètre/*

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
TEMPERATURE=0
PRESSION=0
VENT=0
HUMIDITE=0
ALTITUDE=0
parametre=0             #le nombre de parametre
mode_tri="avl"
p=0

#tant que l'on a pas fait passer tous les arguments dans le case on boucle jusqu'au '--' qui est le dernier élément

while getopts t:hp:wmFAQGSOf:-: name
do
    p=$((p+1))
    if [[ ${name} = "-" ]]      #on dit que - est une option qui a pour parametre avl
    then
        case "${OPTARG%%=*}" in
        avl );;
        abr )   mode_tri="abr"
        ;;
        tab )   mode_tri="tab"
        ;;
        * )
            echo "option longue n'existe pas --${OPTARG%%=*}">&2 >> erreur.txt
            usage
        ;;
        esac
    else 
        case "${name}" in
        t)  parametre=1
            if [[ $TEMPERATURE != 0 ]];then 
                echo "il ne peut y avoir qu'un mode de temperature à la fois">&2 >> erreur.txt
                usage
            elif [[ $OPTARG = 1 ]]; then      #on teste quel mode est choisi
                TEMPERATURE=1
            elif [[ $OPTARG = 2 ]]; then 
                TEMPERATURE=2
            elif [[ $OPTARG = 3 ]]; then 
                TEMPERATURE=3
            else 
                    echo "mauvais mode activer pour la temperature">&2 >> erreur.txt
            fi ;;                                                        
        h)  parametre=1
            ALTITUDE=1;;
        m)  parametre=1
            HUMIDITE=1;; 
        p)  parametre=1
            if [[ $PRESSION != 0 ]];then 
                echo "il ne peut y avoir qu'un mode de temperature à la fois">&2 >> erreur.txt
                usage
            elif [[ $OPTARG = 1 ]]; then 
                PRESSION=1
            elif [[ $OPTARG = 2 ]]; then 
                PRESSION=2
            elif [[ $OPTARG = 3 ]]; then 
                PRESSION=3
            else 
                echo "mauvais mode activer pour la pression">&2 >>erreur.txt
            fi;;
        w)   parametre=1
                VENT=1;;
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
        * )     echo "option n'existe pas ${args[$p]}">&2 >> erreur.txt
                usage
            ;;
        --)  break;;
        esac
    fi
done

#il doit y avoir au moins 1 parametre

if [[ $parametre = 0 ]]; then 
    echo "un paramètre au moins doit ếtre spécifié">&2 >> erreur.txt
    usage
fi

#on ne peut avoir que une seule Zone 

if [[ $ZONE -gt 1 ]]; then 
    echo "il ne peut y avoir que 1 seule zone.">&2 >> erreur.txt
    usage
fi            

echo "préparation des fichiers"

#creation d'un fichier temporaire

temp1=temp1.csv
temp=temp.csv

#Ce que fait le programme en fonction des arguments 

if [ $TEMPERATURE -eq 1 ]; then #temperature mode 1
    cut -d ";" -f1,11,12,13,15 $tab > $temp1 #A trier en fonction du numeros de station (colonne 1)                                                                 
elif [ $TEMPERATURE -eq 2 ]; then #temperature mode 2
    cut -d ";" -f2,1,11,15 $tab > $temp1    #A trier en fonction de la date (colonne 2)
elif [ $TEMPERATURE -eq 3 ]; then #temperature mode 3
    cut -d ";" -f2,1,11,15 $tab > $temp1    #A trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)

    cut -d ";" -f1,2,11,15 $tab > $temp1
fi
if [ $ALTITUDE -eq 1 ]; then 
    cut -d ";" -f13,1,15 $tab > $temp1    #A trier en fonction de l'altitude par ordre décroissant (colonne 14)
fi
if [ $HUMIDITE -eq 1 ]; then 
    cut -d ";" -f6,1,15 $tab > $temp1    #A trier en fonction de l'humidité par ordre décroissant (colonne 6)
fi
if [ $PRESSION -eq 1 ]; then #pression mode 1
    cut -d ";" -f1,7,15 $tab > $temp1  #A trier en fonction du numeros de station (colonne 1)  
elif [ $PRESSION -eq 2 ]; then #pression mode 2
    cut -d ";" -f15,2,1,7 $tab > $temp1    #A trier en fonction de la date (colonne 2)
elif [ $PRESSION -eq 3 ]; then #pression mode 3
    cut -d ";" -f15,2,1,7 $tab > $temp1    #A trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)
    cut -d ";" -f15,1,2,7 $tab > $temp1 
fi
if [ $VENT -eq 1 ]; then 
    cut -d ";" -f15,1,4,5 $tab > $temp1   #trouver laxe x et y et faire une moyenne pour la direction trier en fonction de la station (colonne 1)
fi

#creer un fichier propre

tail +2 $temp1 > $temp
rm $temp1
    #entrer des espaces dans le fichier csv pour que le c comprenne les espaces

    sed -i -e "s/;;/; ;/g" $temp # ";;;" => "; ;;"
    sed -i -e "s/;;/; ;/g" $temp # ";;;" => "; ; ;"
    sed -i -e "s/*;\n/; \n/g" $temp # "*;" => "*; "

    #mettre que des chiffres dans la colonne dates 

    sed -i -e "s/-//g" $temp
    sed -i -e "s/://g" $temp
    sed -i -e "s/+//g" $temp
    sed -i -e "s/T//g" $temp

    #Retirer les a et les b du code postal

    sed -i -e "s/a//g" $temp
    sed -i -e "s/b//g" $temp

#initialisations de nouvelle variable 

nblignes=$(cat $temp | wc -l)
nbcolonnes=$(awk -F';' '(NR==1){print NF;}' $temp)


#on teste si une variable zone est activer ( cela réduit la taille du fichier à trier ensuite )

if [[ $ZONE == 1 ]]; then
    if [[ $zone = F ]]; then        ## si option pour France + Corse (F)
        echo "traitement de la zone FRANCE et CORSE :"
        ./tri_lignes_ZONE -f $temp -o $sortie $nblignes $nbcolonnes F
    elif [[ $zone = A ]]; then        ## si option pour Antilles (A)
        ./tri_lignes_ZONE -f $temp -o $sortie $nblignes $nbcolonnes A
    elif [[ $zone = G ]]; then        ## si option pour guyane (G)
        ./tri_lignes_ZONE -f $temp -o $sortie $nblignes $nbcolonnes G
    elif [[ $zone = S ]]; then        ## si option pour Saint-Pierre et Miquelon (S)
        ./tri_lignes_ZONE -f $temp -o $sortie $nblignes $nbcolonnes S
    elif [[ $zone = O ]]; then        ## si option pour Océan indien (O)
        ./tri_lignes_ZONE -f $temp -o $sortie $nblignes $nbcolonnes O
    else                              ## si option pour Antartique (Q)
        ./tri_lignes_ZONE -f $temp -o $sortie $nblignes $nbcolonnes Q
    fi
    rm $temp
else 
    sortie=$temp
fi

