#include <iostream>

// Structure représentant le résultat d'une politique
struct Politique
{
    long long vx; // Position x du viewport
    long long vy; // Position y du viewport
    long long vw; // Largeur du viewport
    long long vh; // Hauteur du viewport
    long long mw; // Largeur du monde visible
    long long mh; // Hauteur du monde visible
};

long long arrondi(long long a, long long b)
{
    return (2 * a + b) / (2 * b);
}

// ------------------------------------------------------------
// Calcule la politique FIT_LETTERBOX.
// ------------------------------------------------------------
Politique fitLetterbox(
    long long RW,
    long long RH,
    long long W,
    long long H)
{
    Politique p;

    if (W * RH <= H * RW)
    {
        // La largeur de la fenêtre limite le viewport.
        p.vw = W;

        // Calcul de la hauteur en conservant
        // les proportions du monde de référence.
        p.vh = arrondi(RH * W, RW);
    }
    else
    {
        // La hauteur de la fenêtre limite le viewport.
        p.vh = H;

        // Calcul de la largeur correspondante.
        p.vw = arrondi(RW * H, RH);
    }

    // Le viewport est centré dans la fenêtre.
    p.vx = (W - p.vw) / 2;
    p.vy = (H - p.vh) / 2;

    // Le monde visible correspond toujours
    // à la référence.
    p.mw = RW;
    p.mh = RH;

    return p;
}

// ------------------------------------------------------------
// Affichage d'une politique.
// ------------------------------------------------------------
void afficher(
    const char* nom,
    const Politique& p)
{
    std::cout << nom << " "
         << p.vx << " "
         << p.vy << " "
         << p.vw << " "
         << p.vh << " "
         << p.mw << " "
         << p.mh << std::endl;
}

int main()
{
    // RW, RH : résolution de référence
    // AW, AH : ancienne taille de la fenêtre
    // W, H   : nouvelle taille de la fenêtre
    long long RW, RH, AW, AH, W, H;

    std::cin >> RW >> RH >> AW >> AH >> W >> H;

    // Les quatre politiques qui utilisent la référence
    // retombent sur FOLLOW_WINDOW si aucune référence
    // n'est définie.
    bool referenceExiste = (RW != 0 && RH != 0);

    // =========================================================
    // 1. FOLLOW_WINDOW
    // =========================================================

    Politique follow;

    // Le viewport occupe toute la fenêtre.
    follow.vx = 0;
    follow.vy = 0;
    follow.vw = W;
    follow.vh = H;

    // Le monde visible a exactement la taille du viewport.
    follow.mw = W;
    follow.mh = H;

    // =========================================================
    // 2. STRETCH
    // =========================================================

    Politique stretch;

    if (!referenceExiste)
    {
        // Sans référence, STRETCH fait comme FOLLOW_WINDOW.
        stretch = follow;
    }
    else
    {
        // Le viewport occupe toute la fenêtre.
        stretch.vx = 0;
        stretch.vy = 0;
        stretch.vw = W;
        stretch.vh = H;

        // Le monde conserve la taille de référence.
        stretch.mw = RW;
        stretch.mh = RH;
    }

    // =========================================================
    // 3. FIT_LETTERBOX
    // =========================================================

    Politique letterbox;

    if (!referenceExiste)
    {
        // Sans référence, on utilise FOLLOW_WINDOW.
        letterbox = follow;
    }
    else
    {
        letterbox = fitLetterbox(RW, RH, W, H);
    }

    // =========================================================
    // 4. INTEGER_SCALE
    // =========================================================

    Politique integerScale;

    if (!referenceExiste)
    {
        // Sans référence, on utilise FOLLOW_WINDOW.
        integerScale = follow;
    }
    else if (W >= RW && H >= RH)
    {
        // La fenêtre est suffisamment grande pour permettre
        // un agrandissement entier d'au moins 1.

        // Agrandissement entier possible horizontalement.
        long long kLargeur = W / RW;

        // Agrandissement entier possible verticalement.
        long long kHauteur = H / RH;

        // On prend le plus petit pour que le monde entier
        // tienne dans la fenêtre.
        long long k = (kLargeur < kHauteur)
                        ? kLargeur
                        : kHauteur;

        // Calcul du viewport avec cet agrandissement.
        integerScale.vw = RW * k;
        integerScale.vh = RH * k;

        // Centrage du viewport.
        integerScale.vx = (W - integerScale.vw) / 2;
        integerScale.vy = (H - integerScale.vh) / 2;

        // Le monde visible reste celui de référence.
        integerScale.mw = RW;
        integerScale.mh = RH;
    }
    else
    {
        // Si la fenêtre est plus petite que la référence
        // dans au moins une dimension, on utilise exactement
        // FIT_LETTERBOX.
        integerScale = letterbox;
    }

    // =========================================================
    // 5. FIT_CROP
    // =========================================================

    Politique crop;

    if (!referenceExiste)
    {
        // Sans référence, on utilise FOLLOW_WINDOW.
        crop = follow;
    }
    else
    {
        // Le viewport occupe toujours toute la fenêtre.
        crop.vx = 0;
        crop.vy = 0;
        crop.vw = W;
        crop.vh = H;

        // Comparaison des rapports sans division.
        //
        // W * RH > H * RW signifie que la fenêtre
        // est proportionnellement plus large.
        if (W * RH > H * RW)
        {
            // La largeur du monde reste RW.
            crop.mw = RW;

            // On calcule la hauteur du monde visible.
            crop.mh = arrondi(RW * H, W);
        }
        else
        {
            // La hauteur du monde reste RH.
            crop.mh = RH;

            // On calcule la largeur du monde visible.
            crop.mw = arrondi(RH * W, H);
        }
    }

    // =========================================================
    // 6. MANUAL
    // =========================================================

    Politique manual;

    // MANUAL conserve l'ancien viewport.
    manual.vx = 0;
    manual.vy = 0;
    manual.vw = AW;
    manual.vh = AH;

    // Le monde visible correspond à l'ancienne taille.
    manual.mw = AW;
    manual.mh = AH;

    // =========================================================
    // AFFICHAGE DES SIX POLITIQUES
    // =========================================================

    afficher("FOLLOW_WINDOW", follow);
    afficher("STRETCH", stretch);
    afficher("FIT_LETTERBOX", letterbox);
    afficher("INTEGER_SCALE", integerScale);
    afficher("FIT_CROP", crop);
    afficher("MANUAL", manual);

    // =========================================================
    // CALCUL DE BANDES
    // =========================================================

    int bandes = 0;

    // Une politique a des bandes si son viewport
    // est plus étroit OU plus bas que la fenêtre.
    Politique politiques[] =
    {
        follow,
        stretch,
        letterbox,
        integerScale,
        crop,
        manual
    };

    for (const Politique& p : politiques)
    {
        if (p.vw < W || p.vh < H)
        {
            bandes++;
        }
    }

    std::cout << "BANDES " << bandes << std::endl;

    // =========================================================
    // CALCUL DE LA DÉFORMATION
    // =========================================================

    bool deformation = false;

    if (referenceExiste &&
        W * RH != H * RW)
    {
        deformation = true;
    }

    if (deformation)
    {
        std::cout << "DEFORMATION OUI" << std::endl;
    }
    else
    {
        std::cout << "DEFORMATION NON" << std::endl;
    }

    return 0;
}
