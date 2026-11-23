#include <iostream>
#include <string>
#include <vector>

// Vérifie si une clé existe dans une liste
bool contient(const std::vector<std::string>& liste,
              const std::string& cle) {
    for (int i = 0; i < static_cast<int>(liste.size()); i++) {
        if (liste[i] == cle) {
            return true;
        }
    }

    return false;
}

int main() {
    int n, c, a;

    // Lire la liste AVANT
    std::string mot;
    std::cin >> mot >> n;

    std::vector<std::string> avant(n);

    for (int i = 0; i < n; i++) {
        std::cin >> avant[i];
    }

    // Lire la liste CORRIGE
    std::cin >> mot >> c;

    std::vector<std::string> corrige(c);

    for (int i = 0; i < c; i++) {
        std::cin >> corrige[i];
    }

    // Lire la liste APRES
    std::cin >> mot >> a;

    std::vector<std::string> apres(a);

    for (int i = 0; i < a; i++) {
        std::cin >> apres[i];
    }

    // Compteurs des différentes catégories
    int vraies = 0;
    int fausses = 0;
    int oubliees = 0;
    int nouvelles = 0;

    // Parcourir la liste AVANT dans son ordre initial
    for (int i = 0; i < n; i++) {
        std::string categorie;

        // Priorité 1 : la clé a été corrigée
        if (contient(corrige, avant[i])) {
            categorie = "DEVENUE_FAUSSE";
            fausses++;
        }

        // Priorité 2 : la clé est toujours présente
        else if (contient(apres, avant[i])) {
            categorie = "ENCORE_VRAIE";
            vraies++;
        }

        // Priorité 3 : la clé a été oubliée
        else {
            categorie = "OUBLIEE";
            oubliees++;
        }

        // Afficher le numéro, la clé et sa catégorie
        std::cout << i + 1 << " "
                  << avant[i] << " "
                  << categorie << "\n";
    }

    // Compter les nouvelles clés présentes dans APRES
    for (int i = 0; i < a; i++) {
        if (!contient(avant, apres[i])) {
            nouvelles++;
        }
    }

    // Calculer la part oubliée
    int partOubliee = 0;

    if (vraies + oubliees != 0) {
        partOubliee = (100 * oubliees) / (vraies + oubliees);
    }

    // Afficher les cinq résultats finaux
    std::cout << "VRAIES " << vraies << "\n";
    std::cout << "FAUSSES " << fausses << "\n";
    std::cout << "OUBLIEES " << oubliees << "\n";
    std::cout << "NOUVELLES " << nouvelles << "\n";
    std::cout << "PART_OUBLIEE " << partOubliee << "\n";

    return 0;
}