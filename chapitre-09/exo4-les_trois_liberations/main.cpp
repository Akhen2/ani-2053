#include <iostream>
#include <vector>
#include <string>

// Libère une texture un certain nombre de fois.
// Retourne false si une double libération provoque un plantage.
bool libererTexture(int texture, int nombre, std::vector<bool>& liberees) {

    for (int i = 0; i < nombre; i++) {

        // Vérifier si la texture a déjà été libérée.
        if (liberees[texture]) {
            return false;
        }

        // Marquer la texture comme libérée.
        liberees[texture] = true;
    }

    return true;
}

int main() {
    int S, V, F;

    // Lire le nombre de libérations à chaque emplacement.
    std::cin >> S >> V >> F;

    int N;
    std::cin >> N;

    // Tableau des textures encore présentes.
    std::vector<int> tableau;

    // État de chaque texture : true si elle est libérée.
    // L'indice 0 est inutilisé : les textures commencent à 1.
    std::vector<bool> liberees(1, false);

    int creees = 0;

    // Lire et exécuter les opérations.
    for (int k = 1; k <= N; k++) {
        std::string operation;
        std::cin >> operation;

        if (operation == "AJOUTE") {

            // Créer une nouvelle texture.
            creees++;

            // Une nouvelle texture n'est pas encore libérée.
            liberees.push_back(false);

            // Ajouter son numéro à la fin du tableau.
            tableau.push_back(creees);

        } else if (operation == "SUPPRIME") {

            int index;
            std::cin >> index;

            // Récupérer le numéro de la texture à supprimer.
            int texture = tableau[index];

            // Libérer la texture S fois.
            if (!libererTexture(texture, S, liberees)) {
                std::cout << "PLANTAGE " << k << " TEXTURE " << texture << std::endl;
                return 0;
            }

            // Retirer la texture du tableau.
            // Les éléments suivants reculent automatiquement.
            tableau.erase(tableau.begin() + index);

        } else if (operation == "VIDE") {

            // Parcourir le tableau du premier au dernier.
            for (int texture : tableau) {

                // Libérer chaque texture V fois.
                if (!libererTexture(texture, V, liberees)) {
                    std::cout << "PLANTAGE " << k << " TEXTURE " << texture << std::endl;
                    return 0;
                }
            }

            // Toutes les textures ont été retirées du tableau.
            tableau.clear();
        }
    }

    // Simuler la fin du programme.
    for (int texture : tableau) {

        // Libérer chaque texture F fois.
        if (!libererTexture(texture, F, liberees)) {
            std::cout << "PLANTAGE FIN TEXTURE " << texture << std::endl;
            return 0;
        }
    }

    // Compter les textures qui n'ont jamais été libérées.
    int fuites = 0;
    std::vector<int> perdues;

    for (int i = 1; i <= creees; i++) {

        if (!liberees[i]) {
            fuites++;
            perdues.push_back(i);
        }
    }

    // Afficher les résultats.
    std::cout << "CREEES " << creees << std::endl;
    std::cout << "FUITES " << fuites << std::endl;

    std::cout << "PERDUES";

    if (perdues.empty()) {
        std::cout << " AUCUN";
    } else {
        for (int texture : perdues) {
            std::cout << " " << texture;
        }
    }

    std::cout << std::endl;

    return 0;
}