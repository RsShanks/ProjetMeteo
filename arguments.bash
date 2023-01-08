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

#initialisations des variables 

sortie=out.csv
ZONE=0
TEMPERATURE=0
PRESSION=0
VENT=0
HUMIDITE=0
ALTITUDE=0
parametre=0             #le nombre de parametre
mode_tri="AVL"
p=0
parametre1=0
temp=temp

#tant que l'on a pas fait passer tous les arguments dans le case on boucle jusqu'au '--' qui est le dernier élément

while getopts t:hp:wmFAQGSOd:f:-: name
do
    p=$((p+1))
    if [[ ${name} = "-" ]]      #on dit que - est une option qui a pour parametre avl
    then
        case "${OPTARG%%=*}" in
        avl );;
        abr )   mode_tri="ABR"
        ;;
        tab )   mode_tri="TAB"
        ;;
        * )
            echo "option longue n'existe pas --${OPTARG%%=*}">&2 >> erreur.txt
            usage
        ;;
        esac
    else 
        case "${name}" in
        t)  
            if [[ $OPTARG = 1 ]]; then      #on teste quel mode est choisi
                TEMPERATURE=1
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 2 ]]; then 
                TEMPERATURE=2
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 3 ]]; then 
                TEMPERATURE=3
                parametre=$((1+$parametre))
            else 
                    echo "mauvais mode activer pour la temperature">&2 >> erreur.txt
            fi ;;                                                        
        h)  parametre=$((1+$parametre))
            ALTITUDE=1;;
        m)  parametre=$((1+$parametre))
            HUMIDITE=1;; 
        p)  if [[ $OPTARG = 1 ]]; then 
                PRESSION=1
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 2 ]]; then 
                PRESSION=2
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 3 ]]; then 
                PRESSION=3
                parametre=$((1+$parametre))
            else 
                echo "mauvais mode activer pour la pression">&2 >>erreur.txt
            fi;;
        w)   parametre=$((1+$parametre))
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
        d)  date = $(cat $OPTARG > temp.csv | grep -E "[2012-2022]\-[1-12]\-[1-31]")
            if [ ! date ]; then 
                echo "erreur pas bon format : YYYY-MM-JJ "
            fi
            echo $OPTARG
            min=$OPTARG
            shift $(($OPTIND-1))
            max=0
            ;;
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

#Choix des colonnes en fonction des arguments 

    if [ $TEMPERATURE -eq 1 ]; then                                                             #temperature mode 1                                                      
        awk -F';' 'BEGIN {OFS=";"} { print $1,$11,$12,$13,$10 }' < $tab > temp$parametre.csv
        parametre=$(($parametre-1))
        parametre1=$((1+$parametre1))                                                           #A trier en fonction du numeros de station (colonne 1)                                                                 
    elif [ $TEMPERATURE -eq 2 ]; then                                                                      #temperature mode 2            
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$11,$10 }' < $tab > temp$parametre.csv      #A trier en fonction de la date (colonne 2)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    elif [ $TEMPERATURE -eq 3 ]; then                                                          #temperature mode 3
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$11,$10 }' < $tab > temp$parametre.csv      #A trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    fi
    if [ $ALTITUDE -eq 1 ]; then 
        awk -F';' 'BEGIN {OFS=";"} { print $14,$1,$10 }' < $tab > temp$parametre.csv         #A trier en fonction de l'altitude par ordre décroissant (colonne 13)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    fi
    if [ $HUMIDITE -eq 1 ]; then 
        awk -F';' 'BEGIN {OFS=";"} { print $6,$1,$10 }' < $tab > temp$parametre.csv           #A trier en fonction de l'humidité par ordre décroissant (colonne 6)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    fi
    if [ $PRESSION -eq 1 ]; then                                                                #pression mode 1
        cut -d ";" -f1,7,10 $tab > temp$parametre.csv                                             #A trier en fonction du numeros de station (colonne 1)  
        parametre=$(($parametre-1))
        parametre1=$(( 1 + $parametre1)) 
    elif [ $PRESSION -eq 2 ]; then                                                              #pression mode 2
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$7,10 }' < $tab > temp$parametre.csv            #A trier en fonction de la date (colonne 2)
        parametre=$(($parametre-1))
        parametre1=$(( 1 + $parametre1))
    elif [ $PRESSION -eq 3 ]; then                                                              #pression mode 3
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$7,10 }' < $tab > temp$parametre.csv                                           #A trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)
        parametre=$(($parametre-1))
        parametre1=$(( 1 + $parametre1))
    fi
    if [ $VENT -eq 1 ]; then 
        cut -d ";" -f10,1,4,5 $tab > temp$parametre.csv                                          #trouver laxe x et y et faire une moyenne pour la direction trier en fonction de la station (colonne 1)
    fi

