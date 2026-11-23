#include <iostream>
#include <string>
#include <vector>
#include <set>

// Représente un commit
struct Commit {
    std::string hash;
    std::string action;
    std::vector<std::string> fonctions;
};

// Représente une annonce
struct Annonce {
    std::string hash;
    std::string etat;
    std::string fonction;
    int numeroCommit;
};

// Vérifie si une annonce est vraie dans un état donné
bool annonceVraie(const Annonce& annonce,
                  const std::set<std::string>& fonctions) {

    bool presente = fonctions.find(annonce.fonction) != fonctions.end();

    if (annonce.etat == "A_VENIR") {
        return !presente;
    }

    return presente;
}

int main() {
    int H;
    std::cin >> H;

    // Stocker tous les commits
    std::vector<Commit> commits(H);

    for (int i = 0; i < H; i++) {
        std::cin >> commits[i].hash;
        std::cin >> commits[i].action;

        int k;
        std::cin >> k;

        // Lire les fonctions concernées par le commit
        for (int j = 0; j < k; j++) {
            std::string fonction;
            std::cin >> fonction;

            commits[i].fonctions.push_back(fonction);
        }
    }

    // Lire les annonces
    int A;
    std::cin >> A;

    std::vector<Annonce> annonces(A);

    for (int i = 0; i < A; i++) {
        std::cin >> annonces[i].hash;
        std::cin >> annonces[i].etat;
        std::cin >> annonces[i].fonction;

        // Retrouver le numéro du commit où l'annonce a été écrite
        annonces[i].numeroCommit = -1;

        for (int j = 0; j < H; j++) {
            if (commits[j].hash == annonces[i].hash) {
                annonces[i].numeroCommit = j;
                break;
            }
        }
    }

    // Enregistrer l'état des fonctions après chaque commit
    std::vector<std::set<std::string>> historique;

    std::set<std::string> fonctionsPresentes;

    for (int i = 0; i < H; i++) {

        // Appliquer les changements du commit
        for (int j = 0;
             j < static_cast<int>(commits[i].fonctions.size());
             j++) {

            std::string fonction = commits[i].fonctions[j];

            if (commits[i].action == "AJOUTE") {
                fonctionsPresentes.insert(fonction);
            } else {
                fonctionsPresentes.erase(fonction);
            }
        }

        // Conserver une copie de l'état après ce commit
        historique.push_back(fonctionsPresentes);
    }

    // Vérifier chaque annonce
    int mensonges = 0;

    for (int i = 0; i < A; i++) {

        int numeroEcriture = annonces[i].numeroCommit;

        // Vérifier si l'annonce est vraie au dernier commit
        if (annonceVraie(annonces[i], historique[H - 1])) {
            std::cout << "ANNONCE " << i + 1 << " VRAI\n";
        } else {
            mensonges++;

            // Remonter depuis le dernier commit
            int debutMensonge = H - 1;

            while (debutMensonge > numeroEcriture &&
                   !annonceVraie(annonces[i],
                                 historique[debutMensonge - 1])) {
                debutMensonge--;
            }

            // Afficher le commit depuis lequel l'annonce ment
            std::cout << "ANNONCE " << i + 1 << " MENT "
                      << commits[debutMensonge].hash << "\n";
        }
    }

    // Afficher le nombre total de mensonges
    std::cout << "MENSONGES " << mensonges << "\n";

    return 0;
}