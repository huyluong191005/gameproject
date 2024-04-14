
#include "defs.h"
#include "graphics.h"
#include <iostream>
using namespace std;
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int SDL_main(int argc, char* argv[])
{
     Graphics graphics;
    graphics.init();

     SDL_Texture* background = graphics.loadTexture("images\\bg2.png");
    graphics.prepareScene(background);

    graphics.presentScene();
    waitUntilKeyPressed();
    SDL_DestroyTexture( background );
    background = NULL;


    graphics.quit();
    return 0;


}




