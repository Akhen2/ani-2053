#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Vérifie si un objet a déjà été libéré.
bool estLibere(const std::string& objet, const std::vector<std::string>& objetsLibres) {

    return std::find(objetsLibres.begin(),
                     objetsLibres.end(),
                     objet) != objetsLibres.end();
}

// Libère un objet et vérifie ses dépendances.
// Retourne false si un plantage se produit.
bool libererObjet(
    const std::string& objet,
    const std::vector<std::pair<std::string, std::string>>& dependances,
    std::vector<std::string>& objetsLibres,
    const std::string& typeLiberation
) {

    // Un objet déjà libéré ne doit pas être libéré une deuxième fois.
    if (estLibere(objet, objetsLibres)) {
        return true;
    }

    // Vérifier les dépendances dans leur ordre de lecture.
    for (const auto& dependance : dependances) {

        const std::string& a = dependance.first;
        const std::string& b = dependance.second;

        if (a == objet && estLibere(b, objetsLibres)) {
            std::cout << "PLANTAGE " << a << " " << b << '\n';
            return false;
        }
    }

    // Aucune dépendance problématique : l'objet peut être libéré.
    objetsLibres.push_back(objet);

    std::cout << typeLiberation << " " << objet << std::endl;

    return true;
}

int main() {

    // Chaque élément représente un bloc.
    // Le bloc principal existe dès le début.
    std::vector<std::vector<std::string>> blocs(1);

    // Stocker les dépendances dans l'ordre de lecture.
    std::vector<std::pair<std::string, std::string>> dependances;

    // Stocker les objets déjà libérés.
    std::vector<std::string> objetsLibres;

    std::string ligne;

    // Lire les instructions jusqu'à la fin de l'entrée.
    while (std::getline(std::cin, ligne)) {

        std::istringstream flux(ligne);

        std::string instruction;
        flux >> instruction;

        if (instruction.empty()) {
            continue;
        }

        if (instruction == "DECL") {

            std::string objet;
            flux >> objet;

            // Déclarer l'objet dans le bloc courant.
            blocs.back().push_back(objet);

        } else if (instruction == "DEPEND") {

            std::string a, b;
            flux >> a >> b;

            // Enregistrer la dépendance.
            dependances.push_back({a, b});

        } else if (instruction == "FERME") {

            std::string objet;
            flux >> objet;

            // Fermer explicitement l'objet.
            if (!libererObjet(objet, dependances, objetsLibres, "FERME")) {
                return 0;
            }

        } else if (instruction == "{") {

            // Ouvrir un nouveau bloc.
            blocs.push_back({});

        } else if (instruction == "}") {

            // Détruire les objets du bloc courant.
            for (int i = static_cast<int>(blocs.back().size()) - 1;
                 i >= 0; i--) {

                const std::string& objet = blocs.back()[i];

                if (!libererObjet(objet, dependances, objetsLibres, "DETRUIT")) {
                    return 0;
                }
            }

            // Retirer le bloc qui vient d'être fermé.
            blocs.pop_back();
        }
    }

    // À la fin de l'entrée, fermer le bloc de la fonction.
    while (!blocs.empty()) {

        // Détruire les objets du dernier bloc.
        for (int i = static_cast<int>(blocs.back().size()) - 1; i >= 0; i--) {

            const std::string& objet = blocs.back()[i];

            if (!libererObjet(objet, dependances, objetsLibres, "DETRUIT")) {
                return 0;
            }
        }

        blocs.pop_back();
    }

    // Si aucun plantage ne s'est produit.
    std::cout << "PROPRE" << std::endl;

    return 0;
}
