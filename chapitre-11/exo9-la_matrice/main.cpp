[22/11/2026 11:28] Akhen Aristide: #include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Structure représentant une entrée
struct Entree
{
    std::string nom;
    int valeur;
    int cout;
    std::string etiquette;
    std::string genre;
    std::string cible;

    int ordre;
    int caseClassement;
};

// Structure représentant une entrée écartée
struct EntreeEcartee
{
    std::string nom;
    std::string raison;
};

// Détermine la priorité d'une étiquette
int prioriteEtiquette(const std::string& etiquette)
{
    if (etiquette == "MESUREE")
    {
        return 1;
    }

    if (etiquette == "OBSERVEE")
    {
        return 2;
    }

    return 3;
}

// Détermine la case d'une entrée
int determinerCase(int valeur, int cout)
{
    if (valeur >= 3 && cout < 3)
    {
        return 1; // MAINTENANT
    }

    if (valeur >= 3 && cout >= 3)
    {
        return 2; // DECOUPER
    }

    if (valeur < 3 && cout < 3)
    {
        return 3; // EN_PASSANT
    }

    return 4; // ON_NE_LE_FAIT_PAS
}

// Donne le nom correspondant à une case
std::string nomCase(int numero)
{
    if (numero == 1)
    {
        return "MAINTENANT";
    }

    if (numero == 2)
    {
        return "DECOUPER";
    }

    if (numero == 3)
    {
        return "EN_PASSANT";
    }

    return "ON_NE_LE_FAIT_PAS";
}

int main()
{
    int n;

    // Lire le nombre d'entrées
    std::cin >> n;

    std::vector<Entree> entrees;
    std::vector<EntreeEcartee> ecartees;

    // Lire toutes les entrées
    for (int i = 0; i < n; i++)
    {
        Entree e;

        std::cin >> e.nom
                 >> e.valeur
                 >> e.cout
                 >> e.etiquette
                 >> e.genre;

        e.cible = "";
        e.ordre = i;
        e.caseClassement = 0;

        // Un SOCLE possède un sixième mot : sa cible
        if (e.genre == "SOCLE")
        {
            std::cin >> e.cible;
        }

        // Vérifier si l'entrée doit être écartée
        if (e.genre == "REECRITURE")
        {
            EntreeEcartee x;
            x.nom = e.nom;
            x.raison = "reecriture";

            ecartees.push_back(x);
        }
        else if (e.genre == "CHOIX")
        {
            EntreeEcartee x;
            x.nom = e.nom;
            x.raison = "choix";

            ecartees.push_back(x);
        }
        else if (e.etiquette == "-")
        {
            EntreeEcartee x;
            x.nom = e.nom;
            x.raison = "sans_etiquette";

            ecartees.push_back(x);
        }
        else
        {
            // L'entrée est conservée
            entrees.push_back(e);
        }
    }

    // Donner aux SOCLES la valeur de leur cible si nécessaire
    for (int i = 0; i < static_cast<int>(entrees.size()); i++)
    {
        if (entrees[i].genre == "SOCLE")
        {
            // Rechercher la cible du SOCLE
            for (int j = 0; j < static_cast<int>(entrees.size()); j++)
            {
                if (entrees[j].nom == entrees[i].cible
                    && entrees[j].genre == "MANQUE")
                {
                    // Garder la plus grande des deux valeurs
                    if (entrees[j].valeur > entrees[i].valeur)
                    {
                        entrees[i].valeur = entrees[j].valeur;
                    }

                    break;
                }
            }
        }
    }

    // Déterminer la case de chaque entrée conservée
    bool refusExiste = false;

    for (int i = 0; i < static_cast<int>(entrees.size()); i++)
    {
        entrees[i].caseClassement =
            determinerCase(entrees[i].valeur, entrees[i].cout);

        // Vérifier si au moins une entrée est refusée
        if (entrees[i].caseClassement == 4)
        {
            refusExiste = true;
        }
    }

    // Trier les entrées selon les règles de l'énoncé
[22/11/2026 11:28] Akhen Aristide: std::sort(entrees.begin(), entrees.end(),
        [](const Entree& a, const Entree& b)
        {
            // 1. Priorité à la case
            if (a.caseClassement != b.caseClassement)
            {
                return a.caseClassement < b.caseClassement;
            }

            // 2. Priorité à l'étiquette
            int prioriteA = prioriteEtiquette(a.etiquette);
            int prioriteB = prioriteEtiquette(b.etiquette);

            if (prioriteA != prioriteB)
            {
                return prioriteA < prioriteB;
            }

            // 3. Valeur la plus forte en premier
            if (a.valeur != b.valeur)
            {
                return a.valeur > b.valeur;
            }

            // 4. Coût le plus faible en premier
            if (a.cout != b.cout)
            {
                return a.cout < b.cout;
            }

            // 5. Ordre initial des entrées
            return a.ordre < b.ordre;
        });

    // Afficher les entrées conservées dans leur ordre de classement
    for (int i = 0; i < static_cast<int>(entrees.size()); i++)
    {
        std::cout << nomCase(entrees[i].caseClassement)
                  << " "
                  << entrees[i].nom
                  << " "
                  << entrees[i].etiquette
                  << "\n";
    }

    // Afficher les entrées écartées dans leur ordre initial
    for (int i = 0; i < static_cast<int>(ecartees.size()); i++)
    {
        std::cout << "HORS_LISTE "
                  << ecartees[i].nom
                  << " "
                  << ecartees[i].raison
                  << "\n";
    }

    // Afficher le verdict final
    if (refusExiste)
    {
        std::cout << "VERDICT HONNETE\n";
    }
    else
    {
        std::cout << "VERDICT COMPLAISANT\n";
    }

    return 0;
}
