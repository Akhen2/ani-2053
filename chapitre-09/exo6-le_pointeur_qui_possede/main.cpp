#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

// Libère l'objet détenu par une variable.
// Si la variable est nulle, aucune action n'est effectuée.
void detruireObjet(const std::string& variable, std::map<std::string, int>& proprietaires, int& nombreDetruits
) {
    if (proprietaires[variable] != 0) {

        // Récupérer le numéro de l'objet.
        int objet = proprietaires[variable];

        // Afficher la destruction.
        std::cout << "DETRUIT " << objet << std::endl;

        // La variable devient nulle.
        proprietaires[variable] = 0;

        // Incrémenter le compteur.
        nombreDetruits++;
    }
}

int main() {
    int N;
    std::cin >> N;

    // Consommer le retour à la ligne après N.
    std::cin.ignore();

    // Stocker les instructions du programme.
    std::vector<std::string> instructions;

    // Stocker les numéros des lignes COPY.
    std::vector<int> lignesCopy;

    // Première lecture : détecter les COPY.
    for (int i = 1; i <= N; i++) {

        std::string ligne;
        std::getline(std::cin, ligne);

        instructions.push_back(ligne);

        std::istringstream flux(ligne);
        std::string commande;
        flux >> commande;

        if (commande == "COPY") {
            lignesCopy.push_back(i);
        }
    }

    // Si au moins un COPY existe, refuser le programme.
    if (!lignesCopy.empty()) {

        for (int numero : lignesCopy) {
            std::cout << "REFUSE " << numero << std::endl;
        }

        return 0;
    }

    // Associer chaque variable à son objet.
    // 0 signifie que la variable est nulle.
    std::map<std::string, int> proprietaires;

    // Mémoriser l'ordre de première apparition des variables.
    std::vector<std::string> ordreVariables;

    // Compteurs.
    int nombreCrees = 0;
    int nombreDetruits = 0;
    int nombreNuls = 0;

    // Enregistrer une variable lors de sa première apparition.
    auto enregistrerVariable = [&](const std::string& nom) {

        if (proprietaires.find(nom) == proprietaires.end()) {

            proprietaires[nom] = 0;
            ordreVariables.push_back(nom);
        }
    };

    // Deuxième lecture : exécuter les instructions.
    for (int i = 0; i < N; i++) {

        std::istringstream flux(instructions[i]);

        std::string commande;
        std::string a, b;

        flux >> commande;

        if (commande == "NEW") {

            flux >> a;
            enregistrerVariable(a);

            // Créer un nouvel objet.
            nombreCrees++;

            // Détruire l'ancien objet de a, s'il existe.
            detruireObjet(a, proprietaires, nombreDetruits);

            // Attribuer le nouvel objet à a.
            proprietaires[a] = nombreCrees;

        } else if (commande == "MOVE") {

            flux >> a >> b;

            enregistrerVariable(a);
            enregistrerVariable(b);

            // Récupérer l'objet détenu par la source.
            int objet = proprietaires[a];

            // La source devient nulle.
            proprietaires[a] = 0;

            // Détruire l'ancien objet de la destination.
            detruireObjet(b, proprietaires, nombreDetruits);

            // La destination reçoit l'objet de la source.
            proprietaires[b] = objet;

        } else if (commande == "RESET") {

            flux >> a;
            enregistrerVariable(a);

            // Détruire l'objet détenu par a.
            detruireObjet(a, proprietaires, nombreDetruits);

        } else if (commande == "USE") {

            flux >> a;
            enregistrerVariable(a);

            // Vérifier si la variable est nulle.
            if (proprietaires[a] == 0) {

                std::cout << "NUL " << i + 1 << " " << a << std::endl;

                nombreNuls++;
            }
        }
    }

    // Fin du programme :
    // détruire les variables dans l'ordre inverse
    // de leur première apparition.
    for (int i = static_cast<int>(ordreVariables.size()) - 1; i >= 0; i--) {

        const std::string& variable = ordreVariables[i];

        detruireObjet(variable, proprietaires, nombreDetruits);
    }

    // Afficher le bilan final.
    std::cout << "CREES " << nombreCrees << std::endl;
    std::cout << "DETRUITS " << nombreDetruits << std::endl;
    std::cout << "NULS " << nombreNuls << std::endl;

    return 0;
}
