#!/bin/bash

#on elimine les fichiers residuels du dernier lancement

if [ -d resultat_tri ];then 
    fichier=$(ls resultat_tri| grep OK)
    for f in $fichier;do
        rm resultat_tri/$f
    done
fi

if [ -d graphiqueGnuplot ];then 
    fichier=$(ls graphiqueGnuplot | grep .jpeg)
    for f in $fichier;do
        rm graphiqueGnuplot/$f
    done
fi

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
    echo "Usage : ./Meteo [parametre] [Zone] -f [fichier.csv]
--help pour voir les options
'cat erreur.txt' pour afficher l'erreur"
    exit 10
}

Compilation()
{
        if [ ! -f Fichier_C/Meteo ];then
            make all >&2 >> erreur.txt
            if [[ $? == 0 ]];then
                rm erreur.txt
            else 
                echo "erreur lors de la compilation ">&2 >> erreur.txt
                mv erreur.txt ../
                usage
            fi
        fi
}

traitement_erreur_C()
{
    if [[ $1 == 1 ]];then
        echo "Mauvaise option activer pour le tri">&2 >> erreur.txt
        usage
    elif [[ $1 == 2 ]];then
        echo "erreur avec le fichier de données d’entrée">&2 >> erreur.txt
        usage
    elif [[ $1 == 3 ]];then
        echo "erreur avec le fichier de données de sortie">&2 >> erreur.txt
        usage
    elif [[ $1 -ge 4 ]];then
        echo "erreur dans le programme de tri">&2 >> erreur.txt
        usage
    fi
}
#on teste si il y a des arguments

