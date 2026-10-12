#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// Informations associées à un caractère (glyphe).
struct Glyphe {
    int avance;
    int x0;
    int y0;
    int x1;
    int y1;
};

// Informations associées à un couple de caractères pour le crénage.
struct Crenage {
    char premier;
    char second;

    // Permet d'utiliser le couple comme clé dans une table.
    bool operator==(const Crenage& autre) const {
        return premier == autre.premier && second == autre.second;
    }
};

// Fonction de hachage pour les couples de caractères.
struct HachageCrenage {
    size_t operator()(const Crenage& c) const {
        return (static_cast<size_t>(
                    static_cast<unsigned char>(c.premier)) << 8)
               | static_cast<unsigned char>(c.second);
    }
};

// Informations sur la boîte englobante du texte.
struct Boite {
    int minx;
    int miny;
    int maxx;
    int maxy;
    bool existe = false;
};

int main() {
    // Table des glyphes.
    unordered_map<char, Glyphe> glyphes;

    int G;
    std::cin >> G;

    for (int i = 0; i < G; i++) {
        char c;
        Glyphe g;

        std::cin >> c >> g.avance >> g.x0 >> g.y0 >> g.x1 >> g.y1;

        // Le caractère '_' représente un espace.
        glyphes[c] = g;
    }

    // Table des corrections de crénage.
    unordered_map<Crenage, int, HachageCrenage> crenages;

    int K;
    std::cin >> K;

    for (int i = 0; i < K; i++) {
        char premier, second;
        int correction;

        std::cin >> premier >> second >> correction;

        crenages[{premier, second}] = correction;
    }

    // Lecture du texte et de la position de sa ligne de base.
    std::string texte;
    int ox, oy;

    std::cin >> texte >> ox >> oy;

    // Position initiale du curseur.
    int x = ox;

    // Boîte englobante des glyphes effectivement dessinés.
    Boite boite;

    // Hauteur maximale au-dessus et au-dessous de la ligne de base.
    int monte = 0;
    int descend = 0;

    // Nombre de caractères absents de la table.
    int absents = 0;

    // Parcours des caractères du texte dans l'ordre.
    for (size_t i = 0; i < texte.size(); i++) {
        char c = texte[i];

        // Recherche du glyphe correspondant au caractère.
        auto it = glyphes.find(c);

        // Un caractère absent ne dessine rien et ne fait pas avancer
        // le curseur. Aucun crénage ne sera appliqué après ce caractère.
        if (it == glyphes.end()) {
            std::cout << c << " ABSENT" << std::endl;
            absents++;
            continue;
        }

        // Le caractère est posé à la position actuelle du curseur.
        std::cout << c << " " << x << std::endl;

        const Glyphe& g = it->second;

        // Un glyphe est dessiné uniquement si son rectangle
        // possède une largeur et une hauteur strictement positives.
        if (g.x1 > g.x0 && g.y1 > g.y0) {
            int gx0 = x + g.x0;
            int gy0 = oy + g.y0;
            int gx1 = x + g.x1;
            int gy1 = oy + g.y1;

            // Première boîte dessinée : initialisation des limites.
            if (!boite.existe) {
                boite.minx = gx0;
                boite.miny = gy0;
                boite.maxx = gx1;
                boite.maxy = gy1;
                boite.existe = true;
            } else {
                // Agrandissement de la boîte pour inclure le glyphe.
                boite.minx = std::min(boite.minx, gx0);
                boite.miny = std::min(boite.miny, gy0);
                boite.maxx = std::max(boite.maxx, gx1);
                boite.maxy = std::max(boite.maxy, gy1);
            }
        }

        // Avance du curseur, indépendamment de la largeur du dessin.
        x += g.avance;

        // Recherche du crénage avec le caractère suivant.
        // Il n'y a pas de crénage après le dernier caractère.
        if (i + 1 < texte.size()) {
            char suivant = texte[i + 1];

            // Si le caractère suivant est absent, aucun crénage
            // ne doit être recherché après le caractère courant.
            if (glyphes.find(suivant) != glyphes.end()) {
                auto itCrenage = crenages.find({c, suivant});

                if (itCrenage != crenages.end()) {
                    x += itCrenage->second;
                }
            }
        }
    }

    // Affichage de la position finale du curseur.
    std::cout << "CURSEUR " << x << std::endl;

    // Si aucun glyphe n'a été dessiné, la boîte est inexistante.
    if (!boite.existe) {
        std::cout << "BOITE AUCUNE" << std::endl;
        std::cout << "MONTE 0" << std::endl;
        std::cout << "DESCEND 0" << std::endl;
        std::cout << "ECRAN RIEN" << std::endl;
    } else {
        // Affichage des limites de la boîte englobante.
        std::cout << "BOITE " << boite.minx << " " << boite.miny << " " << boite.maxx << " " << boite.maxy << std::endl;

        // Calcul de la hauteur au-dessus de la ligne de base.
        if (boite.miny < oy) {
            monte = oy - boite.miny;
        }

        // Calcul de la hauteur au-dessous de la ligne de base.
        if (boite.maxy > oy) {
            descend = boite.maxy - oy;
        }

        std::cout << "MONTE " << monte << std::endl;
        std::cout << "DESCEND " << descend << std::endl;

        // Détermination de la position du texte par rapport à l'écran.
        if (boite.maxy <= 0) {
            std::cout << "ECRAN HORS" << std::endl;
        } else if (boite.miny < 0) {
            std::cout << "ECRAN COUPE" << std::endl;
        } else {
            std::cout << "ECRAN VISIBLE" << std::endl;
        }
    }

    // Affichage du nombre de caractères absents.
    std::cout << "ABSENTS " << absents << std::endl;

    return 0;
}
