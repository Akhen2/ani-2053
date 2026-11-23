#include <iostream>
#include <string>
#include <sstream>

// Informations d'une tâche
struct Tache {
    std::string nom;
    int minimum;
    int parJour;

    int gestes;
    long long debut;
    long long attente;
};

// Convertir des secondes en minutes:secondes
void afficherTemps(long long secondes) {
    long long minutes = secondes / 60;
    long long reste = secondes % 60;

    std::cout << minutes << ":";

    // Afficher un zéro devant les secondes si nécessaire
    if (reste < 10) {
        std::cout << "0";
    }

    std::cout << reste;
}

int main() {
    Tache tache;
    bool enCours = false;

    // Total des secondes perdues sur une journée
    long long totalJour = 0;

    std::string ligne;

    // Lire le journal jusqu'à la fin de l'entrée
    while (std::getline(std::cin, ligne)) {

        std::stringstream lecture(ligne);

        long long instant;
        std::string operation;

        if (!(lecture >> instant >> operation)) {
            continue;
        }

        // Début d'une tâche
        if (operation == "DEBUT") {
            lecture >> tache.nom >> tache.minimum >> tache.parJour;

            tache.gestes = 0;
            tache.debut = instant;
            tache.attente = 0;

            enCours = true;
        }

        // Fin d'une tâche
        else if (operation == "FIN") {
            std::string nom;
            lecture >> nom;

            if (enCours) {
                // Calculer les gestes supplémentaires
                int enTrop = tache.gestes - tache.minimum;

                if (enTrop < 0) {
                    enTrop = 0;
                }

                // Calculer la durée de la tâche
                long long duree = instant - tache.debut;

                // Calculer le coût de l'attente sur une journée
                long long coutJour =
                    (tache.attente * tache.parJour) / 1000;

                // Afficher les résultats
                std::cout << tache.nom
                          << " GESTES " << tache.gestes
                          << " EN_TROP " << enTrop
                          << " DUREE " << duree
                          << " ATTENTE " << tache.attente
                          << " JOUR ";

                afficherTemps(coutJour);
                std::cout << "\n";

                // Ajouter le coût au total journalier
                totalJour += coutJour;

                enCours = false;
            }
        }

        // Une attente
        else if (operation == "ATTENTE") {
            long long duree;
            lecture >> duree;

            if (enCours) {
                tache.attente += duree;
            }
        }

        // Un clic
        else if (operation == "CLIC") {
            if (enCours) {
                tache.gestes++;
            }
        }

        // Une touche du clavier
        else if (operation == "TOUCHE") {
            std::string touche;
            lecture >> touche;

            if (enCours) {
                tache.gestes++;
            }
        }

        // Un mouvement de molette
        else if (operation == "MOLETTE") {
            if (enCours) {
                tache.gestes++;
            }
        }

        // Un glissement
        else if (operation == "GLISSE") {
            if (enCours) {
                tache.gestes++;
            }
        }
    }

    // Signaler une tâche qui n'est pas terminée
    if (enCours) {
        std::cout << tache.nom << " INACHEVEE\n";
    }

    // Afficher le total journalier
    std::cout << "TOTAL_JOUR ";
    afficherTemps(totalJour);
    std::cout << "\n";

    return 0;
}
