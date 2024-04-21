#include "defs.h"
#include "graphics.h"
#include "char.h"
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
void playSoundIfNotPlaying(Mix_Chunk* sound) {
    if (Mix_Playing(-1) == 0) {
        Mix_PlayChannel(-1, sound, 0);
    }
}
int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();
    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images\\background2.png"));
    Mix_Chunk *gJump = graphics.loadSound("soundgame\\flapping3.mp3");
    Mix_Chunk *drop = graphics.loadSound("soundgame\\collision2.mp3");
    SDL_Texture* bird = graphics.loadTexture("images\\bird1.png");
    SDL_Texture* pipe1 = graphics.loadTexture("images\\pipe1.png");
    SDL_Texture* pipe2 = graphics.loadTexture("images\\pipe2.png");
    SDL_Texture* over = graphics.loadTexture("images\\gameover1.png");
    SDL_Texture* again = graphics.loadTexture("images\\playagain.png");

    Mouse os1;
    os1.x=870;
    os1.y=-50;
    os1.speed=6;

    Mouse os2;
    os2.x=1350;
    os2.y=-50;
    os2.speed=6;

    Mouse os3;
    os3.x=1830;
    os3.y=-50;
    os3.speed=6;

    Mouse mouse;
    mouse.x =450 ;
    mouse.y =350;
    mouse.speed=INITIAL_SPEED;
    mouse.isJumping=false;
    bool quit = false;
    SDL_Event event;

    while (!quit ) {
            if(gameOver(mouse,os1,os2,os3))
            {

                graphics.play(drop);
                graphics.renderTexture(over,140,-20);
                graphics.renderTexture(again,480,400);
                graphics.presentScene();
                waitUntilKeyPressed();
                break;
            }
        graphics.prepareScene();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


        if (currentKeyStates[SDL_SCANCODE_SPACE]&&!mouse.isJumping)
        {
            mouse.makeAjump();
            playSoundIfNotPlaying(gJump);
            mouse.tiltAngle=-45;
        }
        else  {
                mouse.freeFall();
        }
        mouse.move();

        background.scroll(6);
        graphics.render(background);

        graphics.renderTexture2(bird, mouse.x, mouse.y,mouse.tiltAngle);
               if(mouse.tiltAngle<10) mouse.tiltAngle+=2;

        graphics.renderTexture(pipe1,os1.x,os1.y);
        graphics.renderTexture(pipe2,os2.x,os2.y);
        graphics.renderTexture(pipe1,os3.x,os3.y);

        if(os1.x<-230) os1.x=SCREEN_WIDTH;
        os1.x-=os1.speed;
        if(os2.x<-230) os2.x=SCREEN_WIDTH;
        os2.x-=os2.speed;
        if(os3.x<-230) os3.x=SCREEN_WIDTH;
        os3.x-=os3.speed;


        graphics.presentScene();

        SDL_Delay(5);
    }

    if (gJump != nullptr) Mix_FreeChunk( gJump);
    if (drop != nullptr) Mix_FreeChunk( drop);


    SDL_DestroyTexture(bird);
    SDL_DestroyTexture(pipe1);
    SDL_DestroyTexture(over);
    SDL_DestroyTexture(again);
    graphics.quit();

    return 0;
}
