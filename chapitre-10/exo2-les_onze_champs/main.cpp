#include <iostream>
#include <string>

int main() {
    int N;

    // Lire le nombre d'images.
    std::cin >> N;

    // Compteurs des images et des champs modifiés.
    int restent = 0;
    int changes = 0;

    // Parcourir toutes les images.
    for (int i = 1; i <= N; i++) {

        // Lire les informations de l'image.
        int id;
        double x, y, echelle, rotation, opacite;
        int miroirX, miroirY, largeur, hauteur;
        int selectionne;
        std::string chemin;
        int octets;

        std::cin >> id >> x >> y >> echelle
                 >> rotation >> opacite
                 >> miroirX >> miroirY
                 >> largeur >> hauteur
                 >> selectionne >> chemin >> octets;

        // Une image sans octets ne peut pas être rouverte.
        if (octets == 0) {

            std::cout << "ITEM " << i << " SAUTE\n";

        } else {

            // L'image revient dans la planche.
            restent++;

            // Compter les champs qui changent.
            int nombreChanges = 0;

            // L'identifiant revient à 0.
            if (id != 0) {
                std::cout << "ITEM " << i << " "
                          << restent << " id";
                nombreChanges++;
            } else {
                std::cout << "ITEM " << i << " "
                          << restent;
            }

            // La sélection revient à 0.
            if (selectionne == 1) {
                std::cout << " selected";
                nombreChanges++;
            }

            // Le chemin revient vide.
            if (chemin != "-") {
                std::cout << " sourcePath";
                nombreChanges++;
            }

            // Aucun champ n'a changé.
            if (nombreChanges == 0) {
                std::cout << " AUCUN";
            }

            std::cout << '\n';

            // Ajouter les changements au total.
            changes += nombreChanges;
        }
    }

    // Afficher le bilan final.
    std::cout << "RESTENT " << restent << '\n';
    std::cout << "CHANGES " << changes << '\n';

    return 0;
}