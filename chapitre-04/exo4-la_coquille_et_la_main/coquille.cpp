#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"

#include "NKMath/NKMath.h"
#include "NKTime/NkTime.h"


class Fenetre : public nkentseu::renderer::NkCanvasApp{
    private :
    nkentseu::math::NkRect2f carre{20, 20, 50, 50};
    nkentseu::float32 deltaTime = 100.f; // Vitesse par seconde

    public :
        Fenetre() {
            Config().title = "Fenetre nue";
            Config().width = 1200;
            Config().height = 600;
            Config().clearColor = nkentseu::renderer::NkColor2D{36, 36, 36, 255};
        }

        bool OnInit() override {
            
            return true;
        }

        void OnUpdate(nkentseu::float32 deltaTime) override{
			//nkentseu::float32 deltaTime = 100.f; // Vitesse par seconde
		}

        void OnRender(nkentseu::renderer::NkRenderWindow &target) override {
			nkentseu::renderer::NkRenderer2D &c2d = target.GetRenderer2D();
            c2d.DrawFilledRect(carre, nkentseu::renderer::NkColor2D{255, 0, 0, 255});
		}

        bool OnEvent(const nkentseu::NkEvent &event) override {
			if (auto* kp = event.As<nkentseu::NkKeyPressEvent>()) {
            if (kp->GetKey() == nkentseu::NkKey::NK_UP){
                carre.y -= deltaTime;
            }
            if (kp->GetKey() == nkentseu::NkKey::NK_DOWN){
                carre.y += deltaTime;
            }
            if (kp->GetKey() == nkentseu::NkKey::NK_RIGHT){
                carre.x += deltaTime;
            }
            if (kp->GetKey() == nkentseu::NkKey::NK_LEFT){
                carre.x -= deltaTime;
            }
        }
			return false;
		}
};

int nkmain(const nkentseu::NkEntryState &state){
    return nkentseu::renderer::NkCanvasApp::Run<Fenetre>(state);
}
