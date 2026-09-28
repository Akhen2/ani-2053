# Exercice 3 :

Ici, il est question de gérer la fermeture de la fenêtre grâce à l'évènement de fermeture.

## Code

````cpp
  while (NkEvent* ev = NkEvents().PollEvent()) {
        if (ev->Is<NkWindowCloseEvent>()) {
            window.Close();          // l'utilisateur veut fermer
        }
        else if (auto* kp = ev->As<NkKeyPressEvent>()) {
            if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
        }
    }
````

Cet évènement permet de fermer la fenêtre grâce à la croix rouge  **❌** présente sur l'extrême droite de la fenêtre
et aussi grâce à la touche **ECHAP**