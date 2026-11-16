#include <iostream>
#include <string>
#include <cmath>

// Structure qui représente une image.
struct Image {
    std::string nom;
    double x;
    double y;
    double largeur;
    double hauteur;
    double echelle;
};

// Fonction qui vérifie si un point touche une image.
bool toucheImage(Image image, double px, double py) {

    // Calcul de la demi-largeur et de la demi-hauteur.
    double demiLargeur = image.largeur * image.echelle / 2.0;
    double demiHauteur = image.hauteur * image.echelle / 2.0;

    // Vérification de la position du clic.
    if (std::abs(px - image.x) <= demiLargeur &&
        std::abs(py - image.y) <= demiHauteur) {
        return true;
    }

    return false;
}

int main() {

    // Lecture du nombre d'images.
    int N;
    std::cin >> N;

    // Déclaration du tableau des images.
    Image images[N];

    // Lecture des informations de chaque image.
    for (int i = 0; i < N; i++) {
        std::cin >> images[i].nom
                 >> images[i].x
                 >> images[i].y
                 >> images[i].largeur
                 >> images[i].hauteur
                 >> images[i].echelle;
    }

    // Lecture du nombre de clics.
    int Q;
    std::cin >> Q;

    // Compteur des erreurs.
    int erreurs = 0;

    // Traitement de chaque clic.
    for (int k = 1; k <= Q; k++) {

        double px, py;
        std::cin >> px >> py;

        // Résultats des deux recherches.
        std::string resultatArriere = "AUCUN";
        std::string resultatEndroit = "AUCUN";

        // Recherche à rebours : de la dernière image à la première.
        for (int i = N - 1; i >= 0; i--) {

            if (toucheImage(images[i], px, py)) {
                resultatArriere = images[i].nom;
                break;
            }
        }

        // Recherche à l'endroit : de la première image à la dernière.
        for (int i = 0; i < N; i++) {

            if (toucheImage(images[i], px, py)) {
                resultatEndroit = images[i].nom;
                break;
            }
        }

        // Comparaison des deux résultats.
        if (resultatArriere != resultatEndroit) {
            erreurs++;
        }

        // Affichage du résultat du clic.
        std::cout << "CLIC " << k << " "
                  << resultatArriere << " "
                  << resultatEndroit << "\n";
    }

    // Affichage du nombre total d'erreurs.
    std::cout << "ERREURS " << erreurs << "\n";

    return 0;
}