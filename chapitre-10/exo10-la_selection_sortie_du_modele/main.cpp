#include <iostream>
#include <string>
#include <vector>

// Représente une image pour la conception DANS_ITEM
struct Image {
    std::string nom;
    bool selectionnee;
};

// Vérifie si un indice existe dans une planche
bool indiceValide(int indice, int taille) {
    return indice >= 0 && indice < taille;
}

// Vérifie si une valeur existe dans une liste
bool contient(const std::vector<int>& liste, int valeur) {
    for (int i = 0; i < static_cast<int>(liste.size()); i++) {
        if (liste[i] == valeur) {
            return true;
        }
    }
    return false;
}

// Vérifie si un nom existe dans une liste
bool contientNom(const std::vector<std::string>& liste,
                 const std::string& nom) {
    for (int i = 0; i < static_cast<int>(liste.size()); i++) {
        if (liste[i] == nom) {
            return true;
        }
    }
    return false;
}

// Affiche une planche
void afficherPlanche(const std::string& conception,
                     const std::vector<std::string>& planche) {
    std::cout << conception << " PLANCHE";

    if (planche.empty()) {
        std::cout << " AUCUN";
    } else {
        for (int i = 0; i < static_cast<int>(planche.size()); i++) {
            std::cout << " " << planche[i];
        }
    }

    std::cout << "\n";
}

// Affiche les images sélectionnées, dans l'ordre de la planche
void afficherSelection(const std::string& conception,
                       const std::vector<std::string>& planche,
                       const std::vector<bool>& selection) {
    std::cout << conception << " SELECTION";

    bool vide = true;

    for (int i = 0; i < static_cast<int>(planche.size()); i++) {
        if (selection[i]) {
            std::cout << " " << planche[i];
            vide = false;
        }
    }

    if (vide) {
        std::cout << " AUCUN";
    }

    std::cout << "\n";
}

