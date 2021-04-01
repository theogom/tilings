# SYNOPSIS

`./project [-s seed] [-b board_size] [-n number_of_players]`


# DESCRIPTION

Ce programme simule une partie de jeu de pavage à l'aide de tuiles de Wang, puis affiche le tableau des scores ainsi que le plateau en fin de partie.


# OPTIONS

* -s : modifie la graine pour le générateur aléatoire (valeur par défaut : 11098)

* -b : définie la taille du plateau (valeur par défaut : 10)

* -n : définie le nombre de joueurs (valeur par défaut : 3)


# COMPILATION

Chaque dossier achiev[0-2]/ contient les différents fichiers sources et tests nécessaires à chaque achievement. En outre chaque dossier contient un fichier Makefile permettant de réaliser les différentes opérations de compilation.
Les options disponibles sont les suivantes :

* `make project` : création de l'exécutable principal à partir des différents fichiers .c dans achiev?/src

* `make test` : création des exécutables de test à partir des fichiers .c dans achiev?/src et achiev?/tst, et lancement des tests

* `make clean` : suppression des fichiers objets .o, des fichiers de dépendances .d, ainsi que des exécutables


# LIENS UTILES

* Lien vers le sujet du projet :
<https://www.labri.fr/perso/renault/working/teaching/projets/2020-21-S5-Tilings.php>

* Lien vers le projet sur la forge :
<https://thor.enseirb-matmeca.fr/ruby/projects/projetss5>

* Lien vers la documentation sur l'utilisation de git :
<https://thor.enseirb-matmeca.fr/ruby/docs/repository/git>