[22/11/2026 11:25] Akhen Aristide: #include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdlib>

// Découper une chaîne avec un séparateur
std::vector<std::string> decouper(const std::string& texte, char separateur) {
    std::vector<std::string> resultat;
    std::string morceau;
    std::stringstream lecture(texte);

    while (std::getline(lecture, morceau, separateur)) {
        resultat.push_back(morceau);
    }

    // Conserver le dernier champ s'il est vide
    if (!texte.empty() && texte.back() == separateur) {
        resultat.push_back("");
    }

    return resultat;
}

// Vérifier qu'une chaîne contient un entier valide
bool estEntier(const std::string& texte) {
    if (texte.empty()) {
        return false;
    }

    char* fin;
    std::strtoll(texte.c_str(), &fin, 10);

    return *fin == '\0';
}

// Vérifier qu'une chaîne contient un nombre valide
bool estNombre(const std::string& texte) {
    if (texte.empty()) {
        return false;
    }

    char* fin;
    std::strtod(texte.c_str(), &fin);

    return *fin == '\0';
}

// Informations des événements d'un tour
struct Tour {
    std::vector<std::string> pan;
    std::vector<std::string> zoom;
    std::vector<std::string> depots;
    std::vector<std::string> clics;
    std::vector<std::string> move;
    std::vector<std::string> range;
    std::vector<std::string> grille;
    std::vector<std::string> captures;
};

