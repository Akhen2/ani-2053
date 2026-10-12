#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Convertit un caractère hexadécimal en entier.
// Exemple : 'A' -> 10, 'F' -> 15, '9' -> 9.
int valeurHex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return -1;
}

// Convertit une chaîne hexadécimale en octets.
// Chaque paire de caractères représente un octet.
std::vector<int> decoderHex(const std::string& hex)
{
    std::vector<int> octets;

    // Le tiret signifie qu'aucun octet n'est fourni.
    if (hex == "-")
        return octets;

    for (size_t i = 0; i + 1 < hex.size(); i += 2)
    {
        int haut = valeurHex(hex[i]);
        int bas = valeurHex(hex[i + 1]);

        // On ajoute uniquement les paires hexadécimales valides.
        if (haut != -1 && bas != -1)
        {
            octets.push_back(haut * 16 + bas);
        }
    }

    return octets;
}

// Vérifie que les octets commencent par une signature donnée.
bool commencePar(const std::vector<int>& octets,
                 const std::vector<int>& signature)
{
    if (octets.size() < signature.size())
        return false;

    for (size_t i = 0; i < signature.size(); ++i)
    {
        if (octets[i] != signature[i])
            return false;
    }

    return true;
}

// Vérifie si un octet correspond à une valeur parmi plusieurs possibilités.
bool estDans(int valeur, const vector<int>& valeurs)
{
    return find(valeurs.begin(), valeurs.end(), valeur) != valeurs.end();
}

// Détermine le format réel du fichier.
// Les règles sont testées dans l'ordre exact de l'énoncé.
std::string reconnaitreFormat(long long taille, const std::vector<int>& b)
{
    // Règle 1 : les fichiers de moins de 4 octets sont refusés.
    if (taille < 4)
        return "";

    // Règle 2 : signature PNG.
    if (taille >= 8 &&
        commencePar(b, {0x89, 0x50, 0x4E, 0x47}))
    {
        return "PNG";
    }

    // Règle 3 : signature JPEG.
    if (commencePar(b, {0xFF, 0xD8, 0xFF}))
    {
        return "JPEG";
    }

    // Règle 4 : signature BMP, lettres BM.
    if (commencePar(b, {0x42, 0x4D}))
    {
        return "BMP";
    }

    // Règle 5 : signature QOI, lettres qoif.
    if (commencePar(b, {0x71, 0x6F, 0x69, 0x66}))
    {
        return "QOI";
    }

    // Règle 6 : signature GIF8.
    if (commencePar(b, {0x47, 0x49, 0x46, 0x38}))
    {
        return "GIF";
    }

    // Règle 7 : signature ICO ou CUR.
    if (b.size() >= 4 &&
        b[0] == 0x00 &&
        b[1] == 0x00 &&
        (b[2] == 0x01 || b[2] == 0x02) &&
        b[3] == 0x00)
    {
        return "ICO";
    }

    // Règle 8 : signature HDR.
    if (taille >= 10 &&
        commencePar(b, {0x23, 0x3F}))
    {
        return "HDR";
    }

    // Règle 9 : signature EXR.
    if (commencePar(b, {0x76, 0x2F, 0x31, 0x01}))
    {
        return "EXR";
    }

    // Règle 10 : formats PBM, PGM et PPM.
    if (b.size() >= 2 &&
        b[0] == 0x50 &&
        b[1] >= 0x31 &&
        b[1] <= 0x36)
    {
        // Les nombres 1 et 4 correspondent à PBM.
        if (b[1] == 0x31 || b[1] == 0x34)
            return "PBM";

        // Les nombres 2 et 5 correspondent à PGM.
        if (b[1] == 0x32 || b[1] == 0x35)
            return "PGM";

        // Les nombres 3 et 6 correspondent à PPM.
        return "PPM";
    }

    // Règle 11 : reconnaissance approximative du format TGA.
    if (taille >= 18 &&
        b.size() >= 3 &&
        estDans(b[2], {0x00, 0x01, 0x02, 0x03,
                       0x09, 0x0A, 0x0B}))
    {
        return "TGA";
    }

    // Règle 12 : reconnaissance du format SVG.
    // On commence par ignorer un éventuel BOM UTF-8.
    size_t position = 0;

    if (b.size() >= 3 &&
        b[0] == 0xEF &&
        b[1] == 0xBB &&
        b[2] == 0xBF)
    {
        position = 3;
    }

    // On ignore ensuite les espaces, tabulations et sauts de ligne autorisés.
    while (position < b.size() &&
           (b[position] == 0x20 ||
            b[position] == 0x09 ||
            b[position] == 0x0A ||
            b[position] == 0x0D))
    {
        ++position;
    }

    // On vérifie si la suite commence par "<?xml".
    bool commenceXML =
        position + 5 <= b.size() &&
        b[position]     == 0x3C &&
        b[position + 1] == 0x3F &&
        b[position + 2] == 0x78 &&
        b[position + 3] == 0x6D &&
        b[position + 4] == 0x6C;

    // On vérifie si la suite commence par "<svg".
    bool commenceSVG =
        position + 4 <= b.size() &&
        b[position]     == 0x3C &&
        b[position + 1] == 0x73 &&
        b[position + 2] == 0x76 &&
        b[position + 3] == 0x67;

    if (commenceXML || commenceSVG)
        return "SVG";

    // Aucune règle ne correspond.
    return "";
}

