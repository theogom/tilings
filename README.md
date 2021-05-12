# Tilings

## Usage

`./bin/tilings [-s seed] [-b board_size] [-n number_of_players]`


## Description

Ce programme simule une partie de jeu de pavage à l'aide de tuiles de Wang, puis affiche le tableau des scores ainsi que le plateau en fin de partie.


## Options

* -s : modifie la graine pour le générateur aléatoire (valeur par défaut : 11098)

* -b : définie la taille du plateau (valeur par défaut : 10)

* -n : définie le nombre de joueurs (valeur par défaut : 3)


## Compilation

Le dossier contient un fichier Makefile permettant de réaliser les différentes opérations de compilation.
Les options disponibles sont les suivantes :

* `make` : compilation des différents fichiers sources .c dans src

* `make install` : installation des différents exécutables dans le dossier `bin`

* `make game` : lancement d'une partie avec les paramètres par défaut

* `make test` : création des exécutables de test à partir des fichiers .c dans src et tst, et lancement des tests

* `make clean` : suppression des fichiers objets .o, des fichiers de dépendances .d, ainsi que des exécutables


## Lien utiles

* Lien vers le sujet du projet :
<https://www.labri.fr/perso/renault/working/teaching/projets/2020-21-S5-Tilings.php>