if [ $# = 0 ]; then
    echo "une option au moins doit être spécifiée." 2>&1 >> erreur.txt
    usage
fi

#initialisations des variables 

ZONE=0
TEMPERATURE=0
PRESSION=0
VENT=0
HUMIDITE=0
ALTITUDE=0
parametre=0             #le nombre de parametre
mode_tri=1
p=0
parametre1=0
temp=temp
tableau_arg=()
reverse=0
#tant que l'on a pas fait passer tous les arguments dans le case on boucle jusqu'au '--' qui est le dernier élément

while getopts t:hp:wmFAQGSOf:-:r name
do
    p=$((p+1))
    if [[ ${name} = "-" ]]      #on dit que - est une option qui a pour parametre avl
    then
        case "${OPTARG%%=*}" in
        avl );;
        abr )   mode_tri=2
        ;;
        tab )   echo "Les tris par tableau n'ont pas été implémenté, pour plus d'information aller voir le rapport de projet."
                exit 0
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
                tableau_arg[$parametre]="t1"
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 2 ]]; then 
                TEMPERATURE=2
                tableau_arg[$parametre]="t2"
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 3 ]]; then 
                TEMPERATURE=3
                tableau_arg[$parametre]="t3"
                parametre=$((1+$parametre))
            else 
                    echo "mauvais mode activer pour la temperature">&2 >> erreur.txt
            fi ;;                                                        
        h)  tableau_arg[$parametre]="h"
            parametre=$((1+$parametre))
            ALTITUDE=1 ;;
        m)  tableau_arg[$parametre]="m0"
            parametre=$((1+$parametre))
            HUMIDITE=1 ;; 
        p)  if [[ $OPTARG = 1 ]]; then 
                PRESSION=1
                tableau_arg[$parametre]="p1"
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 2 ]]; then 
                PRESSION=2
                tableau_arg[$parametre]="p2"
                parametre=$((1+$parametre))
            elif [[ $OPTARG = 3 ]]; then 
                PRESSION=3
                tableau_arg[$parametre]="p3"
                parametre=$((1+$parametre))
            else 
                echo "mauvais mode activer pour la pression">&2 >>erreur.txt
            fi ;;
        w)  tableau_arg[$parametre]="w" 
            parametre=$((1+$parametre))
                VENT=1 ;;
        F)   ZONE=$((1+$ZONE))   #la variable compte combien de zone sont dans les arguments
                zone=F ;;
        G)   ZONE=$((1+$ZONE)) 
                zone=G ;;
        A)   ZONE=$((1+$ZONE))
                zone=A ;;
        S)   ZONE=$((1+$ZONE))
                zone=S ;;
        Q)   ZONE=$((1+$ZONE))
                zone=Q ;;
        O)   ZONE=$((1+$ZONE))
                zone=O ;;
        f)   if [[ "$OPTARG" != *.csv ]]; then #on regarde si on a bien un fichier .csv en entrée
                    echo "mauvais format de fichier .csv requis en entrée">&2 >> erreur.txt
                    usage
             elif [[ ! -f $OPTARG ]]; then #on regarde si on a un fichier .csv qui existe
                    echo "fichier.csv introuvable">&2 >> erreur.txt
                    usage
                fi                              
                tab=$OPTARG ;;       #tab est le tableau d'entrée du programme
        r)  reverse=1 ;;
        * )     echo "option n'existe pas ${args[$p]} ">&2 >> erreur.txt
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
while [[ $parametre -ne 0 ]];do
    if [[ ${tableau_arg[$parametre1]} == t1 ]]; then                                                             #temperature mode 1                                                      
        awk -F';' 'BEGIN {OFS=";"} { print $1,$11,$12,$13,$10 }' < $tab > temp${tableau_arg[$parametre1]}.csv
        parametre=$(($parametre-1))
        parametre1=$((1+$parametre1))                                                           #A trier en fonction du numeros de station (colonne 1)                                                                 
    elif [[ ${tableau_arg[$parametre1]} == t2 ]]; then                                                                      #temperature mode 2            
        awk -F';' 'BEGIN {OFS=";"} { print $2,$11,$10 }' < $tab > temp${tableau_arg[$parametre1]}.csv      #A trier en fonction de la date (colonne 2)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    elif [[ ${tableau_arg[$parametre1]} == t3 ]]; then                                                          #temperature mode 3
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$11,$10 }' < $tab > temp${tableau_arg[$parametre1]}.csv      #A trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    fi
    if [[ ${tableau_arg[$parametre1]} == h ]]; then 
        awk -F';' 'BEGIN {OFS=";"} { print $14,$1,$10 }' < $tab > temp${tableau_arg[$parametre1]}.csv         #A trier en fonction de l'altitude par ordre décroissant (colonne 13)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    fi
    if [[ ${tableau_arg[$parametre1]} == m0 ]]; then 
        awk -F';' 'BEGIN {OFS=";"} { print $1,$6,$10 }' < $tab > temp${tableau_arg[$parametre1]}.csv           #A trier en fonction de l'humidité par ordre décroissant (colonne 6)
        parametre=$(($parametre-1))
        parametre1=$(($parametre1+1))
    fi
    if [[ ${tableau_arg[$parametre1]} == p1 ]]; then                                                                #pression mode 1
        cut -d ";" -f1,7,10 $tab > temp${tableau_arg[$parametre1]}.csv                                             #A trier en fonction du numeros de station (colonne 1)  
        parametre=$(($parametre-1))
        parametre1=$(( 1 + $parametre1)) 
    elif [[ ${tableau_arg[$parametre1]} == p2 ]]; then                                                              #pression mode 2
        awk -F';' 'BEGIN {OFS=";"} { print $2,$7,$10 }' < $tab > temp${tableau_arg[$parametre1]}.csv            #A trier en fonction de la date (colonne 2)
        parametre=$(($parametre-1))
        parametre1=$(( 1 + $parametre1))
    elif [[ ${tableau_arg[$parametre1]} == p3 ]]; then                                                              #pression mode 3
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$7,$10 }' < $tab > temp${tableau_arg[$parametre1]}.csv                                           #A trier en fonction de la date (colonne 2) puis en fonction du numéros de la station (colonne 1)
        parametre=$(($parametre-1))
        parametre1=$(( 1 + $parametre1))
    fi
    if [[ ${tableau_arg[$parametre1]} == w ]]; then 
        cut -d ";" -f1,4,5,10 $tab > temp${tableau_arg[$parametre1]}.csv                                          #trouver laxe x et y et faire une moyenne pour la direction trier en fonction de la station (colonne 1)
        parametre=$(($parametre-1))
        parametre1=$(( 1 + $parametre1))
    fi
done
#tri de fichier 

