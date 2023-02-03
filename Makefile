CC=gcc
OPTION=-Wall -lm
RM=rm -rf	# force la suppression
SRC=$(wildcard Fichier_C/*.c) # fichiers source par wildcard dans srcdir
HEAD=$(wildcard Fichier_C/*.h) # fichiers d'entete idem
OBJ=$(SRC:.c=.o)  # fichiers objet par récupération des .c 
				  # et placement dans les bon répertoires
PROG=Fichier_C/Meteo # exécutables

all : $(PROG)		# target principal

$(PROG) : $(OBJ) 	# compilation du programme
	$(CC) -g $^ -o $@ $(OPTION)

%.o : %.c		# compilation des objets
	$(CC) -c $^ -o $@ $(OPTION)

.PHONY : clean mrproper print	# cibles sans dépendances à toujours executer

clean :	# nettoyage des fichiers objets pour recompilation totale
	$(RM) $(OBJ)

mrproper :	# nettoyage de tout fichier compilé
	$(RM) $(PROG) $(OBJ)

print :		# validation des variables par affichage
	@echo "SRC= $(SRC)"
	@echo "HEAD= $(HEAD)"
	@echo "OBJ= $(OBJ)"

