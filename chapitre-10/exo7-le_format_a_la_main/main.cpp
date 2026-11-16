#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cstring>

// Structure qui représente une image.
struct Image {
    float x, y;
    float echelle, rotation, opacite;
    int mx, my;
    std::uint32_t largeur, hauteur, taille;
};

// Structure qui représente un point.
struct Point {
    float x, y;
};

// Structure qui représente un trait.
struct Trait {
    int r, g, b, a;
    float epaisseur;
    std::vector<Point> points;
};

// Lecture d'un octet.
bool lireU8(const std::vector<unsigned int>& octets,
            std::size_t& position, unsigned int& valeur) {

    if (position >= octets.size()) {
        return false;
    }

    valeur = octets[position];
    position++;

    return true;
}

// Lecture d'un entier non signé de quatre octets.
bool lireU32(const std::vector<unsigned int>& octets,
             std::size_t& position, std::uint32_t& valeur) {

    if (octets.size() - position < 4) {
        return false;
    }

    // Reconstruction de l'entier en petit-boutiste.
    valeur = octets[position]
           | (octets[position + 1] << 8)
           | (octets[position + 2] << 16)
           | (octets[position + 3] << 24);

    position += 4;

    return true;
}

// Lecture d'un nombre à virgule sur quatre octets.
bool lireF32(const std::vector<unsigned int>& octets,
             std::size_t& position, float& valeur) {

    std::uint32_t nombre;

    if (!lireU32(octets, position, nombre)) {
        return false;
    }

    // Conversion des bits en nombre float.
    std::memcpy(&valeur, &nombre, sizeof(float));

    return true;
}

// Sauter un nombre donné d'octets.
bool sauterOctets(const std::vector<unsigned int>& octets,
                  std::size_t& position, std::uint32_t nombre) {

    if (nombre > octets.size() - position) {
        return false;
    }

    position += nombre;

    return true;
}

// Affichage d'un nombre à deux chiffres après la virgule.
double corrigerZero(double valeur) {
    if (valeur > -0.005 && valeur < 0.005) {
        return 0.0;
    }

    return valeur;
}