fichier=$( ls | grep temp )
for f in $fichier ; do  
                            #creer un fichier propre

    #mettre que des chiffres dans la colonne dates et separé les heures et la date

    sed -i -e "s/://g" $f
    sed -i -e "s/+//g" $f
    sed -i -e "s/T//g" $f

    #transformer la "," des coordonnées en 2 colonnes
   
    sed -i -e "s/,/;/g" $f           
           
    #enlever la premiere ligne
    tail +2 $f > TRI_$parametre1.csv 
    cat TRI_$parametre1.csv > $f
    rm TRI_$parametre1.csv

    if [[ "tempt3.csv" == $f || "tempp3.csv" == $f  ]];then #placer la colonne date qui possede uniquement des chiffres
        cut -d";" -f1 $f > tmp.csv
        sed -i -e "s/-//g" tmp.csv
        paste -d ";" $f tmp.csv > output.csv
        awk -F';' 'BEGIN {OFS=";"} { print $2,$6,$3,$4,$5 }' output.csv > $f
        rm output.csv
        rm tmp.csv
    elif [[ "tempt2.csv" == $f || "tempp2.csv" == $f ]];then #placer la colonne date qui possede uniquement des chiffres
        cut -d";" -f1 $f > tmp.csv
        sed -i -e "s/-//g" tmp.csv
        paste -d ";" $f tmp.csv > output.csv
        awk -F';' 'BEGIN {OFS=";"} { print $5,$2,$3,$4 }' output.csv > $f
        rm output.csv
        rm tmp.csv
    fi
done

#on teste si une variable zone est activer ( cela réduit la taille du fichier à trier ensuite )

if [[ $ZONE == 1 ]]; then
    Compilation
    parametre=0
    for f in $fichier ; do
        
        nblignes=$(cat temp${tableau_arg[$parametre]}.csv | wc -l)
        nbcolonnes=$(awk -F';' '(NR==1){print NF;}' temp${tableau_arg[$parametre]}.csv)
        if [[ $zone = F ]]; then          ## si option pour France + Corse (F)
            echo "traitement de la zone FRANCE et CORSE pour ${tableau_arg[$parametre]} :"
            ./Fichier_C/Meteo -f temp${tableau_arg[$parametre]}.csv -o REGION_${tableau_arg[$parametre]}.csv -l $nblignes -c $nbcolonnes -z F -k 4
            traitement_erreur_C "$?"
            rm temp${tableau_arg[$parametre]}.csv
            parametre=$(($parametre+1))
        
        elif [[ $zone = A ]]; then        ## si option pour Antilles (A)
            echo "traitement de la zone ANTILLES pour ${tableau_arg[$parametre]} :"
            ./Fichier_C/Meteo -f temp${tableau_arg[$parametre]}.csv -o REGION_${tableau_arg[$parametre]}.csv -l $nblignes -c $nbcolonnes -z A -k 4
            traitement_erreur_C "$?"
            rm temp${tableau_arg[$parametre]}.csv
            parametre=$(($parametre+1))
      
        elif [[ $zone = G ]]; then        ## si option pour guyane (G)
            echo "traitement de la zone GUYANE pour ${tableau_arg[$parametre]} :"
            ./Fichier_C/Meteo -f $f -o REGION_${tableau_arg[$parametre]}.csv -l $nblignes -c $nbcolonnes -z G -k 4
            traitement_erreur_C "$?"
            rm temp${tableau_arg[$parametre]}.csv
            parametre=$(($parametre+1))
       
        elif [[ $zone = S ]]; then        ## si option pour Saint-Pierre et Miquelon (S)
            echo "traitement de la zone SAINT-PIERRE ET MIQUELON pour ${tableau_arg[$parametre]} :"
            grep -E "46.766333" temp${tableau_arg[$parametre]}.csv > REGION_${tableau_arg[$parametre]}.csv
            rm temp${tableau_arg[$parametre]}.csv
            parametre=$(($parametre+1))
       
        elif [[ $zone = O ]]; then        ## si option pour Océan indien (O)
            echo "traitement de la zone OCEAN INDIEN pour ${tableau_arg[$parametre]} :"
            ./Fichier_C/Meteo -f temp${tableau_arg[$parametre]}.csv -o REGION_${tableau_arg[$parametre]}.csv -l $nblignes -c $nbcolonnes -z O -k 4 
            traitement_erreur_C "$?"
            rm temp${tableau_arg[$parametre]}.csv
            parametre=$(($parametre+1))
      
        else                              ## si option pour Antartique (Q)
            echo "traitement de la zone ANTARTIQUE pour ${tableau_arg[$parametre]} :"
            grep "\-66.*;140.*" temp${tableau_arg[$parametre]}.csv > REGION_${tableau_arg[$parametre]}.csv
            rm temp${tableau_arg[$parametre]}.csv
            parametre=$(($parametre+1))
        fi
    done
