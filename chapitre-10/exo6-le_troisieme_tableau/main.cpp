#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Vérifie si un tableau contient un élément à un index donné.
bool indexExiste(std::vector<std::string>& tableau, int index) {
    return index >= 0 && index < static_cast<int>(tableau.size());
}

// Supprime les éléments aux index indiqués.
// Les suppressions se font du plus grand index au plus petit.
void supprimerElements(std::vector<std::string>& tableau,
                       std::vector<int>& indices) {

    for (int i = static_cast<int>(indices.size()) - 1; i >= 0; i--) {
        int index = indices[i];

        // On supprime seulement si l'index existe.
        if (indexExiste(tableau, index)) {
            tableau.erase(tableau.begin() + index);
        }
    }
}

// Échange deux éléments si les deux index existent.
void echangerElements(std::vector<std::string>& tableau,
                      int index1, int index2) {

    if (indexExiste(tableau, index1) &&
        indexExiste(tableau, index2)) {

        std::swap(tableau[index1], tableau[index2]);
    }
}

int main() {

    // Lecture des trois lignes de configuration.
    std::string ligneAjout;
    std::string ligneSuppression;
    std::string ligneEchange;

    std::getline(std::cin, ligneAjout);
    std::getline(std::cin, ligneSuppression);
    std::getline(std::cin, ligneEchange);

    // Détermination des tableaux concernés par chaque opération.
    bool ajoutTextures = false;
    bool ajoutSources = false;

    bool suppressionTextures = false;
    bool suppressionSources = false;

    bool echangeTextures = false;
    bool echangeSources = false;

    std::stringstream lecture;

    // Configuration de AJOUTE.
    lecture.str(ligneAjout);

    std::string nomTableau;

    while (lecture >> nomTableau) {
        if (nomTableau == "textures") {
            ajoutTextures = true;
        }

        if (nomTableau == "sources") {
            ajoutSources = true;
        }
    }

    // Configuration de SUPPRIME.
    lecture.clear();
    lecture.str(ligneSuppression);

    while (lecture >> nomTableau) {
        if (nomTableau == "textures") {
            suppressionTextures = true;
        }

        if (nomTableau == "sources") {
            suppressionSources = true;
        }
    }

    // Configuration de ECHANGE.
    lecture.clear();
    lecture.str(ligneEchange);

    while (lecture >> nomTableau) {
        if (nomTableau == "textures") {
            echangeTextures = true;
        }

        if (nomTableau == "sources") {
            echangeSources = true;
        }
    }

    // Création des trois tableaux.
    std::vector<std::string> modele;
    std::vector<std::string> textures;
    std::vector<std::string> sources;

    // Lecture du nombre d'opérations.
    int N;
    std::cin >> N;

    // Exécution des opérations.
    for (int i = 0; i < N; i++) {

        std::string operation;
        std::cin >> operation;

        // Opération AJOUTE.
        if (operation == "AJOUTE") {

            std::string nom;
            std::cin >> nom;

            // Le modèle reçoit toujours l'image.
            modele.push_back(nom);

            // Les autres tableaux la reçoivent seulement s'ils sont cités.
            if (ajoutTextures) {
                textures.push_back(nom);
            }

            if (ajoutSources) {
                sources.push_back(nom);
            }
        }

        // Opération SUPPRIME.
        else if (operation == "SUPPRIME") {

            int c;
            std::cin >> c;

            // Lecture des index à supprimer.
            std::vector<int> indices(c);

            for (int j = 0; j < c; j++) {
                std::cin >> indices[j];
            }

            // Suppression dans le modèle.
            supprimerElements(modele, indices);

            // Suppression dans les tableaux concernés.
            if (suppressionTextures) {
                supprimerElements(textures, indices);
            }

            if (suppressionSources) {
                supprimerElements(sources, indices);
            }
        }

        // Opération MONTE.
        else if (operation == "MONTE") {

            int index;
            std::cin >> index;

            // Vérification de l'existence de la position suivante.
            if (indexExiste(modele, index + 1)) {

                // Échange dans le modèle.
                echangerElements(modele, index, index + 1);

                // Échange dans les tableaux concernés.
                if (echangeTextures) {
                    echangerElements(textures, index, index + 1);
                }

                if (echangeSources) {
                    echangerElements(sources, index, index + 1);
                }
            }
        }

        // Opération DESCEND.
        else if (operation == "DESCEND") {

            int index;
            std::cin >> index;

            // Vérification de l'existence de la position précédente.
            if (indexExiste(modele, index - 1)) {

                // Échange dans le modèle.
                echangerElements(modele, index, index - 1);

                // Échange dans les tableaux concernés.
                if (echangeTextures) {
                    echangerElements(textures, index, index - 1);
                }

                if (echangeSources) {
                    echangerElements(sources, index, index - 1);
                }
            }
        }
    }

    // Recherche de la longueur du plus grand tableau.
    int longueur = static_cast<int>(modele.size());

    if (static_cast<int>(textures.size()) > longueur) {
        longueur = static_cast<int>(textures.size());
    }

    if (static_cast<int>(sources.size()) > longueur) {
        longueur = static_cast<int>(sources.size());
    }

    // Compteur des lignes décalées.
    int decales = 0;

    // Affichage des trois tableaux alignés.
    for (int i = 0; i < longueur; i++) {

        std::string nomModele = "-";
        std::string nomTexture = "-";
        std::string nomSource = "-";

        // Récupération des éléments s'ils existent.
        if (indexExiste(modele, i)) {
            nomModele = modele[i];
        }

        if (indexExiste(textures, i)) {
            nomTexture = textures[i];
        }

        if (indexExiste(sources, i)) {
            nomSource = sources[i];
        }

        // Affichage de la ligne.
        std::cout << i << " "
                  << nomModele << " "
                  << nomTexture << " "
                  << nomSource << "\n";

        // Vérification de l'alignement.
        if (nomModele != nomTexture ||
            nomModele != nomSource) {
            decales++;
        }
    }

    // Affichage du nombre de lignes décalées.
    std::cout << "DECALES " << decales << "\n";

    return 0;
}