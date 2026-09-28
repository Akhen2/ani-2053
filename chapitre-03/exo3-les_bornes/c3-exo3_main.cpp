#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Ma fenêtre";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.minWidth = 560;
    cfg.minHeight = 390;

    // 2) Créer la fenêtre
    NkWindow window(cfg);
    math::NkVec2u sz = window.GetSize();

    std::cout << sz.width << std::endl;
    std::cout << sz.height << std::endl;

    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale 
    while (window.IsOpen()) {
      while (NkEvent* ev = NkEvents().PollEvent()) {
        if (ev->Is<NkWindowCloseEvent>()) {
            window.Close();          // l'utilisateur veut fermer
        }
        else if (auto* kp = ev->As<NkKeyPressEvent>()) {
            if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
        }
        if(auto* vz = ev -> As<NkWindowResizeEvent>()){
            math::NkVec2u sz = window.GetSize();

            std::cout << "Nouvelle taille est : " << sz.width << " , " << sz.height << std::endl;
        }
    }

    }

    return 0;

}