else 
    fichier=$( ls | grep temp )
    for f in $fichier ; do
        mv temp${tableau_arg[$parametre]}.csv REGION_${tableau_arg[$parametre]}.csv
        parametre=$(($parametre+1))
    done
fi

#Compilation 

Compilation

#execution du programme
i=0
fichier=$( ls | grep REGION )
for fic in $fichier ; do
    echo Tri ${tableau_arg[$i]} :
    nblignes=$(cat REGION_${tableau_arg[$i]}.csv | wc -l)                   
    nbcolonnes=$(awk -F';' '(NR==1){print NF;}' REGION_${tableau_arg[$i]}.csv)
    if [ ! -d resultat_tri ];then
        mkdir resultat_tri
    fi
    ./Fichier_C/Meteo -f REGION_${tableau_arg[$i]}.csv -o resultat_tri/OK_tri_${tableau_arg[$i]}.csv -l $nblignes -c $nbcolonnes -${tableau_arg[$i]} -k $mode_tri -r $reverse
    traitement_erreur_C "$?"
    rm REGION_${tableau_arg[$i]}.csv
    nblignes=$(cat resultat_tri/OK_tri_${tableau_arg[$i]}.csv | wc -l)
    nbcolonnes=$(awk -F';' '(NR==1){print NF;}' resultat_tri/OK_tri_${tableau_arg[$i]}.csv)
    if [[  ${tableau_arg[$i]} == t3 || ${tableau_arg[$i]} == p3 ]];then     #trier une 2ème fois le fichier mais selon une autre colonne
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$3,$4,$5 }' resultat_tri/OK_tri_${tableau_arg[$i]}.csv > tmp.csv
        ./Fichier_C/Meteo -f tmp.csv -o resultat_tri/OK_tri_${tableau_arg[$i]}.csv -l $nblignes -c $nbcolonnes -t0 -k $mode_tri -r$reverse
        traitement_erreur_C "$?"
        rm tmp.csv
    elif [[  ${tableau_arg[$i]} == m0 ]];then                               #trier une 2ème fois le fichier mais selon une autre colonne
        awk -F';' 'BEGIN {OFS=";"} { print $2,$1,$3,$4,$5 }' resultat_tri/OK_tri_${tableau_arg[$i]}.csv > tmp.csv
        rm resultat_tri/OK_tri_${tableau_arg[$i]}.csv
        ./Fichier_C/Meteo -f tmp.csv -o resultat_tri/OK_tri_m.csv -l $nblignes -c $nbcolonnes -m1 -k $mode_tri -r$reverse
        traitement_erreur_C "$?"
        rm tmp.csv
    fi
    i=$(($i+1))
done