int main() {

    // Lecture du nombre total d'octets.
    std::size_t T;
    std::cin >> T;

    // Lecture des octets en hexadécimal.
    std::vector<unsigned int> octets;

    for (std::size_t i = 0; i < T; i++) {

        std::string texte;
        if (!(std::cin >> texte)) {
            break;
        }

        unsigned int valeur;

        // Conversion du texte hexadécimal en entier.
        std::stringstream conversion(texte);
        conversion >> std::hex >> valeur;

        octets.push_back(valeur);
    }

    // Position actuelle dans le fichier.
    std::size_t position = 0;

    // Vérification de la signature NKRF.
    const unsigned int signature[4] = {
        0x4E, 0x4B, 0x52, 0x46
    };

    for (int i = 0; i < 4; i++) {

        unsigned int valeur;

        if (!lireU8(octets, position, valeur)) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        if (valeur != signature[i]) {
            std::cout << "PAS_UNE_PLANCHE\n";
            return 0;
        }
    }

    // Lecture de la version.
    std::uint32_t version;

    if (!lireU32(octets, position, version)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    if (version != 1) {
        std::cout << "VERSION_INCONNUE " << version << "\n";
        return 0;
    }

    // Lecture des informations de la vue.
    float cx, cy, zoom;

    if (!lireF32(octets, position, cx) ||
        !lireF32(octets, position, cy) ||
        !lireF32(octets, position, zoom)) {

        std::cout << "TRONQUE\n";
        return 0;
    }

    // Lecture du thème et de la grille.
    unsigned int theme, grille;
    unsigned int remplissage;

    if (!lireU8(octets, position, theme) ||
        !lireU8(octets, position, grille) ||
        !lireU8(octets, position, remplissage) ||
        !lireU8(octets, position, remplissage)) {

        std::cout << "TRONQUE\n";
        return 0;
    }

    // Lecture du nombre d'images.
    std::uint32_t nombreImages;

    if (!lireU32(octets, position, nombreImages)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    // Tableau des images.
    std::vector<Image> images;

    // Lecture de chaque image.
    for (std::uint32_t i = 0; i < nombreImages; i++) {

        Image image;

        unsigned int miroirX, miroirY;
        unsigned int ignore;

        // Lecture des cinq nombres à virgule.
        if (!lireF32(octets, position, image.x) ||
            !lireF32(octets, position, image.y) ||
            !lireF32(octets, position, image.echelle) ||
            !lireF32(octets, position, image.rotation) ||
            !lireF32(octets, position, image.opacite)) {

            std::cout << "TRONQUE\n";
            return 0;
        }

        // Lecture des miroirs.
        if (!lireU8(octets, position, miroirX) ||
            !lireU8(octets, position, miroirY) ||
            !lireU8(octets, position, ignore) ||
            !lireU8(octets, position, ignore)) {

            std::cout << "TRONQUE\n";
            return 0;
        }

        image.mx = (miroirX != 0) ? 1 : 0;
        image.my = (miroirY != 0) ? 1 : 0;

        // Lecture de la largeur, de la hauteur et de la taille.
        if (!lireU32(octets, position, image.largeur) ||
            !lireU32(octets, position, image.hauteur) ||
            !lireU32(octets, position, image.taille)) {

            std::cout << "TRONQUE\n";
            return 0;
        }

        // Saut des octets source de l'image.
        if (!sauterOctets(octets, position, image.taille)) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        images.push_back(image);
    }

    // Lecture du nombre de traits.
    std::uint32_t nombreTraits;

    if (!lireU32(octets, position, nombreTraits)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    // Tableau des traits.
    std::vector<Trait> traits;

    // Lecture de chaque trait.
    for (std::uint32_t i = 0; i < nombreTraits; i++) {

        Trait trait;

        unsigned int couleur;

        // Lecture des quatre composantes de couleur.
        if (!lireU8(octets, position, couleur)) {
            std::cout << "TRONQUE\n";
            return 0;
        }
        trait.r = couleur;

        if (!lireU8(octets, position, couleur)) {
            std::cout << "TRONQUE\n";
            return 0;
        }
        trait.g = couleur;

        if (!lireU8(octets, position, couleur)) {
            std::cout << "TRONQUE\n";
            return 0;
        }
        trait.b = couleur;

        if (!lireU8(octets, position, couleur)) {
            std::cout << "TRONQUE\n";
            return 0;
        }
        trait.a = couleur;

        // Lecture de l'épaisseur.
        if (!lireF32(octets, position, trait.epaisseur)) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        // Lecture du nombre de points.
        std::uint32_t nombrePoints;

        if (!lireU32(octets, position, nombrePoints)) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        // Lecture des coordonnées des points.
        for (std::uint32_t j = 0; j < nombrePoints; j++) {

            Point point;

            if (!lireF32(octets, position, point.x) ||
                !lireF32(octets, position, point.y)) {

                std::cout << "TRONQUE\n";
                return 0;
            }

            trait.points.push_back(point);
        }

        traits.push_back(trait);
    }

    // À partir d'ici, le fichier est entièrement décodé.
    // On peut afficher les informations.

    std::cout << std::fixed << std::setprecision(2);

    // Affichage de la vue.
    std::cout << "VUE "
              << corrigerZero(cx) << " "
              << corrigerZero(cy) << " "
              << corrigerZero(zoom) << "\n";

    // Affichage du thème.
    if (theme != 0) {
        std::cout << "THEME SOMBRE\n";
    } else {
        std::cout << "THEME CLAIR\n";
    }

    // Affichage de la grille.
    if (grille == 0) {
        std::cout << "GRILLE AFFICHEE\n";
    } else {
        std::cout << "GRILLE CACHEE\n";
    }

    // Affichage des images.
    std::cout << "IMAGES " << images.size() << "\n";

    for (std::size_t i = 0; i < images.size(); i++) {

        Image image = images[i];

        std::cout << "IMAGE " << i + 1 << " "
                  << corrigerZero(image.x) << " "
                  << corrigerZero(image.y) << " "
                  << corrigerZero(image.echelle) << " "
                  << corrigerZero(image.rotation) << " "
                  << corrigerZero(image.opacite) << " "
                  << image.mx << " "
                  << image.my << " "
                  << image.largeur << " "
                  << image.hauteur << " "
                  << image.taille << "\n";
    }

    // Affichage des traits.
    std::cout << "TRAITS " << traits.size() << "\n";

    for (std::size_t i = 0; i < traits.size(); i++) {

        Trait trait = traits[i];

        std::cout << "TRAIT " << i + 1 << " "
                  << trait.r << " "
                  << trait.g << " "
                  << trait.b << " "
                  << trait.a << " "
                  << corrigerZero(trait.epaisseur) << " "
                  << trait.points.size() << "\n";

        // Affichage des points du trait.
        for (std::size_t j = 0; j < trait.points.size(); j++) {

            std::cout << "POINT "
                      << corrigerZero(trait.points[j].x) << " "
                      << corrigerZero(trait.points[j].y) << "\n";
        }
    }

    return 0;
}