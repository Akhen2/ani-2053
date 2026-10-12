#include <iostream>
#include <string>

int main() {
    // Lecture du seuil maximal de mémoire autorisé, en octets.
    long long S;
    std::cin >> S;

    // Lecture du nombre de sons à traiter.
    int N;
    std::cin >> N;

    // Bilans demandés à la fin du programme.
    long long totalMemoire = 0;
    int totalFlux = 0;
    int totalRefuses = 0;

    // Traitement des sons dans leur ordre de lecture.
    for (int i = 0; i < N; i++) {
        std::string nom;
        long long frequence, canaux, bits, duree, fichier;

        std::cin >> nom >> frequence >> canaux >> bits >> duree >> fichier;

        // Seules les profondeurs de 8, 16, 24 et 32 bits sont acceptées.
        if (bits != 8 && bits != 16 && bits != 24 && bits != 32) {
            std::cout << nom << " REFUSE" << std::endl;
            totalRefuses++;
            continue;
        }

        // Calcul de la taille brute en octets.
        // Les multiplications sont effectuées avant la division par 1000.
        // long long permet de gérer les grandes valeurs sans débordement
        // dans les limites des données prévues par l'exercice.
        long long brut = frequence * canaux * (bits / 8) * duree / 1000;

        // Calcul du pourcentage occupé par le fichier par rapport au brut.
        // La division entière arrondit le résultat vers le bas.
        long long pourcent = fichier * 100 / brut;

        // Affichage des informations calculées pour le son.
        if (brut > S) {
            // Un son strictement supérieur au seuil est lu en flux.
            std::cout << nom << " " << brut << " " << pourcent << " FLUX" << std::endl;

            totalFlux++;
        } else {
            // Un son inférieur ou égal au seuil est chargé en mémoire.
            std::cout << nom << " " << brut << " " << pourcent << " MEMOIRE" << std::endl;

            totalMemoire += brut;
        }
    }

    // Affichage du bilan final.
    std::cout << "MEMOIRE " << totalMemoire << std::endl;
    std::cout << "FLUX " << totalFlux << std::endl;
    std::cout << "REFUSES " << totalRefuses << std::endl;

    return 0;
}