int main() {
    // Planche de la conception DANS_ITEM
    std::vector<Image> dansItem;

    // Planche de la conception PAR_INDEX
    std::vector<std::string> plancheIndex;
    std::vector<int> selectionIndex;

    // Planche de la conception PAR_ID
    std::vector<std::string> plancheId;
    std::vector<std::string> selectionId;

    std::string operation;

    // Lire les opérations jusqu'à la fin de l'entrée
    while (std::cin >> operation) {

        if (operation == "AJOUTE") {
            std::string nom;
            std::cin >> nom;

            // DANS_ITEM : nouvelle image non sélectionnée
            Image nouvelle;
            nouvelle.nom = nom;
            nouvelle.selectionnee = false;
            dansItem.push_back(nouvelle);

            // PAR_INDEX
            plancheIndex.push_back(nom);

            // PAR_ID
            plancheId.push_back(nom);
        }

        else if (operation == "CLIC") {
            int indice;
            std::cin >> indice;

            // DANS_ITEM : vider la sélection
            for (int i = 0; i < static_cast<int>(dansItem.size()); i++) {
                dansItem[i].selectionnee = false;
            }

            // Puis sélectionner l'image si l'indice existe
            if (indiceValide(indice, static_cast<int>(dansItem.size()))) {
                dansItem[indice].selectionnee = true;
            }

            // PAR_INDEX : vider puis garder l'indice
            selectionIndex.clear();

            if (indiceValide(indice, static_cast<int>(plancheIndex.size()))) {
                selectionIndex.push_back(indice);
            }

            // PAR_ID : vider puis garder le nom
            selectionId.clear();

            if (indiceValide(indice, static_cast<int>(plancheId.size()))) {
                selectionId.push_back(plancheId[indice]);
            }
        }

        else if (operation == "AJOUTE_SEL") {
            int indice;
            std::cin >> indice;

            // DANS_ITEM : ajouter l'image à la sélection
            if (indiceValide(indice, static_cast<int>(dansItem.size()))) {
                dansItem[indice].selectionnee = true;
            }

            // PAR_INDEX : ajouter l'indice s'il n'est pas déjà présent
            if (indiceValide(indice, static_cast<int>(plancheIndex.size()))) {
                if (!contient(selectionIndex, indice)) {
                    selectionIndex.push_back(indice);
                }
            }

            // PAR_ID : ajouter le nom s'il n'est pas déjà présent
            if (indiceValide(indice, static_cast<int>(plancheId.size()))) {
                std::string nom = plancheId[indice];

                if (!contientNom(selectionId, nom)) {
                    selectionId.push_back(nom);
                }
            }
        }

        else if (operation == "ECHANGE") {
            int i, j;
            std::cin >> i >> j;

            // DANS_ITEM : échanger les images avec leurs drapeaux
            if (indiceValide(i, static_cast<int>(dansItem.size())) &&
                indiceValide(j, static_cast<int>(dansItem.size()))) {
                Image temporaire = dansItem[i];
                dansItem[i] = dansItem[j];
                dansItem[j] = temporaire;
            }

            // PAR_INDEX : échanger seulement les images
            // Les indices sélectionnés ne changent pas
            if (indiceValide(i, static_cast<int>(plancheIndex.size())) &&
                indiceValide(j, static_cast<int>(plancheIndex.size()))) {
                std::string temporaire = plancheIndex[i];
                plancheIndex[i] = plancheIndex[j];
                plancheIndex[j] = temporaire;
            }

            // PAR_ID : échanger seulement les images
            // Les noms sélectionnés ne changent pas
            if (indiceValide(i, static_cast<int>(plancheId.size())) &&
                indiceValide(j, static_cast<int>(plancheId.size()))) {
                std::string temporaire = plancheId[i];
                plancheId[i] = plancheId[j];
                plancheId[j] = temporaire;
            }
        }

        else if (operation == "RETIRE") {
            int indice;
            std::cin >> indice;

            // DANS_ITEM : retirer l'image et son drapeau
            if (indiceValide(indice, static_cast<int>(dansItem.size()))) {
                dansItem.erase(dansItem.begin() + indice);
            }

            // PAR_INDEX : retirer l'image, sans modifier les indices gardés
            if (indiceValide(indice, static_cast<int>(plancheIndex.size()))) {
                plancheIndex.erase(plancheIndex.begin() + indice);
            }

            // PAR_ID : retirer l'image, sans modifier les noms gardés
            if (indiceValide(indice, static_cast<int>(plancheId.size()))) {
                plancheId.erase(plancheId.begin() + indice);
            }
        }

        else if (operation == "SUPPRIME") {
            // DANS_ITEM : retirer toutes les images sélectionnées
            std::vector<Image> nouvellePlanche;

            for (int i = 0; i < static_cast<int>(dansItem.size()); i++) {
                if (!dansItem[i].selectionnee) {
                    nouvellePlanche.push_back(dansItem[i]);
                }
            }

            dansItem = nouvellePlanche;

            // PAR_INDEX : retirer les images aux indices sélectionnés
            nouvellePlanche.clear();

            for (int i = 0; i < static_cast<int>(plancheIndex.size()); i++) {
                if (!contient(selectionIndex, i)) {
                    Image image;
                    image.nom = plancheIndex[i];
                    nouvellePlanche.push_back(image);
                }
            }

            plancheIndex.clear();

            for (int i = 0; i < static_cast<int>(nouvellePlanche.size()); i++) {
                plancheIndex.push_back(nouvellePlanche[i].nom);
            }

            // Vider la sélection PAR_INDEX
            selectionIndex.clear();

            // PAR_ID : retirer les images dont le nom est sélectionné
            std::vector<std::string> nouvellePlancheId;

            for (int i = 0; i < static_cast<int>(plancheId.size()); i++) {
                if (!contientNom(selectionId, plancheId[i])) {
                    nouvellePlancheId.push_back(plancheId[i]);
                }
            }

            plancheId = nouvellePlancheId;

            // Vider la sélection PAR_ID
            selectionId.clear();
        }
    }

    // Construire les planches et sélections finales
    std::vector<std::string> nomsItem;
    std::vector<bool> selectionItem;

    for (int i = 0; i < static_cast<int>(dansItem.size()); i++) {
        nomsItem.push_back(dansItem[i].nom);
        selectionItem.push_back(dansItem[i].selectionnee);
    }

    std::vector<bool> selectionParIndex;

    for (int i = 0; i < static_cast<int>(plancheIndex.size()); i++) {
        selectionParIndex.push_back(contient(selectionIndex, i));
    }

    std::vector<bool> selectionParId;

    for (int i = 0; i < static_cast<int>(plancheId.size()); i++) {
        selectionParId.push_back(contientNom(selectionId, plancheId[i]));
    }

    // Afficher DANS_ITEM
    afficherPlanche("DANS_ITEM", nomsItem);
    afficherSelection("DANS_ITEM", nomsItem, selectionItem);

    // Afficher PAR_INDEX
    afficherPlanche("PAR_INDEX", plancheIndex);
    afficherSelection("PAR_INDEX", plancheIndex, selectionParIndex);

    // Afficher PAR_ID
    afficherPlanche("PAR_ID", plancheId);
    afficherSelection("PAR_ID", plancheId, selectionParId);

    // Comparer les résultats avec DANS_ITEM
    bool fauxIndex = false;
    bool fauxId = false;

    if (plancheIndex != nomsItem || selectionParIndex != selectionItem) {
        fauxIndex = true;
    }

    if (plancheId != nomsItem || selectionParId != selectionItem) {
        fauxId = true;
    }

    std::cout << "FAUX";

    if (!fauxIndex && !fauxId) {
        std::cout << " AUCUN";
    } else {
        if (fauxIndex) {
            std::cout << " PAR_INDEX";
        }

        if (fauxId) {
            std::cout << " PAR_ID";
        }
    }

    std::cout << "\n";

    return 0;
}