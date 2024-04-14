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
         SDL_Texture* background = graphics.loadTexture("images\\background.png");
    graphics.prepareScene(background);

    graphics.presentScene();
   // waitUntilKeyPressed();


    SDL_Texture *pipe1 = graphics.loadTexture("images\\pipe2.png");
     graphics.renderTexture(pipe1, 25,- 70);
     graphics.presentScene();
   // waitUntilKeyPressed();
    SDL_Texture *pipe3 = graphics.loadTexture("images\\pipe1.png");
     graphics.renderTexture(pipe3, 350,- 80);
     graphics.presentScene();

     SDL_Texture *pipe2 = graphics.loadTexture("images\\pipe2.png");
     graphics.renderTexture(pipe2, 675, -70);
     graphics.presentScene();

      SDL_Texture *bird1 = graphics.loadTexture("images\\bird1.png");
     graphics.renderTexture(bird1, 290,120);
     graphics.presentScene();
    waitUntilKeyPressed();
    SDL_DestroyTexture( pipe2 );
    pipe2 = NULL;
    SDL_DestroyTexture( pipe1 );
    pipe1 =NULL;
    pipe3 = NULL;SDL_DestroyTexture( pipe3 );
    pipe3 = NULL;
    SDL_DestroyTexture( bird1 );
    bird1 =NULL;
    SDL_DestroyTexture( background );
    background = NULL;

    return 0;

}




