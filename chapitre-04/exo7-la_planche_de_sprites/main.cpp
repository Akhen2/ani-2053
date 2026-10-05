#include <iostream>

int main()
{
    int C, R, W, H, F, D, P;

    std::cin >> C >> R >> W >> H >> F >> D >> P;

    // Nombre de durées dt à traiter
    int N;
    std::cin >> N;

    // Case actuelle de l'animation.
    // L'animation commence toujours sur la case 0.
    int currentCase = 0;

    // Temps accumulé depuis le dernier changement de case.
    // Il est conservé d'une image à l'autre.
    int tempsAccumule = 0;

    // Compteurs demandés par l'énoncé
    int avances = 0;
    int plafonnes = 0;

    // Traitement des N images
    for (int i = 0; i < N; i++)
    {
        int dt;
        std::cin >> dt;

        // =========================================================
        // 1. APPLICATION DU PLAFOND
        // =========================================================

        // Si le temps écoulé dépasse P, on le ramène à P.
        // Un dt égal à P n'est PAS plafonné.
        if (dt > P)
        {
            dt = P;
            plafonnes++;
        }

        // =========================================================
        // 2. AJOUT DU TEMPS ÉCOULÉ
        // =========================================================

        // On conserve le temps qui n'a pas encore permis
        // de changer de case.
        tempsAccumule += dt;

        // =========================================================
        // 3. CHANGEMENT DE CASE
        // =========================================================

        // Une même image peut faire avancer l'animation
        // de plusieurs cases.
        while (tempsAccumule >= D)
        {
            // On retire seulement D.
            // Le temps restant doit être conservé.
            tempsAccumule -= D;

            // Passage à la case suivante.
            currentCase++;

            // Si on dépasse la dernière case utilisée
            // de l'animation, on revient à la case 0.
            if (currentCase >= F)
            {
                currentCase = 0;
            }

            // Chaque changement de case compte comme une avance.
            avances++;
        }

        // =========================================================
        // 4. CALCUL DE LA POSITION DANS LA PLANCHE
        // =========================================================

        // Les cases sont parcourues :
        // - de gauche à droite
        // - puis de haut en bas.
        //
        // La colonne correspond au reste de la division
        // par le nombre de colonnes.
        int colonne = currentCase % C;

        // La ligne correspond au quotient de la division
        // par le nombre de colonnes.
        int ligne = currentCase / C;

        // Conversion de la position de la case en pixels.
        int x = colonne * W;
        int y = ligne * H;

        // Affichage :
        // numéro de case, x, y, largeur, hauteur
        std::cout << currentCase << " "
             << x << " "
             << y << " "
             << W << " "
             << H << std::endl;
    }

    // =============================================================
    // BILAN FINAL
    // =============================================================

    std::cout << "AVANCES " << avances << std::endl;
    std::cout << "PLAFONNES " << plafonnes << std::endl;

    return 0;
}