#on teste si une variable zone est activer ( cela réduit la taille du fichier à trier ensuite )
if [[ $ZONE == 1 ]]; then
    fichier=$( ls | grep temp )
    for f in $fichier ; do
        if [[ $zone = F ]]; then          ## si option pour France + Corse (F)
            echo "traitement de la zone FRANCE et CORSE :"
            grep -E "[42-51].*,[-7-10]." temp$parametre1.csv > REGION_$parametre1.csv
            rm temp$parametre1.csv
            parametre1=$(($parametre1-1))
        elif [[ $zone = A ]]; then        ## si option pour Antilles (A)
            echo "traitement de la zone ANTILLES : "
            grep -E ";97[0-2][0-9][0-9]$|97[7-8][0-9][0-9]$" temp$parametre1.csv > REGION_$parametre1.csv
            rm temp$parametre1.csv
            parametre1=$(($parametre1-1))
        elif [[ $zone = G ]]; then        ## si option pour guyane (G)
            echo "traitement de la zone GUYANE : "
            grep -E ";973[00-99]$" temp$parametre1.csv > REGION_$parametre1.csv
            rm temp$parametre1.csv
            parametre1=$(($parametre1-1))
        elif [[ $zone = S ]]; then        ## si option pour Saint-Pierre et Miquelon (S)
            echo "traitement de la zone SAINT-PIERRE ET MIQUELON :"
            grep -E "46.766333,-56.179167" temp$parametre1.csv > REGION_$parametre1.csv
            rm temp$parametre1.csv
            parametre1=$(($parametre1-1))
        elif [[ $zone = O ]]; then        ## si option pour Océan indien (O)
            echo "traitement de la zone OCEAN INDIEN : "
            grep  temp$parametre1.csv > REGION_$parametre1.csv
            rm temp$parametre1.csv
            parametre1=$(($parametre1-1))
        else                              ## si option pour Antartique (Q)
            echo "traitement de la zone ANTARTIQUE ; "
            grep "\-66.*,140.*" temp$parametre1.csv > REGION_$parametre1.csv
            rm temp$parametre1.csv
            parametre1=$(($parametre1-1))
        fi
    done
else 
    fichier=$( ls | grep temp )
    for f in $fichier ; do
        mv $f REGION_$parametre1.csv
        parametre1=$(($parametre1-1))
    done
fi

#tri de fichier 

fichier=$( ls | grep REGION )
for f in $fichier ; do                              #creer un fichier propre
    parametre1=$((1+$parametre1))
    #entrer des espaces dans le fichier csv pour que le c comprenne les espaces

    sed -i -e "s/;;/; ;/g" $f # ";;;" => "; ;;"
    sed -i -e "s/;;/; ;/g" $f # "; ;;" => "; ; ;"
    sed -i -e "s/;\$/; /g" $f # ";" => "; "   fin de ligne 
    sed -i -e "s/^;/ ;/g" $f # ";" => " ;"   debut de ligne

    #mettre que des chiffres dans la colonne dates et separé les heures et la date

    sed -i -e "s/://g" $f
    sed -i -e "s/+//g" $f
    sed -i -e "s/T//g" $f

    #transformer la "," des coordonnées en 2 colonnes

    sed -i -e "s/,/;/g" $f

    #enlever la premiere ligne
    tail +2 $f > TRI_$parametre1.csv
    #supprimer l'ancien fichier
    rm $f
    if [[ $TEMPERATURE == 2 || $PRESSION == 2 || $TEMPERATURE == 3 || $PRESSION == 3 ]];then 
        cut -d";" -f1 TRI_$parametre1.csv > tmp.csv
        sed -i -e "s/-//g" tmp.csv
        paste -d ";" TRI_$parametre1.csv tmp.csv > output.csv
        awk -F';' 'BEGIN {OFS=";"} { print $6,$2,$3,$4,$5 }' output.csv > TRI_$parametre1.csv
        rm output.csv
        rm tmp.csv
    fi
done

#Compilation 

gcc $mode_tri.c -o $mode_tri 2> erreur.txt
if [[ $? == 0 ]];then
    rm erreur.txt
else 
    echo "erreur lors de la compilation ">&2 >> erreur.txt
    usage
fi

#execution du programme

fichier=$( ls | grep TRI )
for fic in $fichier ; do

#initialisations de nouvelles variables 

    nblignes=$(cat $fic | wc -l)
    nbcolonnes=$(awk -F';' '(NR==1){print NF;}' $fic)

    touch OK_$fic

    ./$mode_tri -f $fic -o OK_$fic -l $nblignes -c $nbcolonnes

    if [[ $? == 1 ]];then
        echo "Mauvaise option activer pour le tri">&2 >> erreur.txt
    elif [[ $? == 2 ]];then
        echo "erreur avec le fichier de données d’entrée">&2 >> erreur.txt
    elif [[ $? == 3 ]];then
        echo "erreur avec le fichier de données de sortie">&2 >> erreur.txt
    elif [[ $? -ge 4 ]];then
        echo "erreur dans le programme de tri">&2 >> erreur.txt
    fi

    if [[ $TEMPERATURE == 2 || $PRESSION == 2 || $TEMPERATURE == 3 || $PRESSION == 3 ]];then 
        echo "la"
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$3,$4,$5 }' OK_$fic > tmp.csv
        ./$mode_tri -f tmp.csv -o OK_$fic -l $nblignes -c $nbcolonnes
        rm tmp.csv
    fi
    if [[ $? == 1 ]];then
        echo "Mauvaise option activer pour le tri">&2 >> erreur.txt
    elif [[ $? == 2 ]];then
        echo "erreur avec le fichier de données d’entrée">&2 >> erreur.txt
    elif [[ $? == 3 ]];then
        echo "erreur avec le fichier de données de sortie">&2 >> erreur.txt
    elif [[ $? -ge 4 ]];then
        echo "erreur dans le programme de tri">&2 >> erreur.txt
    fi
done