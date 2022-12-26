#!/bin/bash

## NOTES AVANT DE LIRE : peut etre qu'il faut rajouter des $ avant les parentheses du if, je sais pas


read nblignes < <(wc -l data.csv)
nblignes=$(echo "$nblignes" | cut -d ' ' -f1)
echo $nblignes

## si option pour O
for i in {2..$nblignes}
do
    if [(head -n $i data.csv | tail -1 | cut -d ';' -f15) == 98415]
    then
        head -n i data.csv | tail -1 >> fichier.txt
    fi
done

## si option pour Q
for i in {2..$nblignes}
do
    if [(head -n $i data.csv | tail -1 | cut -d ';' -f15) == 98412]
    then
        head -n i data.csv | tail -1 >> fichier.txt
    fi
done

## si option pour France + Corse
for i in {2..$nblignes}
do
    if [(head -n $i data.csv | tail -1 | cut -d ';' -f15) < 95999 || 2a* || 2b*]
    then
        head -n i data.csv | tail -1 >> fichier.txt
    fi
done

## si option pour guyane
for i in {2..$nblignes}
do
    if [(head -n $i data.csv | tail -1 | cut -d ';' -f15) =< 97399 && (head -n $i data.csv | tail -1 | cut -d ';' -f15) => 97300]
    then
        head -n i data.csv | tail -1 >> fichier.txt
    fi
done

## si option pour guyane
for i in {2..$nblignes}
do
    if [(head -n $i data.csv | tail -1 | cut -d ';' -f15) =< 97599 && (head -n $i data.csv | tail -1 | cut -d ';' -f15) => 97500]
    then
        head -n i data.csv | tail -1 >> fichier.txt
    fi
done

## si option pour guyane
for i in {2..$nblignes}
do
    if [(head -n $i data.csv | tail -1 | cut -d ';' -f15) =< 97199 && (head -n $i data.csv | tail -1 | cut -d ';' -f15) => 97100]
    then
        head -n i data.csv | tail -1 >> fichier.txt
    fi
done