for ((p=0; p<$#; p++)); do
    if [ ! -d "graphiqueGnuplot/" ]
        then
            mkdir graphiqueGnuplot
    fi
    if [[ ${tableau_arg[$p]} == t1 ]]
        then
        gnuplot << EOF
    set terminal jpeg size 800,600
    set output 'graphiqueGnuplot/$zone_${tableau_arg[$p]}_Graphique.jpeg'
    set style data lines
    set title "temperature en fonctions des numéros de stations"
    set datafile separator ";"
    set xlabel 'Stations'
    set ylabel 'Temperature'
    set xrange [ * : * ]
    set xtics rotate by 45 right
    set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
    NO_ANIMATION = 1
    Shadecolor = "#80E0A080"
    plot "resultat_tri/OK_tri_${tableau_arg[$p]}.csv" u 0:3:4:xticlabels(1) with filledcurve fc rgb Shadecolor title "temperature min et max",'' using 0:2 smooth mcspline lw 2 title "temperature moyenne"
    quit
EOF
    fi
    if [[ ${tableau_arg[$p]} == p1 ]]
        then
        gnuplot << EOF
    set terminal jpeg size 800,600
    set output 'graphiqueGnuplot/{$zone}_${tableau_arg[$p]}_Graphique.jpeg'
    set style data lines
    set title "pression en fonctions des numéros de stations"
    set datafile separator ";"
    set xlabel 'Stations'
    set ylabel 'Pression'
    set xrange [ * : * ]
    set xtics rotate by 45 right
    set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
    NO_ANIMATION = 1
    Shadecolor = "#80E0A080"
    plot "resultat_tri/OK_tri_${tableau_arg[$p]}.csv" u 0:3:4:xticlabels(1) with filledcurve fc rgb Shadecolor title "temperature min et max",'' using 0:2 smooth mcspline lw 2 title "temperature moyenne"
    quit
EOF
    fi
    if [[ ${tableau_arg[$p]} == t2 ]]
        then
        gnuplot << EOF
    set terminal jpeg size 800,600
    set output 'graphiqueGnuplot/{$zone}_${tableau_arg[$p]}_Graphique.jpeg'
    set style data lines
    set title "moyenne temperature par jour en année/mois/jours"
    set datafile separator ";"
    set xlabel 'jours'
    set ylabel 'temperature'
    set xrange [ * : * ]
    set xtics rotate by 45 right
    NO_ANIMATION = 1
    plot "resultat_tri/OK_tri_${tableau_arg[$p]}.csv" u 1:2
    quit
EOF
    
    fi
    if [[ ${tableau_arg[$p]} == p2 ]]
        then
        gnuplot<<EOF
    set terminal jpeg size 800,600
    set output 'graphiqueGnuplot/{$zone}_${tableau_arg[$p]}_Graphique.jpeg'
    set style data lines
    set title "moyenne pression par jour en année/mois/jours"
    set datafile separator ";"
    set xlabel 'jours'
    set ylabel 'pression'
    NO_ANIMATION = 1
    plot "resultat_tri/OK_tri_${tableau_arg[$p]}.csv" using 0:2:xticlabels(1)
    quit
EOF
    fi
    
    if [[ ${tableau_arg[$p]} == h ]]
        then
        gnuplot << EOF
        reset
        set terminal jpeg size 800,600
        set xyplane relative 0
        set title "altitude des stations"
        set output 'graphiqueGnuplot/{$zone}_${tableau_arg[$p]}_Graphique.jpeg'
        set xlabel "Longitude"
        set ylabel "Latitude"
        set zlabel "Altitude"
        set xtics
        set ytics  
        set datafile separator ";"
        set pm3d map interpolate 4,4 flush begin nohidden3d
        set dgrid3d 50,50
        set autoscale noextend
        set zrange[ * : * ]
        set palette rgbformulae 33, 13, 10
        set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
        NO_ANIMATION = 1
        splot "resultat_tri/OK_tri_${tableau_arg[$p]}.csv" u 3:4:1 with pm3d
        reset
EOF
        fi
    if [[ ${tableau_arg[$p]} == w ]]
        then
        gnuplot<<EOF
        reset
        set terminal jpeg size 800,600
        set xyplane relative 0
        set title "vecteur"
        set output 'graphiqueGnuplot/{$zone}_${tableau_arg[$p]}_Graphique.jpeg'
        set xlabel "Longitude"
        set ylabel "Latitude"
        set datafile separator ";"
        set pm3d map interpolate 4,4 flush begin nohidden3d
        set xrange [ -180 : 180 ]
        set yrange [ -90 : 90 ]
        NO_ANIMATION = 1
        plot "resultat_tri/OK_tri_${tableau_arg[$p]}.csv" u 4:5:3:(0.2*sin(2)) with vectors filled head lw 3
        reset
EOF
        fi

    if [[ ${tableau_arg[$p]} == m0 ]]
        then
        gnuplot << EOF
        reset
        set terminal jpeg size 800,600
        set xyplane relative 0
        set title "humidité des stations"
        set output 'graphiqueGnuplot/{$zone}_m_Graphique.jpeg'
        set xlabel "Longitude"
        set ylabel "Latitude"
        set zlabel "humidité"
        set xtics
        set ytics  
        set datafile separator ";"
        set pm3d map interpolate 4,4 flush begin nohidden3d
        set dgrid3d 50,50
        set autoscale noextend
        set zrange[ * : * ]
        set palette rgbformulae 10, 13, 33
        set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
        NO_ANIMATION = 1
        splot "resultat_tri/OK_tri_m.csv" u 3:4:1 with pm3d
        reset
EOF
        fi
done

exit 0