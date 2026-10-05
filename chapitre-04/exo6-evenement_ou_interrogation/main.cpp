#include <iostream>
#include <string>

int main()
{
    // Lecture de la vitesse et du nombre d'images
    int v, N;
    std::cin >> v >> N;

    // Positions initiales des deux carrés
    int xe = 0; // Position du carré contrôlé par événements
    int xi = 0; // Position du carré contrôlé par interrogation

    // État actuel des touches
    bool space = false;
    bool left = false;
    bool right = false;

    // Compteurs demandés par l'énoncé
    int sautsEvenements = 0;
    int sautsInterrogation = 0;
    int manques = 0;

    // Traitement de chaque image
    for (int i = 1; i <= N; i++)
    {
        int k;
        std::cin >> k;

        // Indique si un +SPACE a été reçu pendant cette image.
        // Cette information est nécessaire pour calculer MANQUES.
        bool espaceAppuye = false;

        // Lecture et traitement des événements de l'image
        for (int j = 0; j < k; j++)
        {
            std::string evenement;
            std::cin >> evenement;

            // Un événement est composé de :
            // '+' ou '-' suivi du nom de la touche.
            char action = evenement[0];
            std::string nom = evenement.substr(1);

            // On ignore les touches inconnues.
            if (nom != "SPACE" &&
                nom != "LEFT" &&
                nom != "RIGHT")
            {
                continue;
            }

            // =====================================================
            // TOUCHE SPACE
            // =====================================================
            if (nom == "SPACE")
            {
                if (action == '+')
                {
                    // La touche devient enfoncée.
                    space = true;

                    // Chaque +SPACE compte comme un saut
                    // dans la méthode par événements.
                    sautsEvenements++;

                    // On mémorise qu'un appui a eu lieu
                    // pendant cette image.
                    espaceAppuye = true;
                }
                else if (action == '-')
                {
                    // La touche devient relâchée.
                    space = false;
                }
            }

            // =====================================================
            // TOUCHE RIGHT
            // =====================================================
            else if (nom == "RIGHT")
            {
                if (action == '+')
                {
                    // La touche devient enfoncée.
                    right = true;

                    // Chaque +RIGHT déplace immédiatement
                    // le carré par événements vers la droite.
                    xe += v;
                }
                else if (action == '-')
                {
                    // La touche devient relâchée.
                    right = false;
                }
            }

            // =====================================================
            // TOUCHE LEFT
            // =====================================================
            else if (nom == "LEFT")
            {
                if (action == '+')
                {
                    // La touche devient enfoncée.
                    left = true;

                    // Chaque +LEFT déplace immédiatement
                    // le carré par événements vers la gauche.
                    xe -= v;
                }
                else if (action == '-')
                {
                    // La touche devient relâchée.
                    left = false;
                }
            }
        }

        // =========================================================
        // MÉTHODE PAR INTERROGATION
        // =========================================================
        //
        // On interroge l'état des touches UNE SEULE FOIS,
        // après avoir traité tous les événements de l'image.

        // Si SPACE est encore enfoncée à la fin de l'image,
        // l'interrogation compte un saut.
        if (space)
        {
            sautsInterrogation++;
        }

        // Si RIGHT est enfoncée, le carré avance de v pixels.
        if (right)
        {
            xi += v;
        }

        // Si LEFT est enfoncée, le carré recule de v pixels.
        if (left)
        {
            xi -= v;
        }

        // =========================================================
        // CALCUL DES APPUIS MANQUÉS
        // =========================================================
        //
        // Un +SPACE est manqué si un appui a eu lieu pendant
        // l'image mais que SPACE n'est plus enfoncée à la fin.
        //
        // Dans ce cas, l'interrogation ne pouvait pas voir
        // cet appui.

        if (espaceAppuye && !space)
        {
            manques++;
        }

        // Affichage des positions pour cette image
        std::cout << i << " " << xe << " " << xi << std::endl;
    }

    // Affichage du bilan final
    std::cout << "SAUTS EVENEMENTS " << sautsEvenements << std::endl;
    std::cout << "SAUTS INTERROGATION " << sautsInterrogation << std::endl;
    std::cout << "MANQUES " << manques << std::endl;

    return 0;
}
