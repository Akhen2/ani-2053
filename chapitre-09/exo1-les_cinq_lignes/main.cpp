#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    // Lecture du nom de la classe.
    std::string classe;
    std::getline(std::cin, classe);

    // Les cinq membres spéciaux, dans l'ordre demandé.
    const std::vector<std::string> noms = {
        "DESTRUCTEUR",
        "COPIE",
        "AFFECTATION_COPIE",
        "DEPLACEMENT",
        "AFFECTATION_DEPLACEMENT"
    };

    // Chaque membre commence avec l'état ABSENT.
    std::vector<std::string> etats(5, "ABSENT");

    std::string ligne;

    // Lecture de toutes les déclarations jusqu'à la fin de l'entrée.
    while (std::getline(std::cin, ligne)) {

        // 1. Suppression du commentaire à partir du premier //.
        std::size_t positionCommentaire = ligne.find("//");

        if (positionCommentaire != std::string::npos) {
            ligne.erase(positionCommentaire);
        }

        // 2. Suppression de toutes les espaces.
        ligne.erase(
            std::remove(ligne.begin(), ligne.end(), ' '), ligne.end()
        );

        // Une ligne vide est ignorée.
        if (ligne.empty()) {
            continue;
        }

        // 3. Détermination de l'état de la déclaration.
        std::string etat = "ECRIT";

        if (ligne.size() >= 8 &&
            ligne.compare(ligne.size() - 8, 8, "=default;") == 0) {
            etat = "DEFAUT";
        }
        else if (ligne.size() >= 8 &&
                 ligne.compare(ligne.size() - 8, 8, "=delete;") == 0) {
            etat = "SUPPRIME";
        }

        // Variable indiquant le membre reconnu.
        int membre = -1;

        // Préfixes nécessaires à la reconnaissance.
        const std::string prefixeDestructeur = "~" + classe + "(";
        const std::string prefixeCopie = classe + "(const" + classe + "&";
        const std::string prefixeAffectationCopie =
            classe + "&operator=(const" + classe + "&";
        const std::string prefixeDeplacement = classe + "(" + classe + "&&";
        const std::string prefixeAffectationDeplacement =
            classe + "&operator=(" + classe + "&&";

        // 4. Reconnaissance du destructeur.
        // Le destructeur peut apparaître n'importe où dans la ligne.
        if (ligne.find(prefixeDestructeur) != std::string::npos) {
            membre = 0;
        }

        // 5. Reconnaissance du constructeur de copie.
        // Le caractère suivant le & ne doit pas être un autre &.
        else if (ligne.compare(0, prefixeCopie.size(), prefixeCopie) == 0 &&
                 (ligne.size() == prefixeCopie.size() || ligne[prefixeCopie.size()] != '&')) {
            membre = 1;
        }

        // 6. Reconnaissance de l'affectation par copie.
        else if (ligne.compare(0, prefixeAffectationCopie.size(), prefixeAffectationCopie) == 0 &&
                 (ligne.size() == prefixeAffectationCopie.size() || ligne[prefixeAffectationCopie.size()] != '&')) {
            membre = 2;
        }

        // 7. Reconnaissance du constructeur de déplacement.
        else if (ligne.compare( 0, prefixeDeplacement.size(), prefixeDeplacement) == 0) {
            membre = 3;
        }

        // 8. Reconnaissance de l'affectation par déplacement.
        else if (ligne.compare(0, prefixeAffectationDeplacement.size(), prefixeAffectationDeplacement) == 0) {
            membre = 4;
        }

        // Si un membre est reconnu, on mémorise son état.
        if (membre != -1) {
            etats[membre] = etat;
        }
    }

    // 9. Affichage des cinq états dans l'ordre imposé.
    for (int i = 0; i < 5; i++) {
        std::cout << noms[i] << " " << etats[i] << std::endl;
    }

    // Vérification de la présence des membres.
    bool destructeur = etats[0] != "ABSENT";
    bool copie = etats[1] != "ABSENT";
    bool affectationCopie = etats[2] != "ABSENT";
    bool deplacement = etats[3] != "ABSENT";
    bool affectationDeplacement = etats[4] != "ABSENT";

    int nombreDeclares = 0;

    for (int i = 0; i < 5; i++) {
        if (etats[i] != "ABSENT") {
            nombreDeclares++;
        }
    }

    // 10. Détermination de la règle suivie par la classe.
    std::string regle;

    if (nombreDeclares == 0) {
        regle = "ZERO";
    }
    else if (nombreDeclares == 5) {
        regle = "CINQ";
    }
    else if (destructeur && copie && affectationCopie &&
             !deplacement && !affectationDeplacement) {
        regle = "TROIS";
    }
    else {
        regle = "INCOMPLETE";
    }

    std::cout << "REGLE " << regle << std::endl;

    // 11. Détermination de la propriété de la ressource.
    if (etats[0] == "ECRIT") {
        std::cout << "POSSEDE OUI" << std::endl ;
    } else {
        std::cout << "POSSEDE NON" << std::endl;
    }

    // 12. Détermination du caractère unique de la ressource.
    if (etats[1] == "SUPPRIME" &&
        (etats[3] == "ECRIT" || etats[3] == "DEFAUT")) {
        std::cout << "UNIQUE OUI" << std::endl;
    } else {
        std::cout << "UNIQUE NON" << std::endl;
    }

    // 13. Affichage des membres manquants si la règle est incomplète.
    if (regle == "INCOMPLETE") {

        // Si au moins un déplacement est déclaré, on examine
        // les cinq membres. Sinon, on examine seulement les trois premiers.
        int limite = (deplacement || affectationDeplacement) ? 5 : 3;

        for (int i = 0; i < limite; i++) {
            if (etats[i] == "ABSENT") {
                std::cout << "MANQUE " << noms[i] << std::endl;
            }
        }
    }

    return 0;
}
