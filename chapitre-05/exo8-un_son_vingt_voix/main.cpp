#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // D : durée du son en millisecondes.
    // C : durée nécessaire pour charger le fichier.
    long long D, C;
    std::cin >> D >> C;

    // Lecture du nombre de lectures à effectuer.
    int N;
    std::cin >> N;

    // Stockage des instants de lecture dans leur ordre de lecture.
    std::vector<long long> instants(N);

    for (int i = 0; i < N; i++) {
        std::cin >> instants[i];
    }

    // Variables pour les bilans finaux.
    long long voixMax = 0;
    long long retardMax = 0;
    int coupes = 0;

    // Fin du chargement précédent.
    // Au départ, aucun chargement n'a encore été effectué.
    long long finChargementPrecedent = 0;

    // Traitement de chaque lecture.
    for (int i = 0; i < N; i++) {
        long long t = instants[i];

        // --------------------------------------------------
        // 1. Calcul du nombre de voix actives.
        // --------------------------------------------------
        // Une lecture commencée à un instant précédent est
        // encore active si sa fin est strictement supérieure à t.
        // La lecture actuelle est également comptée.
        long long voix = 0;

        for (int j = 0; j <= i; j++) {
            if (instants[j] + D > t) {
                voix++;
            }
        }

        // Mise à jour du maximum de voix actives.
        voixMax = max(voixMax, voix);

        // --------------------------------------------------
        // 2. Calcul du retard lié au chargement du fichier.
        // --------------------------------------------------
        // Le chargement commence au plus tard de l'instant
        // de lecture prévu et de la fin du chargement précédent.
        long long debutChargement =
            max(t, finChargementPrecedent);

        // Le son ne commence qu'à la fin du chargement.
        long long finChargement = debutChargement + C;

        // Le retard est la différence entre le début réel
        // de la lecture et son instant prévu.
        long long retard = finChargement - t;

        // Le chargement actuel devient le précédent pour la
        // prochaine lecture.
        finChargementPrecedent = finChargement;

        // Mise à jour du retard maximal.
        retardMax = max(retardMax, retard);

        // --------------------------------------------------
        // 3. Détermination des coupures avec une seule voix.
        // --------------------------------------------------
        // Une lecture est coupée si la suivante commence
        // strictement avant la fin de la lecture actuelle.
        bool coupee = false;

        if (i + 1 < N) {
            if (instants[i + 1] < t + D) {
                coupee = true;
            }
        }

        // Affichage des résultats de cette lecture.
        if (coupee) {
            std::cout << t << " " << voix << " " << retard << " " << "COUPE" << std::endl;

            coupes++;
        } else {
            std::cout << t << " " << voix << " " << retard << " " << "ENTIER" << std::endl;
        }
    }

    // Affichage des trois bilans finaux.
    std::cout << "VOIX_MAX " << voixMax << std::endl;
    std::cout << "RETARD_MAX " << retardMax << std::endl;
    std::cout << "COUPES " << coupes << std::endl;

    return 0;
}
