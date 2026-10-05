#include <iostream>
#include <string>
#include <vector>

// Structure représentant un objet dans le monde
struct Objet
{
    std::string nom;
    std::string parent;

    // Transformation propre de l'objet
    int tx;
    int ty;
    int angle;
    int echelle;

    // Transformation dans le monde
    int mondeX;
    int mondeY;
    int mondeAngle;
    int mondeEchelle;

    // Niveau de profondeur dans la hiérarchie
    int profondeur;
};

// ------------------------------------------------------------
// Fonction permettant de normaliser un angle entre 0 et 270.
// Les angles sont toujours des multiples de 90 degrés.
// ------------------------------------------------------------
int normaliserAngle(int angle)
{
    // L'opérateur % peut donner une valeur négative en C++.
    angle %= 360;

    if (angle < 0)
    {
        angle += 360;
    }

    return angle;
}

// ------------------------------------------------------------
// Retourne le cosinus correspondant à un angle multiple
// de 90 degrés.
//
// On utilise directement les valeurs exactes afin d'éviter
// les problèmes d'arrondi liés à cos() et sin().
// ------------------------------------------------------------
int cosAngle(int angle)
{
    switch (normaliserAngle(angle))
    {
        case 0:
            return 1;

        case 90:
            return 0;

        case 180:
            return -1;

        case 270:
            return 0;
    }

    return 1;
}

// ------------------------------------------------------------
// Retourne le sinus correspondant à un angle multiple
// de 90 degrés.
// ------------------------------------------------------------
int sinAngle(int angle)
{
    switch (normaliserAngle(angle))
    {
        case 0:
            return 0;

        case 90:
            return 1;

        case 180:
            return 0;

        case 270:
            return -1;
    }

    return 0;
}

int main()
{
    // Nombre d'objets
    int N;
    std::cin >> N;

    // Tableau contenant tous les objets dans l'ordre de lecture
    vector<Objet> objets;

    // Profondeur maximale rencontrée
    int profondeurMax = 0;

    // --------------------------------------------------------
    // Lecture et traitement des objets
    // --------------------------------------------------------
    for (int i = 0; i < N; i++)
    {
        Objet objet;

        std::cin >> objet.nom
            >> objet.parent
            >> objet.tx
            >> objet.ty
            >> objet.angle
            >> objet.echelle;

        // ====================================================
        // CAS 1 : l'objet n'a pas de parent
        // ====================================================
        if (objet.parent == "-")
        {
            // Un objet sans parent est directement dans le monde.
            objet.mondeX = objet.tx;
            objet.mondeY = objet.ty;

            // Son angle propre est aussi son angle monde.
            objet.mondeAngle = normaliserAngle(objet.angle);

            // Son échelle propre est son échelle monde.
            objet.mondeEchelle = objet.echelle;

            // Une racine est au niveau 1.
            objet.profondeur = 1;
        }
        else
        {
            // =================================================
            // CAS 2 : l'objet possède un parent
            // =================================================

            // Recherche du parent dans les objets déjà lus.
            int indiceParent = -1;

            for (int j = 0; j < static_cast<int>(objets.size()); j++)
            {
                if (objets[j].nom == objet.parent)
                {
                    indiceParent = j;
                    break;
                }
            }

            // Le parent est forcément trouvé car l'énoncé
            // garantit qu'il est lu avant l'enfant.
            const Objet& parent = objets[indiceParent];

            // -------------------------------------------------
            // 1. APPLICATION DE L'ÉCHELLE DU PARENT
            // -------------------------------------------------

            // La position locale de l'enfant est multipliée
            // par l'échelle du parent dans le monde.
            int ax = objet.tx * parent.mondeEchelle;
            int ay = objet.ty * parent.mondeEchelle;

            // -------------------------------------------------
            // 2. APPLICATION DE LA ROTATION DU PARENT
            // -------------------------------------------------

            int c = cosAngle(parent.mondeAngle);
            int s = sinAngle(parent.mondeAngle);

            // Formules de rotation :
            //
            // rx = ax * cos(angle) - ay * sin(angle)
            // ry = ax * sin(angle) + ay * cos(angle)
            int rx = ax * c - ay * s;
            int ry = ax * s + ay * c;

            // -------------------------------------------------
            // 3. AJOUT DE LA POSITION DU PARENT
            // -------------------------------------------------

            objet.mondeX = parent.mondeX + rx;
            objet.mondeY = parent.mondeY + ry;

            // -------------------------------------------------
            // 4. COMPOSITION DES ANGLES
            // -------------------------------------------------

            objet.mondeAngle =
                normaliserAngle(parent.mondeAngle + objet.angle);

            // -------------------------------------------------
            // 5. COMPOSITION DES ÉCHELLES
            // -------------------------------------------------

            objet.mondeEchelle =
                parent.mondeEchelle * objet.echelle;

            // -------------------------------------------------
            // 6. CALCUL DE LA PROFONDEUR
            // -------------------------------------------------

            objet.profondeur = parent.profondeur + 1;
        }

        // Mise à jour de la profondeur maximale
        if (objet.profondeur > profondeurMax)
        {
            profondeurMax = objet.profondeur;
        }

        // On ajoute l'objet au tableau.
        // Il pourra servir de parent aux objets suivants.
        objets.push_back(objet);
    }

    // --------------------------------------------------------
    // AFFICHAGE DES OBJETS DANS L'ORDRE DE LECTURE
    // --------------------------------------------------------

    for (const Objet& objet : objets)
    {
        std::cout << objet.nom << " "
             << objet.mondeX << " "
             << objet.mondeY << " "
             << objet.mondeAngle << " "
             << objet.mondeEchelle << std::endl;
    }

    // Affichage de la profondeur maximale
    std::cout << "PROFONDEUR " << profondeurMax << std::endl;

    return 0;
}
