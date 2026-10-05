#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"

class Fenetre : public nkentseu::renderer::NkCanvasApp{

    public :
        Fenetre() {
            Config().title = "Fenetre nue";
            Config().width = 1200;
            Config().height = 800;
            Config().clearColor = nkentseu::renderer::NkColor2D{250, 100, 0, 255};
        }

        bool OnInit() override {

            return true;
        }
};

int nkmain(const nkentseu::NkEntryState &state){
    return nkentseu::renderer::NkCanvasApp::Run<Fenetre>(state);
}