int main() {
    // Les événements sont rangés par numéro de tour
    std::map<long long, Tour> tours;

    // Nombre d'événements correctement enregistrés
    long long totalGardes = 0;

    // Nombre de valeurs ou éléments ignorés
    long long ignores = 0;

    // Sortie prévue
    long long sortie = 0;

    // Lire les variables d'environnement
    std::string ligne;

    while (std::getline(std::cin, ligne)) {
        std::size_t position = ligne.find('=');

        // Une ligne sans signe égal est ignorée
        if (position == std::string::npos) {
            ignores++;
            continue;
        }

        std::string nom = ligne.substr(0, position);
        std::string valeur = ligne.substr(position + 1);

        // CAPTURES
        if (nom == "NK_AGENT_SHOT") {
            std::vector<std::string> elements = decouper(valeur, ',');

            int gardes = 0;

            for (int i = 0; i < static_cast<int>(elements.size()); i++) {
                if (!estEntier(elements[i])) {
                    ignores++;
                    continue;
                }

                if (gardes >= 8) {
                    ignores++;
                    continue;
                }

                long long n = std::stoll(elements[i]);

                if (n <= 0) {
                    // La capture est valide, mais ne pourra jamais arriver
                    totalGardes++;
                } else {
                    // Une capture de trame n arrive après le tour n - 1
                    tours[n - 1].captures.push_back("CAPTURE");
                    totalGardes++;
                }

                gardes++;
            }
        }

        // SORTIE
        else if (nom == "NK_AGENT_EXIT") {
            if (!estEntier(valeur)) {
                ignores++;
            } else {
                sortie = std::stoll(valeur);
            }
        }

        // PAN
        else if (nom == "NK_AGENT_PAN") {
            std::vector<std::string> champs = decouper(valeur, ':');

            if (champs.size() < 3 ||
                !estEntier(champs[0]) ||
                !estNombre(champs[1]) ||
                !estNombre(champs[2])) {
                ignores++;
                continue;
            }

            long long n = std::stoll(champs[0]);
            totalGardes++;

            if (n > 0) {
                tours[n].pan.push_back(
                    "PAN " + champs[1] + " " + champs[2]
                );
            }
        }

        // ZOOM
        else if (nom == "NK_AGENT_ZOOM") {
            std::vector<std::string> champs = decouper(valeur, ':');
[22/11/2026 11:25] Akhen Aristide: if (champs.size() < 4 ||
                !estEntier(champs[0]) ||
                !estNombre(champs[1]) ||
                !estNombre(champs[2]) ||
                !estNombre(champs[3])) {
                ignores++;
                continue;
            }

            long long n = std::stoll(champs[0]);
            totalGardes++;

            if (n > 0) {
                tours[n].zoom.push_back(
                    "ZOOM " + champs[1] + " " +
                    champs[2] + " " + champs[3]
                );
            }
        }

        // DEPOTS
        else if (nom == "NK_AGENT_DROP") {
            std::vector<std::string> elements = decouper(valeur, ';');

            int gardes = 0;

            for (int i = 0; i < static_cast<int>(elements.size()); i++) {
                std::size_t p1 = elements[i].find(':');
                std::size_t p2 = elements[i].find(':', p1 == std::string::npos ? p1 : p1 + 1);
                std::size_t p3 = elements[i].find(':', p2 == std::string::npos ? p2 : p2 + 1);

                if (p1 == std::string::npos ||
                    p2 == std::string::npos ||
                    p3 == std::string::npos) {
                    ignores++;
                    continue;
                }

                std::string nTexte = elements[i].substr(0, p1);
                std::string px = elements[i].substr(p1 + 1, p2 - p1 - 1);
                std::string py = elements[i].substr(p2 + 1, p3 - p2 - 1);
                std::string chemin = elements[i].substr(p3 + 1);

                if (!estEntier(nTexte) ||
                    !estNombre(px) ||
                    !estNombre(py) ||
                    chemin.empty()) {
                    ignores++;
                    continue;
                }

                if (gardes >= 8) {
                    ignores++;
                    continue;
                }

                long long n = std::stoll(nTexte);
                totalGardes++;
                gardes++;

                if (n > 0) {
                    tours[n].depots.push_back(
                        "DEPOT " + chemin + " " + px + " " + py
                    );
                }
            }
        }

        // CLICS
        else if (nom == "NK_AGENT_CLICK") {
            std::vector<std::string> elements = decouper(valeur, ';');

            int gardes = 0;

            for (int i = 0; i < static_cast<int>(elements.size()); i++) {
                std::vector<std::string> champs = decouper(elements[i], ':');

                if (champs.size() < 3 ||
                    !estEntier(champs[0]) ||
                    !estNombre(champs[1]) ||
                    !estNombre(champs[2])) {
                    ignores++;
                    continue;
                }

                if (gardes >= 8) {
                    ignores++;
                    continue;
                }

                long long n = std::stoll(champs[0]);
                totalGardes++;
                gardes++;

                if (n > 0) {
                    tours[n].clics.push_back(
                        "CLIC " + champs[1] + " " + champs[2]
                    );
                }
            }
        }

        // MOVE
        else if (nom == "NK_AGENT_MOVE") {
            std::vector<std::string> champs = decouper(valeur, ':');

            if (champs.size() < 3 ||
                !estEntier(champs[0]) ||
                !estNombre(champs[1]) ||
                !estNombre(champs[2])) {
                ignores++;
                continue;
            }

            long long n = std::stoll(champs[0]);
            totalGardes++;

            if (n > 0) {
                tours[n].move.push_back(
                    "MOVE " + champs[1] + " " + champs[2]
                );
            }
        }

        // PACK
        else if (nom == "NK_AGENT_PACK") {
            if (!estEntier(valeur)) {
                ignores++;
                continue;
            }

            long long n = std::stoll(valeur);
            totalGardes++;
[22/11/2026 11:25] Akhen Aristide: if (n > 0) {
                tours[n].range.push_back("RANGE");
            }
        }

        // GRID
        else if (nom == "NK_AGENT_GRID") {
            std::vector<std::string> champs = decouper(valeur, ':');

            if (champs.size() < 2 ||
                !estEntier(champs[0])) {
                ignores++;
                continue;
            }

            long long n = std::stoll(champs[0]);
            totalGardes++;

            if (n > 0) {
                tours[n].grille.push_back("GRILLE " + champs[1]);
            }
        }

        // Nom de variable inconnu
        else {
            ignores++;
        }
    }

    // Déterminer le dernier tour joué
    long long dernierTour = -1;

    if (sortie > 0) {
        dernierTour = sortie - 1;
    } else if (!tours.empty()) {
        dernierTour = tours.rbegin()->first;
    }

    // Compter les événements réellement exécutés
    long long executes = 0;

    // Parcourir les tours dans l'ordre
    for (auto it = tours.begin(); it != tours.end(); ++it) {
        long long t = it->first;

        if (t > dernierTour) {
            break;
        }

        Tour& tour = it->second;

        // PAN
        for (int i = 0; i < static_cast<int>(tour.pan.size()); i++) {
            std::cout << "TOUR " << t << " " << tour.pan[i] << "\n";
            executes++;
        }

        // ZOOM
        for (int i = 0; i < static_cast<int>(tour.zoom.size()); i++) {
            std::cout << "TOUR " << t << " " << tour.zoom[i] << "\n";
            executes++;
        }

        // DEPOTS
        for (int i = 0; i < static_cast<int>(tour.depots.size()); i++) {
            std::cout << "TOUR " << t << " " << tour.depots[i] << "\n";
            executes++;
        }

        // CLICS
        for (int i = 0; i < static_cast<int>(tour.clics.size()); i++) {
            std::cout << "TOUR " << t << " " << tour.clics[i] << "\n";
            executes++;
        }

        // MOVE
        for (int i = 0; i < static_cast<int>(tour.move.size()); i++) {
            std::cout << "TOUR " << t << " " << tour.move[i] << "\n";
            executes++;
        }

        // RANGE
        for (int i = 0; i < static_cast<int>(tour.range.size()); i++) {
            std::cout << "TOUR " << t << " " << tour.range[i] << "\n";
            executes++;
        }

        // GRILLE
        for (int i = 0; i < static_cast<int>(tour.grille.size()); i++) {
            std::cout << "TOUR " << t << " " << tour.grille[i] << "\n";
            executes++;
        }

        // CAPTURES : elles arrivent après les actions du tour
        for (int i = 0; i < static_cast<int>(tour.captures.size()); i++) {
            std::cout << "TOUR " << t << " CAPTURE\n";
            executes++;
        }
    }

    // Afficher l'arrêt
    if (sortie > 0) {
        std::cout << "ARRET " << dernierTour << "\n";
    } else {
        std::cout << "SANS_ARRET\n";
    }

    // Les événements gardés mais non exécutés
    long long jamais = totalGardes - executes;

    std::cout << "JAMAIS " << jamais << "\n";
    std::cout << "IGNORES " << ignores << "\n";

    return 0;
}
