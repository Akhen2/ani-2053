#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Ma fenêtre";
    cfg.width  = 1280;
    cfg.height = 720;

    // 2) Créer la fenêtre
    NkWindow window;
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
    }

    }

    return 0;

}
   