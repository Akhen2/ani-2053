# Exercice 2 :

Ici, il est question de dire les touches et à donner leurs codes physique. Et cela est possible grâce à la méthode 
````cpp
GetKey();
```` 
qui donne la position des touches grâce à **NkKey**

## Touche **Z**

Lors la pression de la touche **Z**, l'évènement dit de monter. Voici le code 
````cpp
case NkKey::NK_Z:  player.Up();        break;
````

## Touche **S**

Lors la pression de la touche **S**, l'évènement dit de descendre. Voici le code 
````cpp
case NkKey::NK_S:  player.Down();        break;
````

## Touche **Q**

Lors la pression de la touche **Q**, l'évènement dit de partir à gauche. Voici le code 
````cpp
case NkKey::NK_Q:  player.Left();        break;
````

## Touche **D**

Lors la pression de la touche **D**, l'évènement dit de partir à droite. Voici le code 
````cpp
case NkKey::NK_D:  player.Right();        break;
````

## Touche **ECHAP**

Lors la pression de la touche **ECHAP**, l'évènement dit de fermer la fenêtre. Voici le code 
````cpp
case NkKey::NK_ESCAPE: window.Close();       break;
````