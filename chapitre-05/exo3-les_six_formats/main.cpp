#include <iostream>
#include <string>

// Structure décrivant les caractéristiques d'un format de pixels.
struct Format
{
    std::string nom;
    long long octetsParPixel;
    bool couleur;
    bool transparence;
    bool flottants;
};

// Recherche un format à partir de son nom exact.
// Si le format est inconnu, la fonction renvoie false.
bool rechercherFormat(const std::string& nom, Format& resultat)
{
    // Format en niveaux de gris, sans transparence.
    if (nom == "GRAY8")
    {
        resultat = {"GRAY8", 1, false, false, false};
        return true;
    }

    // Format en niveaux de gris avec transparence.
    if (nom == "GRAY_A16")
    {
        resultat = {"GRAY_A16", 2, false, true, false};
        return true;
    }

    // Format RGB sans transparence.
    if (nom == "RGB24")
    {
        resultat = {"RGB24", 3, true, false, false};
        return true;
    }

    // Format RGBA avec transparence.
    if (nom == "RGBA32")
    {
        resultat = {"RGBA32", 4, true, true, false};
        return true;
    }

    // Format RGB utilisant des nombres flottants.
    if (nom == "RGB96F")
    {
        resultat = {"RGB96F", 12, true, false, true};
        return true;
    }

    // Format RGBA utilisant des nombres flottants.
    if (nom == "RGBA128F")
    {
        resultat = {"RGBA128F", 16, true, true, true};
        return true;
    }

    // Aucun format correspondant au nom n'a été trouvé.
    return false;
}

// Détermine les informations perdues lors de la conversion.
std::string calculerPertes(const Format& source, const Format& cible)
{
    std::string pertes = "";

    // Première perte possible : la transparence.
    if (source.transparence && !cible.transparence)
    {
        pertes += "TRANSPARENCE";
    }

    // Deuxième perte possible : la couleur.
    if (source.couleur && !cible.couleur)
    {
        // Le signe + sépare les pertes déjà enregistrées.
        if (!pertes.empty())
        {
            pertes += "+";
        }

        pertes += "COULEUR";
    }

    // Troisième perte possible : l'étendue des flottants.
    if (source.flottants && !cible.flottants)
    {
        if (!pertes.empty())
        {
            pertes += "+";
        }

        pertes += "ETENDUE";
    }

    // Aucune caractéristique n'a été perdue.
    if (pertes.empty())
    {
        return "AUCUNE";
    }

    return pertes;
}

int main()
{
    // Lecture des dimensions de l'image.
    long long w, h;
    std::cin >> w >> h;

    // Lecture du nombre de conversions à effectuer.
    int N;
    std::cin >> N;

    // Compteurs des bilans finaux.
    long long total = 0;
    int sansPerte = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i)
    {
        std::string nomSource, nomCible;
        std::cin >> nomSource >> nomCible;

        // Structures contenant les caractéristiques des formats.
        Format source;
        Format cible;

        // Recherche des deux formats.
        bool sourceConnue = rechercherFormat(nomSource, source);
        bool cibleConnue = rechercherFormat(nomCible, cible);

        // Si l'un des deux formats est inconnu, la conversion est refusée.
        if (!sourceConnue || !cibleConnue)
        {
            std::cout << nomSource << " " << nomCible << " REFUSE" << std::endl;

            ++refuses;
            continue;
        }

        // Calcul de la mémoire nécessaire pour chaque format.
        // long long permet de gérer les grandes valeurs.
        long long nombrePixels = w * h;

        long long octetsSource = nombrePixels * source.octetsParPixel;

        long long octetsCible = nombrePixels * cible.octetsParPixel;

        // Détermination des pertes dans l'ordre imposé.
        std::string pertes = calculerPertes(source, cible);

        // Affichage des informations sur la conversion.
        std::cout << nomSource << " " << nomCible << " " << octetsSource << " "  << octetsCible << " " << pertes << std::endl;

        // Le total additionne la mémoire des formats cibles acceptés.
        total += octetsCible;

        // On compte les conversions qui ne perdent aucune caractéristique.
        if (pertes == "AUCUNE")
        {
            ++sansPerte;
        }
    }

    // Affichage des trois bilans dans l'ordre demandé.
    std::cout << "TOTAL " << total << std::endl;
    std::cout << "SANS_PERTE " << sansPerte << std::endl;
    std::cout << "REFUSES " << refuses << std::endl;

    return 0;
}
