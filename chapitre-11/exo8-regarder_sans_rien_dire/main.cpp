[22/11/2026 11:27] Akhen Aristide: #include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Structure pour mémoriser un contournement observé
struct Contournement
{
    std::string nom;
    int fois;
    int premiereObservation;
    int ordreEntree;
    bool dit;
};

// Convertit un instant mm:ss en secondes
int convertirEnSecondes(const std::string& temps)
{
    int minutes = 0;
    int secondes = 0;

    // Séparer les minutes et les secondes
    std::stringstream flux(temps);
    char deuxPoints;

    flux >> minutes >> deuxPoints >> secondes;

    return minutes * 60 + secondes;
}

int main()
{
    int n, m;

    // Lire le nombre d'observations
    std::cin >> n;

    std::string mot;
    std::cin >> mot; // Lire OBSERVE

    std::vector<Contournement> contournements;

    int horsSeance = 0;
    int ordre = 0;

    // Lire les observations
    for (int i = 0; i < n; i++)
    {
        std::string temps;
        std::string nom;

        std::cin >> temps >> nom;

        int instant = convertirEnSecondes(temps);

        // Une observation après 20 minutes est hors séance
        if (instant > 20 * 60)
        {
            horsSeance++;
            continue;
        }

        // Rechercher si le contournement existe déjà
        bool trouve = false;

        for (int j = 0; j < static_cast<int>(contournements.size()); j++)
        {
            if (contournements[j].nom == nom)
            {
                contournements[j].fois++;
                trouve = true;
                break;
            }
        }

        // Si le nom n'existe pas encore, le créer
        if (!trouve)
        {
            Contournement nouveau;

            nouveau.nom = nom;
            nouveau.fois = 1;
            nouveau.premiereObservation = instant;
            nouveau.ordreEntree = ordre;
            nouveau.dit = false;

            contournements.push_back(nouveau);
        }

        ordre++;
    }

    // Lire le nombre de noms cités pendant l'entretien
    std::cin >> m;
    std::cin >> mot; // Lire DIT

    std::vector<std::string> nomsDits;

    for (int i = 0; i < m; i++)
    {
        std::string nom;
        std::cin >> nom;

        nomsDits.push_back(nom);

        // Vérifier si le nom a été observé
        for (int j = 0; j < static_cast<int>(contournements.size()); j++)
        {
            if (contournements[j].nom == nom)
            {
                contournements[j].dit = true;
                break;
            }
        }
    }

    // Trier les contournements selon les règles de l'énoncé
    std::sort(contournements.begin(), contournements.end(),
        [](const Contournement& a, const Contournement& b)
        {
            // Priorité au nombre d'observations le plus élevé
            if (a.fois != b.fois)
            {
                return a.fois > b.fois;
            }

            // Ensuite, à la première observation la plus ancienne
            if (a.premiereObservation != b.premiereObservation)
            {
                return a.premiereObservation < b.premiereObservation;
            }

            // Enfin, à l'ordre d'apparition dans l'entrée
            return a.ordreEntree < b.ordreEntree;
        });

    int nonDits = 0;
    int totalObservations = 0;
    int totalNonDits = 0;

    // Afficher les contournements observés
    for (int i = 0; i < static_cast<int>(contournements.size()); i++)
    {
        std::cout << contournements[i].nom << " "
                  << contournements[i].fois << " ";

        if (contournements[i].dit)
        {
            std::cout << "DIT\n";
        }
        else
        {
            std::cout << "NON_DIT\n";

            nonDits++;
            totalNonDits += contournements[i].fois;
        }

        totalObservations += contournements[i].fois;
    }

    // Calculer la part non dite en pourcentage
    int partNonDite = 0;

    if (totalObservations > 0)
    {
        partNonDite = (100 * totalNonDits) / totalObservations;
    }
[22/11/2026 11:27] Akhen Aristide: // Afficher les statistiques
    std::cout << "NON_DITS " << nonDits << "\n";
    std::cout << "PART_NON_DITE " << partNonDite << "\n";

    // Rechercher les noms cités mais jamais observés
    std::vector<std::string> ditsSansVu;

    for (int i = 0; i < static_cast<int>(nomsDits.size()); i++)
    {
        bool trouve = false;

        for (int j = 0; j < static_cast<int>(contournements.size()); j++)
        {
            if (nomsDits[i] == contournements[j].nom)
            {
                trouve = true;
                break;
            }
        }

        if (!trouve)
        {
            ditsSansVu.push_back(nomsDits[i]);
        }
    }

    // Afficher les noms cités mais jamais observés
    std::cout << "DIT_SANS_VU";

    if (ditsSansVu.empty())
    {
        std::cout << " AUCUN";
    }
    else
    {
        for (int i = 0; i < static_cast<int>(ditsSansVu.size()); i++)
        {
            std::cout << " " << ditsSansVu[i];
        }
    }

    std::cout << "\n";

    // Afficher le nombre d'observations hors séance
    std::cout << "HORS_SEANCE " << horsSeance << "\n";

    return 0;
}
