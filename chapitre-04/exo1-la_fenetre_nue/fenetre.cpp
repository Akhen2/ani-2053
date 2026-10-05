#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"

using namespace nkentseu::renderer;
class Fenetre : public NkCanvasApp{

    public :
        Fenetre() {
            Config().title = "Fenetre nue";
            Config().width = 1200;
            Config().height = 800;
            Config().clearColor = NkColor2D{250, 100, 0, 255};
        }

        bool OnInit() override {

            return true;
        }
};

int nkmain(const nkentseu::NkEntryState &state){
    return NkCanvasApp::Run<Fenetre>(state);
}
