#include <iostream>
#include <string>
#include <algorithm>

// Représente un point avec des coordonnées entières.
struct Point
{
    long long x;
    long long y;
};

// Ramène un angle dans l'intervalle [0, 359].
int normaliserAngle(long long angle)
{
    int resultat = static_cast<int>(angle % 360);

    // En C++, le modulo d'un nombre négatif reste négatif.
    // On ajoute donc 360 pour obtenir un angle positif.
    if (resultat < 0)
    {
        resultat += 360;
    }

    return resultat;
}

int main()
{
    int N;
    std::cin >> N;

    int refus = 0;

    for (int i = 0; i < N; ++i)
    {
        std::string nom;
        long long w, h;
        long long px, py;
        long long ox, oy;
        long long sx, sy;
        long long angle;

        std::cin >> nom >> w >> h
            >> px >> py
            >> ox >> oy
            >> sx >> sy
            >> angle;

        // On ramène l'angle entre 0 et 359 degrés.
        int angleNormalise = normaliserAngle(angle);

        // Seuls les multiples de 90 degrés sont acceptés.
        if (angleNormalise != 0 &&
            angleNormalise != 90 &&
            angleNormalise != 180 &&
            angleNormalise != 270)
        {
            std::cout << nom << " ANGLE REFUSE" << std::endl;
            ++refus;
            continue;
        }

        // Valeurs exactes de cos(angle) et sin(angle)
        // pour les quatre angles possibles.
        long long c = 0;
        long long s = 0;

        if (angleNormalise == 0)
        {
            c = 1;
            s = 0;
        }
        else if (angleNormalise == 90)
        {
            c = 0;
            s = 1;
        }
        else if (angleNormalise == 180)
        {
            c = -1;
            s = 0;
        }
        else // angleNormalise == 270
        {
            c = 0;
            s = -1;
        }

        // Les quatre coins locaux du rectangle.
        // Ordre imposé :
        // haut-gauche, haut-droit, bas-droit, bas-gauche.
        Point coinsLocaux[4] =
        {
            {0, 0},
            {w, 0},
            {w, h},
            {0, h}
        };

        // Tableau qui contiendra les quatre coins dans le monde.
        Point coinsMonde[4];

        for (int j = 0; j < 4; ++j)
        {
            long long x = coinsLocaux[j].x;
            long long y = coinsLocaux[j].y;

            // 1. On retire d'abord l'origine.
            // 2. Puis on applique l'échelle.
            long long ax = (x - ox) * sx;
            long long ay = (y - oy) * sy;

            // Rotation.
            // L'axe Y descend vers le bas :
            // un angle positif tourne donc dans le sens horaire.
            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;

            // Translation vers la position du rectangle dans le monde.
            coinsMonde[j].x = px + rx;
            coinsMonde[j].y = py + ry;
        }

        // Recherche de la boîte englobante.
        long long minx = coinsMonde[0].x;
        long long maxx = coinsMonde[0].x;
        long long miny = coinsMonde[0].y;
        long long maxy = coinsMonde[0].y;

        for (int j = 1; j < 4; ++j)
        {
            minx = std::min(minx, coinsMonde[j].x);
            maxx = std::max(maxx, coinsMonde[j].x);
            miny = std::min(miny, coinsMonde[j].y);
            maxy = std::max(maxy, coinsMonde[j].y);
        }

        // Affichage des quatre coins dans l'ordre demandé.
        std::cout << nom << " COINS" << std::endl;

        for (int j = 0; j < 4; ++j)
        {
            std::cout << " " << coinsMonde[j].x
                 << " " << coinsMonde[j].y << std::endl;
        }

        std::cout << std::endl;

        // Affichage de la boîte englobante.
        std::cout << nom << " BOITE "
             << minx << " "
             << miny << " "
             << maxx << " "
             << maxy << std::endl;
    }

    // Nombre total de rectangles dont l'angle a été refusé.
    std::cout << "REFUSES " << refus << std::endl;

    return 0;
}
