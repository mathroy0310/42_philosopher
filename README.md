# Philosopher

Ce document est le fichier README pour le projet Philosopher de l'école 42. Philosopher est un projet qui implémente la problématique classique du dîner des philosophes en utilisant la programmation multithread. Le but du projet est de développer un programme qui simule le comportement des philosophes qui se trouvent autour d'une table et partagent des ressources (baguettes) pour manger.

## Introduction

Le projet Philosopher est une simulation du problème classique du dîner des philosophes. Dans ce problème, un certain nombre de philosophes se trouvent autour d'une table et alternent entre la pensée et le repas. Chaque philosophe doit utiliser deux baguettes pour manger. Le but du projet est de développer un programme qui simule ce comportement en utilisant des threads et des mécanismes de synchronisation.

## Installation

Pour utiliser ce projet, suivez les étapes suivantes :

1. Clonez ce dépôt sur votre machine locale.
2. Assurez-vous que vous avez les bibliothèques nécessaires installées sur votre système.
3. Exécutez `make` à la racine du projet pour compiler le programme `philosopher`.

## Utilisation

Pour lancer la simulation des philosophes, exécutez la commande suivante :

```
./philo [nombre_de_philosophes] [temps_de_mange] [temps_de_pense] [nombre_de_repas]
```

- `nombre_de_philosophes` : le nombre de philosophes autour de la table.
- `temps_de_mange` : le temps (en millisecondes) nécessaire pour manger un repas.
- `temps_de_pense` : le temps (en millisecondes) nécessaire pour penser.
- `nombre_de_repas` : le nombre de repas que chaque philosophe doit manger avant de terminer.

Par exemple :

```
./philo 5 100 200 3
```

La simulation démarrera avec 5 philosophes autour de la table. Chaque philosophe prendra environ 100 millisecondes pour manger, 200 millisecondes pour penser, et ils devront tous manger 3 repas avant que la simulation ne se termine.

## Exemple

Voici un exemple d'utilisation du programme Philosopher :

```bash
$ ./philo 5 100 200 3
```

La simulation des 5 philosophes démarrera, et vous pourrez observer leur comportement en train de manger et de penser.

## Ressources

- [fr.subject.pdf](https://cdn.intra.42.fr/pdf/pdf/66945/fr.subject.pdf)

## Auteur

Ce projet a été développé par Mathieu Roy (maroy) dans le cadre du cursus de l'école 42.
