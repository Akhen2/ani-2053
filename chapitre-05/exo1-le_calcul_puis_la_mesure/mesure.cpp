#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLogger.h"
#include <iostream>

#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"

#include "NKMath/NKMath.h"

#include "NKImage/NKImage.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "NKImage";
    cfg.width  = 1280;
    cfg.height = 720;

    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    //Cible
    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_DX11;

    renderer::NkRenderWindow rendererWindow(window, desc);

    if(!rendererWindow.IsValid()){
        return 2;
    }

    NkImage img;

    if(!img.Load("assets/Alde.jpg")){
        return -1;
    }

     /*if(!img.Load("assets/Alba.jpg")){
        return -1;
    }

    if(!img.Load("assets/Dessin.png")){
        return -1;
    }

    if(!img.Load("assets/fenetre.png")){
        return -1;
    }*/


    int large = img.Width();
    int haut = img.Height();
    int pixel = img.BytesPP();
    uint64 sum = static_cast<uint64>(img.Width()) *  img.Height() * img.BytesPP();

    logger.Info("assets/Alde.jpg -> W : {0}, H : {1}, Bpp : {2}, S : {3} ", img.Width(),  img.Height(), img.BytesPP(), sum);
    
    renderer::NkTexture texture;

    if(!texture.LoadFromImage(*rendererWindow.GetRenderer(), img)){
        return 1;
    }

    renderer::NkRectangleShape rect(math::NkVec2f(img.Width(), img.Height()));
    rect.SetTexture(&texture);

    // 3) Boucle principale 
    while (window.IsOpen()) {
      while (NkEvent* ev = NkEvents().PollEvent()) {
        if (ev->Is<NkWindowCloseEvent>()) {
            window.Close();          // l'utilisateur veut fermer
        }

    }

    rendererWindow.Clear(renderer::NkColor2D(250, 250, 250, 255)); // Couleur en arrière plan
    renderer::NkRenderer2D &c2d = rendererWindow.GetRenderer2D();

    c2d.Draw(rect);

    rendererWindow.Display();

    }

    return 0;

}
   