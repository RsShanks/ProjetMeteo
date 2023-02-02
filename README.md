# INSTALLATION :

Installer Projet-Meteo.
Donnez-vous les droits d'éxecution de Meteo.bash et vous serez prêt à utiliser le programme.
Déposez votre fichier .csv dans le repertoire Projet-Meteo.

# Usage :

La commande d'éxecution du programme :
./Meteo -f [fichier.csv] [option] [zone]

le fichier doit obligatoirement être un .csv.

les options sont : 
        [ -t<1,2,3> ]     temperature (tri croissant)
        [ -m ]            humidité (tri décroissant)
        [ -h ]            altitude (tri décroissant)
        [ -p<1,2,3> ]     pression (tri croissant)
        [ -w ]            vent (tri croissant)

1 : produit en sortie les températures (ou pressions) minimales, maximales et moyennes par station dans l’ordre
    croissant du numéro de station.
2 : produit en sortie les températures (ou pressions) moyennes par date/heure, triées dans l’ordre chronologique.
    La moyenne se fait sur toutes les stations.
3 : produit en sortie les températures (ou pressions) par date/heure par station. Elles seront triées d’abord par ordre
    chronologique, puis par ordre croissant de l’identifiant de lastation.

Il peut y avoir 1 ou plusieurs options sans limites. 

les zones sont : 
        [ -F (France) ]
        [ -G (Guyane) ]
        [ -A (Antilles) ]
        [ -S (Saint-Pierre et Miquelon) ]
        [ -Q (Antartiques et Terres Australes) ]
        [ -O (Océan Indien) ]

Il ne peut y avoir que 1 zone au maximum et 0 au minimum (dans ce cas le programme traitera toutes les données).

# BONUS : 

-r (inverse) , qui permet d'inverser les tris (croissant -> decroissant , decroissant -> croissant)

# Processus : 

Le programme récupère votre fichier csv.
Il le trie en fonction des options demandées et créés des fichiers temporaires.
il rend ensuite le fichier exploitable par le C.
Il filtre en fonction de la zone si vous l'avez spécifié a l'appel de la commande, en faisant appel au programme C : tri_lignes_ZONE.c .
Il trie selon l'/les option(s) spécifiée(s) et depose le résultat dans le repertoire : résultat_tri/ . Il utilise le programme : AVL.c ABR.c TAB.c selon l'/les option(s) spécifiée(s).
Il va ensuite créé un/des graphique(s) selon l'/les option(s) spécifiée(s) dans le repertoire : graphiqueGnuplot/ .

# Execution des programmes C : 

Les programmes C transforment toutes les valeurs des cases en double, il faut éviter de mettre des caracteres ou de la ponctuation autre que des points et des points virgules  dans les cases veuillez vérifier que votre tableau n'en contiennent pas avant. (Hormis si c'est la date qui est au format : xxxx-xx-xxTxx:xx:xx+xx:xx et les coordonnées au format : xx.xx,xx.xx )

Filtre_ZONE : 

Pour l'utilser il faut posséder un csv propre c'est à dire qu'il possède que des nombres et des points virgules, aucun autre caractere sinon capable de provoquer une erreur.
Le filtrage s'effectuera correctement si les 2 dernières colonnes sont les coordonnées. 

Commande : 

./Fichier_C/Meteo -f [Fichier.csv] -o [Fichier_de_sortie.csv] -l [nblignes] -c [nbcolonnes] -z [zone] -k 4

AVL.c ABR.c TAB.c : 

Pour l'utilser il faut posséder un csv propre c'est à dire qu'il possède que des nombres et des points virgules, aucun autre caractere sinon capable de provoquer une erreur.
Le tri s'effectuera selon des caractères très spéciaux aux options demandées sur la 1ère colonne et peut altérer les autres colonnes.
Pour récuperer un fichier utilisable pour une option vous pouvez enlever la ligne 357 de Meteo.bash .

Commande : 

./Fichier_C/Meteo -f [Fichier.csv] -o [Fichier_de_sortie.csv] -l [nblignes] -c [nbcolonnes] -[option] -k [mode_de_tri] -r [inverse]

mode_de_tri : 1 pour AVL , 2 pour ABR , 3 pour TAB(liste chainée)
inverse : 0 tri normal (voir au dessus) , 1 inversion des tris 

