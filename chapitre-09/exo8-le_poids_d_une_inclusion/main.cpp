#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

int main() {
    int U;
    std::cin >> U;

    // Conserver les types dans leur ordre de première apparition.
    std::vector<std::string> ordreTypes;

    // Indiquer si chaque type nécessite une inclusion.
    // false : déclaration anticipée suffisante.
    // true  : définition complète nécessaire.
    std::map<std::string, bool> necessiteInclusion;

    // Lire les différents emplois.
    for (int i = 0; i < U; i++) {

        std::string type, emploi;
        std::cin >> type >> emploi;

        // Ajouter le type uniquement lors de sa première apparition.
        if (necessiteInclusion.find(type) == necessiteInclusion.end()) {

            ordreTypes.push_back(type);
            necessiteInclusion[type] = false;
        }

        // Certains emplois nécessitent la définition complète.
        if (emploi == "VALEUR" ||
            emploi == "BASE" ||
            emploi == "CORPS" ||
            emploi == "TAILLE") {

            necessiteInclusion[type] = true;
        }
    }

    // Lire les types actuellement inclus.
    int A;
    std::cin >> A;

    // Utiliser un ensemble pour éviter les doublons.
    std::set<std::string> inclusActuellement;

    for (int i = 0; i < A; i++) {

        std::string type;
        std::cin >> type;

        inclusActuellement.insert(type);
    }

    // Compteurs.
    int nombreInclure = 0;
    int nombreAnticiper = 0;
    int inclusionsRetirees = 0;

    // Afficher la décision pour chaque type.
    for (const std::string& type : ordreTypes) {

        if (necessiteInclusion[type]) {

            std::cout << type << " INCLURE" << std::endl;
            nombreInclure++;

        } else {

            std::cout << type << " ANTICIPER" << std::endl;
            nombreAnticiper++;

            // Une inclusion peut partir uniquement
            // si le type est actuellement inclus.
            if (inclusActuellement.find(type) !=
                inclusActuellement.end()) {

                inclusionsRetirees++;
            }
        }
    }

    // Afficher le bilan.
    std::cout << "INCLURE " << nombreInclure << std::endl;
    std::cout << "ANTICIPER " << nombreAnticiper << std::endl;
    std::cout << "INCLUSIONS_RETIREES " << inclusionsRetirees << std::endl;

    return 0;
}
