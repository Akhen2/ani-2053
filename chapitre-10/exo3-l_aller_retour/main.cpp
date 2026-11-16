#include <iostream>
#include <iomanip>
#include <string>

// Évite d'afficher -0.00 ou -0.000000.
double corrigerZero(double valeur, double seuil) {
    if (valeur > -seuil && valeur < seuil) {
        return 0.0;
    }

    return valeur;
}

int main() {
    // Lecture de la taille de la fenêtre.
    double W, H;
    std::cin >> W >> H;

    // Initialisation de la caméra.
    double cx = 0.0;
    double cy = 0.0;
    double zoom = 1.0;

    std::string commande;

    // Lecture des commandes jusqu'à la fin de l'entrée.
    while (std::cin >> commande) {

        // Conversion d'un pixel vers le monde.
        if (commande == "VERS_MONDE") {
            double px, py;
            std::cin >> px >> py;

            double mx = cx + (px - W / 2.0) / zoom;
            double my = cy + (py - H / 2.0) / zoom;

            // Affichage avec deux chiffres après la virgule.
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "MONDE "
                      << corrigerZero(mx, 0.005) << " "
                      << corrigerZero(my, 0.005) << "\n";
        }

        // Conversion d'un point du monde vers un pixel.
        else if (commande == "VERS_PIXEL") {
            double mx, my;
            std::cin >> mx >> my;

            double px = (mx - cx) * zoom + W / 2.0;
            double py = (my - cy) * zoom + H / 2.0;

            // Affichage avec deux chiffres après la virgule.
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "PIXEL "
                      << corrigerZero(px, 0.005) << " "
                      << corrigerZero(py, 0.005) << "\n";
        }

        // Déplacement de la caméra.
        else if (commande == "DEPLACE") {
            double dx, dy;
            std::cin >> dx >> dy;

            cx = cx - dx / zoom;
            cy = cy - dy / zoom;
        }

        // Zoom autour du curseur.
        else if (commande == "ZOOM") {
            double f, px, py;
            std::cin >> f >> px >> py;

            // On mémorise le point du monde sous le curseur.
            double ax = cx + (px - W / 2.0) / zoom;
            double ay = cy + (py - H / 2.0) / zoom;

            // Modification du zoom.
            zoom = zoom * f;

            // On limite le zoom entre 0.02 et 64.
            if (zoom < 0.02) {
                zoom = 0.02;
            }

            if (zoom > 64.0) {
                zoom = 64.0;
            }

            // On recalcule le centre pour garder le point fixe.
            cx = ax - (px - W / 2.0) / zoom;
            cy = ay - (py - H / 2.0) / zoom;
        }

        // Calcul du pas de la grille.
        else if (commande == "GRILLE") {
            double m;
            std::cin >> m;

            double s = 1.0;

            // On augmente le pas jusqu'à atteindre m pixels.
            while (s * zoom < m) {
                s = s * 2.0;
            }

            // On cherche le plus petit pas qui respecte m.
            while (s * 0.5 * zoom >= m) {
                s = s / 2.0;
            }

            // Affichage avec six chiffres après la virgule.
            std::cout << std::fixed << std::setprecision(6);
            std::cout << "GRILLE "
                      << corrigerZero(s, 0.0000005) << "\n";
        }

        // Retour à la caméra de départ.
        else if (commande == "ORIGINE") {
            cx = 0.0;
            cy = 0.0;
            zoom = 1.0;
        }
    }

    // Affichage de l'état final de la caméra.
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "CENTRE "
              << corrigerZero(cx, 0.005) << " "
              << corrigerZero(cy, 0.005) << "\n";

    std::cout << "ZOOM "
              << corrigerZero(zoom, 0.005) << "\n";

    return 0;
}