// Extrait l'extension après le dernier point et la met en minuscules.
std::string extraireExtension(const std::string& nom)
{
    size_t position = nom.find_last_of('.');

    // Sans point, l'extension est vide.
    if (position == std::string::npos)
        return "";

    std::string extension = nom.substr(position + 1);

    // Conversion de chaque caractère en minuscule.
    for (char& c : extension)
    {
        c = static_cast<char>(
            tolower(static_cast<unsigned char>(c))
        );
    }

    return extension;
}

// Vérifie si l'extension correspond au format reconnu.
bool extensionCorrecte(const std::string& format,
                       const std::string& extension)
{
    if (format == "PNG")
        return extension == "png";

    if (format == "JPEG")
        return extension == "jpg" || extension == "jpeg";

    if (format == "BMP")
        return extension == "bmp";

    if (format == "QOI")
        return extension == "qoi";

    if (format == "GIF")
        return extension == "gif";

    if (format == "ICO")
        return extension == "ico" || extension == "cur";

    if (format == "HDR")
        return extension == "hdr";

    if (format == "EXR")
        return extension == "exr";

    if (format == "PBM")
        return extension == "pbm";

    if (format == "PGM")
        return extension == "pgm";

    if (format == "PPM")
        return extension == "ppm";

    if (format == "TGA")
        return extension == "tga";

    if (format == "SVG")
        return extension == "svg";

    return false;
}

int main()
{
    int N;
    std::cin >> N;

    // Compteurs demandés dans le bilan final.
    int lus = 0;
    int mensonges = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i)
    {
        std::string nom;
        long long taille;
        std::string hexadecimal;

        std::cin >> nom >> taille >> hexadecimal;

        // Étape 1 : décoder les octets du fichier.
        std::vector<int> octets = decoderHex(hexadecimal);

        // Étape 2 : reconnaître le format réel.
        std::string format = reconnaitreFormat(taille, octets);

        // Si aucun format n'est reconnu, le fichier est refusé.
        if (format.empty())
        {
            std::cout << nom << " REFUSE" << std::endl;
            ++refuses;
            continue;
        }

        // Étape 3 : comparer le format réel à l'extension.
        std::string extension = extraireExtension(nom);

        // Chaque fichier reconnu compte dans LUS.
        ++lus;

        if (extensionCorrecte(format, extension))
        {
            std::cout << nom << " " << format << " OK" << std::endl;
        }
        else
        {
            std::cout << nom << " " << format << " MENT" << std::endl;
            ++mensonges;
        }
    }

    // Affichage des trois bilans dans l'ordre imposé.
    std::cout << "LUS " << lus << std::endl;
    std::cout << "MENSONGES " << mensonges << std::endl;
    std::cout << "REFUSES " << refuses << std::endl;

    return 0;
}
