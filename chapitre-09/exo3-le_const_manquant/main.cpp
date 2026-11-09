#include <iostream>
#include <string>
#include <vector>

int main() {
    // Lecture du nombre de méthodes.
    int N;
    std::cin >> N;

    // Informations sur chaque méthode.
    std::vector<std::string> noms(N);
    std::vector<std::string> declarations(N);
    std::vector<int> modifie(N);
    std::vector<std::vector<int>> appels(N);

    // Lecture des méthodes et de leurs appels.
    for (int i = 0; i < N; i++) {
        int k;

        std::cin >> noms[i]
                 >> declarations[i]
                 >> modifie[i]
                 >> k;

        // Lecture des méthodes appelées.
        for (int j = 0; j < k; j++) {
            std::string nomAppelee;
            std::cin >> nomAppelee;

            // Recherche de l'indice de la méthode appelée.
            for (int m = 0; m < N; m++) {
                if (noms[m] == nomAppelee) {
                    appels[i].push_back(m);
                    break;
                }
            }
        }
    }

    // Indique si une méthode peut devenir const.
    std::vector<bool> pourrait(N, false);

    // Étape 1 : déterminer les méthodes qui pourraient être const.
    // Une méthode doit :
    // - ne pas modifier directement l'objet ;
    // - n'appeler aucune méthode qui ne pourrait pas être const.
    for (int i = 0; i < N; i++) {

        // Une méthode qui modifie l'objet ne peut pas être const.
        if (modifie[i] == 1) {
            continue;
        }

        bool valide = true;

        // Vérification de toutes les méthodes appelées.
        for (int indice : appels[i]) {

            // Une méthode déjà déclarée const est acceptable.
            if (declarations[indice] == "const") {
                continue;
            }

            // Une méthode non const doit elle-même pouvoir le devenir.
            if (modifie[indice] == 1) {
                valide = false;
                break;
            }
        }

        // La méthode peut devenir const si toutes ses dépendances
        // sont déclarées const ou ne modifient pas directement l'objet.
        if (valide) {
            pourrait[i] = true;
        }
    }

    // Étape 2 : afficher la liste POURRAIT.
    std::cout << "POURRAIT";

    bool existePourrait = false;

    for (int i = 0; i < N; i++) {
        if (pourrait[i] && declarations[i] != "const") {
            std::cout << " " << noms[i];
            existePourrait = true;
        }
    }

    if (!existePourrait) {
        std::cout << " AUCUN";
    }

    std::cout << std::endl;

    // Étape 3 : déterminer les racines.
    // Une racine n'appelle que des méthodes déjà déclarées const.
    std::cout << "RACINES";

    bool existeRacine = false;

    for (int i = 0; i < N; i++) {
        if (!pourrait[i] || declarations[i] == "const") {
            continue;
        }

        bool racine = true;

        for (int indice : appels[i]) {
            if (declarations[indice] != "const") {
                racine = false;
                break;
            }
        }

        if (racine) {
            std::cout << " " << noms[i];
            existeRacine = true;
        }
    }

    if (!existeRacine) {
        std::cout << " AUCUN";
    }

    std::cout << std::endl;

    // Étape 4 : calculer le nombre de passes.
    // Les méthodes déjà déclarées const sont considérées comme corrigées.
    std::vector<bool> estConst(N, false);

    for (int i = 0; i < N; i++) {
        if (declarations[i] == "const") {
            estConst[i] = true;
        }
    }

    // Nombre de méthodes qui doivent encore devenir const.
    int restantes = 0;

    for (int i = 0; i < N; i++) {
        if (pourrait[i] && !estConst[i]) {
            restantes++;
        }
    }

    int passes = 0;

    // Chaque passage corrige simultanément les méthodes
    // dont toutes les méthodes appelées sont déjà const.
    while (restantes > 0) {

        // On mémorise les méthodes à corriger pendant cette passe.
        std::vector<int> aCorriger;

        for (int i = 0; i < N; i++) {
            if (!pourrait[i] || estConst[i]) {
                continue;
            }

            bool toutesConst = true;

            // Toutes les méthodes appelées doivent déjà être const.
            for (int indice : appels[i]) {
                if (!estConst[indice]) {
                    toutesConst = false;
                    break;
                }
            }

            if (toutesConst) {
                aCorriger.push_back(i);
            }
        }

        // Aucune méthode ne peut être corrigée :
        // cela ne devrait pas arriver puisque l'entrée garantit
        // l'absence de cycles et que les méthodes candidates sont valides.
        if (aCorriger.empty()) {
            break;
        }

        // Application simultanée des corrections.
        for (int indice : aCorriger) {
            estConst[indice] = true;
            restantes--;
        }

        passes++;
    }

    // Affichage du nombre total de passes.
    std::cout << "PASSES " << passes << std::endl;

    return 0;
}
