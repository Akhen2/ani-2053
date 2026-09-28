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
       
        if (auto* kp = ev->As<NkKeyPressEvent>()) {
        switch (kp->GetKey()) {
        case NkKey::NK_ESCAPE: window.Close();       break;
        case NkKey::NK_Z:  player.Up();        break;
        case NkKey::NK_S:  player.Down();        break;
        case NkKey::NK_Q:  player.Left();        break;
        case NkKey::NK_D:  player.Right();        break;
        default: break;
            }
        }
    }

    }

    return 0;

}
   