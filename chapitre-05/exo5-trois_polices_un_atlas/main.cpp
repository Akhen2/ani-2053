#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Représente un groupe de glyphes appartenant à une même police.
struct Groupe
{
    std::string police;
    long long n;
    long long w;
    long long h;
};

// Mémorise la position du premier et du dernier glyphe d'un groupe.
struct PositionGroupe
{
    long long x1;
    long long y1;
    long long x2;
    long long y2;
};

// Calcule les positions de tous les groupes dans la texture.
// Retourne false si tous les glyphes ne peuvent pas être placés.
bool rangerGlyphes(
    const std::vector<Groupe>& groupes,
    long long P,
    long long W,
    long long H,
    std::vector<PositionGroupe>& positions)
{
    // Le curseur commence avec une marge P sur les deux axes.
    long long x = P;
    long long y = P;

    // Hauteur de l'étagère actuelle, marge du glyphe comprise.
    long long e = 0;

    // Les positions sont recalculées à chaque nouvel essai.
    positions.clear();

    // Parcours des groupes dans l'ordre de lecture.
    for (const Groupe& groupe : groupes)
    {
        PositionGroupe position;

        // Les dimensions de rangement incluent la marge P.
        long long rw = groupe.w + P;
        long long rh = groupe.h + P;

        bool premierPlace = false;

        // Placement des glyphes du groupe, un par un.
        for (long long j = 0; j < groupe.n; ++j)
        {
            // Si le glyphe dépasse horizontalement,
            // on passe à l'étagère suivante.
            if (x + rw > W - P)
            {
                x = P;
                y = y + e + P;
                e = 0;

                // Si le glyphe dépasse encore horizontalement,
                // l'essai échoue.
                if (x + rw > W - P)
                {
                    return false;
                }
            }

            // Vérification de la limite verticale.
            if (y + rh > H - P)
            {
                return false;
            }

            // Enregistrement de la position du glyphe.
            if (!premierPlace)
            {
                position.x1 = x;
                position.y1 = y;
                premierPlace = true;
            }

            // La position du glyphe actuel devient la position
            // du dernier glyphe rencontré dans ce groupe.
            position.x2 = x;
            position.y2 = y;

            // Avancement horizontal après le placement.
            x = x + rw;

            // Mise à jour de la hauteur de l'étagère.
            e = std::max(e, rh);
        }

        // Enregistrement des positions du groupe.
        positions.push_back(position);
    }

    // Tous les glyphes ont été placés.
    return true;
}

int main()
{
    long long P, L;
    std::cin >> P, L;

    int G;
    std::cin >> G;

    // Lecture de tous les groupes de glyphes.
    std::vector<Groupe> groupes;
    groupes.reserve(G);

    for (int i = 0; i < G; ++i)
    {
        Groupe groupe;

        std::cin >> groupe.police    >> groupe.n    >> groupe.w    >> groupe.h;

        groupes.push_back(groupe);
    }

    // Aucun groupe : seule la ligne AUCUN doit être affichée.
    if (G == 0)
    {
        std::cout << "AUCUN" << std::endl;
        return 0;
    }

    // Calcul du besoin total pour déterminer la largeur automatique.
    long long besoin = 0;

    // Calcul de la surface réellement occupée par les glyphes,
    // sans compter les marges.
    long long occupe = 0;

    for (const Groupe& groupe : groupes)
    {
        // Surface nécessaire avec les marges.
        besoin += groupe.n
                  * (groupe.w + P)
                  * (groupe.h + P);

        // Surface réellement occupée, sans les marges.
        occupe += groupe.n * groupe.w * groupe.h;
    }

    // Détermination de la largeur initiale.
    long long W;

    if (L != 0)
    {
        W = L;
    }
    else
    {
        // En largeur automatique, on commence à 512 pixels.
        W = 512;

        // La largeur double tant que la surface carrée
        // est inférieure à deux fois le besoin.
        while (W * W < 2 * besoin && W < 4096)
        {
            W *= 2;
        }
    }

    // La hauteur initiale est égale à la largeur.
    long long H = W;

    std::vector<PositionGroupe> positions;
    int essais = 0;
    bool reussi = false;

    // Huit essais au maximum.
    while (essais < 8)
    {
        ++essais;

        // On recommence le rangement de tous les glyphes.
        if (rangerGlyphes(groupes, P, W, H, positions))
        {
            reussi = true;
            break;
        }

        // Agrandissement selon la règle de l'énoncé.
        if (W == H)
        {
            W *= 2;
        }
        else
        {
            H = W;
        }
    }

    // Affichage du nombre d'essais effectués.
    std::cout << "ESSAIS " << essais << std::endl;

    // Si aucun essai n'a réussi, on affiche ECHEC.
    if (!reussi)
    {
        std::cout << "ECHEC" << std::endl;
        return 0;
    }

    // Affichage des dimensions finales de la texture.
    std::cout << "TEXTURE " << W << " " << H << std::endl;

    // Affichage des positions du premier et du dernier glyphe
    // de chaque groupe, dans l'ordre de lecture.
    for (size_t i = 0; i < groupes.size(); ++i)
    {
        std::cout << groupes[i].police << " "
             << positions[i].x1 << " "
             << positions[i].y1 << " "
             << positions[i].x2 << " "
             << positions[i].y2 << std::endl;
    }

    // Calcul de la surface totale de la texture.
    long long surfaceTexture = W * H;

    // Pourcentage de surface perdue, arrondi vers le bas.
    long long perdu =
        (surfaceTexture - occupe) * 100 / surfaceTexture;

    std::cout << "OCCUPE " << occupe << std::endl;
    std::cout << "PERDU " << perdu << std::endl;

    return 0;
}
