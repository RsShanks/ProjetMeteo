#!/bin/bash

rm erreur.txt
args=("$@")
Zone=0
var=0
for (( i=0; i <= $#-1; i++ )); do
    if [ "${args[$i]}" = -p ]; then 
        echo "pression"
        var=$((1+$var))
    elif [ "${args[$i]}" = -w ]; then
        echo "vent"
        var=$((1+$var))
    elif [ "${args[$i]}" = -h ]; then
        echo "humidité"
        var=$((1+$var))
    elif [ "${args[$i]}" = -t ]; then 
        echo "température"
        var=$((1+$var))
    elif [ "${args[$i]}" = -F ]; then 
        echo "France"
        Zone=$((1+$Zone))
    elif [ "${args[$i]}" = -G ]; then 
        echo "Guyane"
        Zone=$((1+$Zone))
    elif [ "${args[$i]}" = -A ]; then 
        echo "Antilles"
        Zone=$((1+$Zone))
    elif [ "${args[$i]}" = -O ]; then 
        echo "Océan Indien"
        Zone=$((1+$Zone))
    elif [ "${args[$i]}" = -S ]; then 
        echo "Saint-Pierre et Miquelon" 
        Zone=$((1+$Zone))
    elif [ "${args[$i]}" = -Q ]; then 
        echo "Antartique"
        Zone=$((1+$Zone))
    else 
         echo "Cette argument n'existe pas : ${args[$i]}" 2>&1 >> erreur.txt  
    fi
done 
if [ "$Zone" -gt 1 ]; then 
    echo "Une seule zone est attendue. --help pour voir les zones" 2>&1 >> erreur.txt
fi
if [ "$var" = 0 ]; then 
    echo "une option au moins doit être spécifiée. --help pour voir les options" 2>&1 >> erreur.txt
fi
if [ -e erreur.txt ]; then
    cat erreur.txt
fi 