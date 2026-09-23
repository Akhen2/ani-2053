# Exercice 1 :

Dans ce code qui affiche une fenêtre, on retrouve 19 lignes de code.

On y retrouve notamment :

## Les includes

````bash
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
````

## Le point d'entrée

````bash
int nkmain(...)
````

## La partie déclaration

````bash
NkWindowConfig cfg;
    cfg.title  = "Ma fenêtre";
    cfg.width  = 1280;
    cfg.height = 720;
````

## La partie création

````bash
NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }
````

## La boucle principale 

````bash
 while (window.IsOpen()) {
       
    }
````