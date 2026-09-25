# Exercice 1 :

Dans ce code qui affiche une fenêtre, on retrouve 19 lignes de code.

On y retrouve notamment :

## Les includes

````cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
````
Indispensable pour commencer à programmer pour avoir les outils pour la création de la fenêtre. Ces includes se trouvent dans le chapitre

## Le point d'entrée

````cpp
int nkmain(...)
````
Ce point d'entrée se trouve effectivent dans le chapitre du cours.

## La partie déclaration

````cpp
NkWindowConfig cfg;
    cfg.title  = "Ma fenêtre";
    cfg.width  = 1280;
    cfg.height = 720;
````
Elle sert à entrer les informations nécessaires pour la création de la fenêtre et ces différentes configurations se trouve dans le chapitre

## La partie création

````cpp
NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }
````
Cette partie sert à vérifier si la fenêtre s'est correctement initialisée pour sa création. Elle se trouve dans le chapitre 

## La boucle principale 

````cpp
 while (window.IsOpen()) {
      while (NkEvent* ev = NkEvents().PollEvent()) {
        if (ev->Is<NkWindowCloseEvent>()) {
            window.Close();          // l'utilisateur veut fermer
        }
        else if (auto* kp = ev->As<NkKeyPressEvent>()) {
            if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
        }
    }

    }
````
Ici, c'est la partie qui s'occupe de la gestion des évènements à savoir la fermeture, l'agrandissement et la réduction de la fenêtre. Cette partie se trouve dans le chapitre mais elle est completé par des éléments provenant du chapitre de NKEvents