#!/bin/bash


usage()
{
    echo "Usage : parametre [ -t | --temperature ] [ -h | --humidite ]
                  [ -p | --pression ] [ -w | --vent ]"
    exit 10
}

PARSED_ARGUMENTS=$(getopt -a -n parametre -o thpw: --long temperature,humidite,pression,vent: -- "$@")
VALID_ARGUMENTS=$?
if [ "$VALID_ARGUMENTS" != 0 ]; then
    usage
fi

echo "les arguments sont : $PARSED_ARGUMENTS"
eval set -- "$PARSED_ARGUMENTS"
while :
do 
    case "$1" in
       -t | --temperature)    TEMPERATURE+=1 ; shift ;;
       -h | --humidite)       HUMIDITE=1    ; shift ;; 
       -p | --pression)       PRESSION=1    ; shift ;;
       -w | --vent)           VENT=1        ; shift ;;
       --) shift; break;;
       *) echo "Option inconnu: $1" usage ;;
    esac
done
