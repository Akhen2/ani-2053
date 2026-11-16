#include <iostream>
#include <vector>

int main() {

    // Lecture du nombre d'opérations.
    int N;
    std::cin >> N;

    // Tableau qui représente l'ordre des images.
    std::vector<int> images;

    // Prochain identifiant à attribuer.
    int prochainId = 1;

    // Les trois compteurs.
    int occasions = 0;
    int repercutes = 0;
    int recherches = 0;

    // Exécution des opérations.
    for (int i = 0; i < N; i++) {

        std::string operation;
        std::cin >> operation;

        // Ajout d'une nouvelle image.
        if (operation == "AJOUTE") {

            // Chaque image reçoit un nouvel identifiant.
            images.push_back(prochainId);

            // On passe à l'identifiant suivant.
            prochainId++;
        }

        // Suppression de plusieurs images.
        else if (operation == "SUPPRIME") {

            int c;
            std::cin >> c;

            // Lecture des index à supprimer.
            std::vector<int> indices(c);

            for (int j = 0; j < c; j++) {
                std::cin >> indices[j];
            }

            // Une opération de suppression a eu lieu.
            occasions++;

            // Deux gestes sont nécessaires par index supprimé.
            repercutes += 2 * c;

            // Suppression du plus grand index au plus petit.
            for (int j = c - 1; j >= 0; j--) {

                int index = indices[j];

                images.erase(images.begin() + index);
            }
        }

        // Déplacement d'une image vers le haut.
        else if (operation == "MONTE") {

            int index;
            std::cin >> index;

            // On vérifie si l'image suivante existe.
            if (index + 1 < static_cast<int>(images.size())) {

                // Échange des deux images.
                int temporaire = images[index];
                images[index] = images[index + 1];
                images[index + 1] = temporaire;

                // Comptabilisation de l'échange.
                occasions++;
                repercutes += 2;
            }
        }

        // Déplacement d'une image vers le bas.
        else if (operation == "DESCEND") {

            int index;
            std::cin >> index;

            // On vérifie si l'image précédente existe.
            if (index - 1 >= 0) {

                // Échange des deux images.
                int temporaire = images[index];
                images[index] = images[index - 1];
                images[index - 1] = temporaire;

                // Comptabilisation de l'échange.
                occasions++;
                repercutes += 2;
            }
        }

        // Dessin de toute la planche.
        else if (operation == "DESSINE") {

            // Chaque image présente nécessite une recherche.
            recherches += static_cast<int>(images.size());
        }
    }

    // Affichage de l'ordre final des images.
    std::cout << "ORDRE";

    if (images.empty()) {
        std::cout << " AUCUN";
    } else {
        for (int i = 0; i < static_cast<int>(images.size()); i++) {
            std::cout << " " << images[i];
        }
    }

    std::cout << "\n";

    // Affichage des compteurs.
    std::cout << "OCCASIONS " << occasions << "\n";
    std::cout << "REPERCUTES " << repercutes << "\n";
    std::cout << "RECHERCHES " << recherches << "\n";

    return 0;
}