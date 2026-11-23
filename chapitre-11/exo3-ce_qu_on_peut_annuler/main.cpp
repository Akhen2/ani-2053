#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    // Pile des opérations de l'utilisateur
    std::vector<std::string> pileUtilisateur;

    // Pile des traits que l'outil sait annuler
    std::vector<int> traitsOutil;

    // Compteur des traits dessinés
    int numeroTrait = 0;

    // Compteurs des résultats
    int justes = 0;
    int riens = 0;
    int trahis = 0;

    // Nombre total d'opérations et de traits annulables
    int operations = 0;
    int annulables = 0;

    // Numéro des demandes d'annulation
    int numeroAnnulation = 0;

    std::string ligne;

    // Lire les opérations jusqu'à la fin de l'entrée
    while (std::getline(std::cin, ligne)) {

        // Lire les éléments de la ligne
        std::stringstream lecture(ligne);

        std::string operation;
        lecture >> operation;

        // Ignorer une éventuelle ligne vide
        if (operation.empty()) {
            continue;
        }

        // TRAIT : dessiner un nouveau trait
        if (operation == "TRAIT") {
            numeroTrait++;
            operations++;
            annulables++;

            // Ajouter le trait à la pile de l'utilisateur
            std::string trait = "TRAIT " + std::to_string(numeroTrait);
            pileUtilisateur.push_back(trait);

            // Ajouter le trait à la liste de l'outil
            traitsOutil.push_back(numeroTrait);
        }

        // EFFACE : effacer tous les traits
        else if (operation == "EFFACE") {
            operations++;

            // Enregistrer l'opération pour l'utilisateur
            pileUtilisateur.push_back("EFFACE");

            // L'outil vide sa liste de traits
            traitsOutil.clear();
        }

        // RANGE : ranger toutes les images
        else if (operation == "RANGE") {
            operations++;
            pileUtilisateur.push_back("RANGE");
        }

        // Opérations qui concernent une image
        else if (operation == "DEPOSE" ||
                 operation == "DEPLACE" ||
                 operation == "SUPPRIME" ||
                 operation == "MIROIR") {

            std::string nom;
            lecture >> nom;

            operations++;

            // Enregistrer l'opération complète
            pileUtilisateur.push_back(operation + " " + nom);
        }

        // ANNULE : comparer les deux systèmes
        else if (operation == "ANNULE") {
            numeroAnnulation++;

            std::string attendu = "AUCUNE";
            std::string obtenu = "RIEN";

            // Annulation attendue par l'utilisateur
            if (!pileUtilisateur.empty()) {
                attendu = pileUtilisateur.back();
                pileUtilisateur.pop_back();
            }

            // Annulation réellement effectuée par l'outil
            if (!traitsOutil.empty()) {
                int numero = traitsOutil.back();
                traitsOutil.pop_back();

                obtenu = "TRAIT " + std::to_string(numero);
            }

            // Déterminer le verdict
            std::string verdict;

            if (attendu == obtenu) {
                verdict = "JUSTE";
                justes++;
            }
            else if (obtenu == "RIEN") {
                verdict = "RIEN";
                riens++;
            }
            else {
                verdict = "TRAHI";
                trahis++;
            }

            // Afficher le résultat de cette annulation
            std::cout << "ANNULE " << numeroAnnulation
                      << " ATTENDU " << attendu
                      << " OBTENU " << obtenu
                      << " " << verdict << "\n";
        }
    }

    // Afficher les statistiques finales
    std::cout << "JUSTES " << justes << "\n";
    std::cout << "RIENS " << riens << "\n";
    std::cout << "TRAHIS " << trahis << "\n";

    std::cout << "ANNULABLES " << annulables
              << " SUR " << operations << "\n";

    return 0;
}
