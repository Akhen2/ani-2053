#include <iostream>
#include <string>

int main()
{
    int N;
    std::cin >> N;

    // Compteurs globaux pour les quatre bilans finaux.
    int totalPoints = 0;
    int totalSegments = 0;
    int totalTriangles = 0;
    int totalRefuses = 0;

    for (int i = 0; i < N; ++i)
    {
        std::string type;
        int sommets;

        std::cin >> type >> sommets;

        // Type POINTS : chaque sommet forme un point.
        if (type == "POINTS")
        {
            int points = sommets;
            int restants = 0;

            totalPoints += points;

            std::cout << type << " " << sommets << " "
                 << points << " POINTS " << restants << std::endl;
        }

        // Type LINES : un segment est formé par deux sommets.
        else if (type == "LINES")
        {
            int segments = sommets / 2;
            int restants = sommets % 2;

            totalSegments += segments;

            std::cout << type << " " << sommets << " "
                 << segments << " SEGMENTS " << restants << std::endl;
        }

        // Type LINE_STRIP : avec s sommets, on forme s - 1 segments.
        else if (type == "LINE_STRIP")
        {
            int segments;
            int restants;

            if (sommets >= 2)
            {
                segments = sommets - 1;
                restants = 0;
            }
            else
            {
                // Avec 0 ou 1 sommet, aucun segment n'est formé.
                segments = 0;
                restants = sommets;
            }

            totalSegments += segments;

            std::cout << type << " " << sommets << " "
                 << segments << " SEGMENTS " << restants << std::endl;
        }

        // Type TRIANGLES : un triangle nécessite trois sommets.
        else if (type == "TRIANGLES")
        {
            int triangles = sommets / 3;
            int restants = sommets % 3;

            totalTriangles += triangles;

            std::cout << type << " " << sommets << " "
                 << triangles << " TRIANGLES " << restants << std::endl;
        }

        // TRIANGLE_STRIP et TRIANGLE_FAN :
        // avec au moins 3 sommets, on forme s - 2 triangles.
        else if (type == "TRIANGLE_STRIP" || type == "TRIANGLE_FAN")
        {
            int triangles;
            int restants;

            if (sommets >= 3)
            {
                triangles = sommets - 2;
                restants = 0;
            }
            else
            {
                // Avec 0, 1 ou 2 sommets, aucun triangle n'est formé.
                // On ne doit surtout pas obtenir un nombre négatif.
                triangles = 0;
                restants = sommets;
            }

            totalTriangles += triangles;

            std::cout << type << " " << sommets << " "
                 << triangles << " TRIANGLES " << restants << std::endl;
        }

        // Tout autre type est refusé, notamment QUADS.
        else
        {
            totalRefuses++;

            std::cout << type << " " << sommets << " REFUSE" << std::endl;
        }
    }

    // Bilans finaux, toujours dans cet ordre.
    std::cout << "POINTS " << totalPoints << std::endl;
    std::cout << "SEGMENTS " << totalSegments << std::endl;
    std::cout << "TRIANGLES " << totalTriangles << std::endl;
    std::cout << "REFUSES " << totalRefuses << std::endl;

    return 0;
}