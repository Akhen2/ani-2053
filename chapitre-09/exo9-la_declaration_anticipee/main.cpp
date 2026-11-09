#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

// Vérifie si un fichier possède une extension donnée.
bool terminePar(const std::string& fichier, const std::string& extension) {

    if (fichier.size() < extension.size()) {
        return false;
    }

    return fichier.compare(
        fichier.size() - extension.size(),
        extension.size(),
        extension
    ) == 0;
}

// Parcours en profondeur des fichiers dépendant d'un fichier.
void parcourir(const std::string& fichier, const std::map<std::string, std::vector<std::string>>& dependants, std::set<std::string>& visites, std::set<std::string>& cppTrouves) {

    // Éviter de visiter deux fois le même fichier.
    if (visites.find(fichier) != visites.end()) {
        return;
    }

    visites.insert(fichier);

    // Si le fichier est un .cpp, il doit être recompilé.
    if (terminePar(fichier, ".cpp")) {
        cppTrouves.insert(fichier);
    }

    // Explorer les fichiers qui incluent ce fichier.
    auto it = dependants.find(fichier);

    if (it != dependants.end()) {

        for (const std::string& suivant : it->second) {
            parcourir(suivant, dependants,
                      visites, cppTrouves);
        }
    }
}

int main() {
    int N;
    std::cin >> N;

    // Conserver les fichiers dans leur ordre de lecture.
    std::vector<std::string> fichiers;

    // Graphe inversé :
    // clé = fichier inclus
    // valeur = fichiers qui l'incluent.
    std::map<std::string, std::vector<std::string>> dependants;

    // Lire les fichiers et leurs inclusions.
    for (int i = 0; i < N; i++) {

        std::string fichier;
        int k;

        std::cin >> fichier >> k;

        fichiers.push_back(fichier);

        for (int j = 0; j < k; j++) {

            std::string inclusion;
            std::cin >> inclusion;

            // Ajouter uniquement les relations.
            // Les fichiers inconnus seront ignorés
            // lors de la recherche.
            dependants[inclusion].push_back(fichier);
        }
    }

    // Lire les questions.
    int Q;
    std::cin >> Q;

    std::vector<std::string> questions(Q);

    for (int i = 0; i < Q; i++) {
        std::cin >> questions[i];
    }

    // Calculer le nombre de .cpp à recompiler
    // pour chaque fichier .h.
    std::string fichierPlusLourd = "AUCUN";
    int maximum = -1;

    for (const std::string& fichier : fichiers) {

        if (!terminePar(fichier, ".h")) {
            continue;
        }

        std::set<std::string> visites;
        std::set<std::string> cppTrouves;

        parcourir(fichier, dependants, visites, cppTrouves);

        int nombre = static_cast<int>(cppTrouves.size());

        // Utiliser strictement > pour conserver
        // le premier fichier en cas d'égalité.
        if (nombre > maximum) {
            maximum = nombre;
            fichierPlusLourd = fichier;
        }
    }

    // Répondre aux questions dans leur ordre.
    for (const std::string& fichier : questions) {

        std::set<std::string> visites;
        std::set<std::string> cppTrouves;

        parcourir(fichier, dependants, visites, cppTrouves);

        std::cout << fichier << " " << cppTrouves.size() << std::endl;
    }

    // Afficher le fichier .h le plus coûteux.
    if (fichierPlusLourd == "AUCUN") {

        std::cout << "PLUS_LOURD AUCUN" << std::endl;

    } else {

        std::cout << "PLUS_LOURD " << fichierPlusLourd << " " << maximum << std::endl;
    }

    return 0;
}
