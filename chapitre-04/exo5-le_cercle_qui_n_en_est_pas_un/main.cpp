#include <iostream>
#include <cmath>

int main()
{
    // Valeur de pi imposée par l'énoncé
    const double PI = 3.141592653589793;

    // Lecture du nombre de cercles
    int N;
    std::cin >> N;

    // Compteurs des cercles visibles et refusés
    int visibles = 0;
    int refuses = 0;

    // Traitement de chaque cercle
    for (int i = 0; i < N; i++)
    {
        int r, n;
        std::cin >> r >> n;

        // Un polygone ayant moins de 3 segments
        // ne peut pas représenter un cercle.
        if (n < 3)
        {
            std::cout << r << " " << n << " REFUSE" << std::endl;
            refuses++;
            continue;
        }

        double g = r * (1.0 - cos(PI / n));

        // Si le rayon est nul, g vaut zéro.
        // Aucun agrandissement ne permettra de voir
        // les segments du polygone.
        if (g == 0.0)
        {
            // L'écart demandé est calculé en millièmes
            // de pixel et arrondi vers le bas.
            long long ecart = static_cast<long long>(floor(g * 1000.0));

            std::cout << r << " " << n << " "
                 << ecart << " JAMAIS" << std::endl;

            continue;
        }

        // Conversion de l'écart en millièmes de pixel,
        // avec un arrondi vers le bas.
        long long ecart = static_cast<long long>(floor(g * 1000.0));

        long long zoom = static_cast<long long>(ceil(100.0 / g));

        // Un cercle est considéré comme visible
        // si le zoom nécessaire est inférieur ou égal
        // à 100 %, c'est-à-dire visible à taille normale.
        if (zoom <= 100)
        {
            std::cout << r << " " << n << " "
                 << ecart << " "
                 << zoom << " VISIBLE" << std::endl;

            visibles++;
        }
        else
        {
            std::cout << r << " " << n << " "
                 << ecart << " "
                 << zoom << " INVISIBLE" << std::endl;
        }
    }

    // Affichage des statistiques finales.
    std::cout << "VISIBLES " << visibles << std::endl;
    std::cout << "REFUSES " << refuses << std::endl;

    return 0;
}
