#include "defs.h"
#include "graphics.h"
#include "char.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    bool startgame=true;
    bool flag=true;
    Graphics graphics;
    graphics.init();
    Mix_Chunk *gJump = graphics.loadSound("soundgame\\flapping3.mp3");
    Mix_Chunk *drop = graphics.loadSound("soundgame\\collision2.mp3");
    SDL_Texture* bird1 = graphics.loadTexture("images\\bird1.png");
    SDL_Texture* bird2 = graphics.loadTexture("images\\bird2.png");
    SDL_Texture* pipe1 = graphics.loadTexture("images\\pipe1.png");
    SDL_Texture* pipe2 = graphics.loadTexture("images\\pipe2.png");
    SDL_Texture* over = graphics.loadTexture("images\\gameover1.png");
    SDL_Texture* again = graphics.loadTexture("images\\playagain.png");
    SDL_Texture* home= graphics.loadTexture("images\\home.png");
    SDL_Texture* startbackground = graphics.loadTexture("images\\background2.png");
    SDL_Texture* flappybird = graphics.loadTexture("images\\flappybird.png");
    SDL_Texture* start = graphics.loadTexture("images\\start.png");
    SDL_Texture* exit = graphics.loadTexture("images\\exit.png");
    SDL_Texture* larrow = graphics.loadTexture("images\\larrow.png");
    SDL_Texture* rarrow = graphics.loadTexture("images\\rarrow.png");
    SDL_Texture*bird=bird1;
    setVolume(23);

    SDL_Event event;
    while(startgame){

        if (flag) {

        graphics.startPage(startbackground, flappybird, bird, start, larrow, rarrow);
        startgame=graphics.mouseClickstart();
        }


    Mouse os1;
    os1.x=1270;
    os1.y=-50;
    os1.speed=6;

    Mouse os2;
    os2.x=1750;
    os2.y=-50;
    os2.speed=6;

    Mouse os3;
    os3.x=2230;
    os3.y=-50;
    os3.speed=6;

    Mouse mouse;
    mouse.x =550 ;
    mouse.y =350;
    mouse.speed=INITIAL_SPEED;
    mouse.tiltAngle=0;



    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images\\background2.png"));

    mouse.isJumping=false ;
    bool quit = false;



    while (!quit ) {

  if(flag)
    {




    }


        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                startgame=false;
            }

        }
            if(gameOver(mouse,os1,os2,os3))
            {

                graphics.play(drop);
                graphics.renderTexture(over,140,-20);
                graphics.renderTexture(again,350,400);
                graphics.renderTexture(home,610,405);
                graphics.renderTexture(exit,1130,600);
                graphics.presentScene();

    bool restartClicked = false;
    bool homeClicked = false;
    SDL_Event mouseEvent;
    while (!restartClicked && !homeClicked) {
        while (SDL_PollEvent(&mouseEvent)) {
            if (mouseEvent.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int r=99;
                if ((x - 471)*(x-471) +(y-505)*(y-505) <= r*r) {
                    restartClicked = true;
                } else if ((x-709)*(x-709) + (y - 504)*(y-504) <= r*r) {
                    homeClicked = true;
                } else if(x>=1130&&x<=1197&&y>=600&&y<=670) {
                    startgame=false;
                    homeClicked=true;
                    restartClicked=true;
                }
            }
        }
    }

    if (restartClicked) {
        flag=false;
    } else if (homeClicked) {
        flag=true;
    }

                break;
            }
        graphics.prepareScene();


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

        background.scroll(7);
        graphics.render(background);

        graphics.renderTexture2(bird, mouse.x, mouse.y,mouse.tiltAngle);
               if(mouse.tiltAngle<90)       mouse.tiltAngle+=2;
        graphics.renderTexture(pipe1,os1.x,os1.y);
        graphics.renderTexture(pipe2,os2.x,os2.y);
        graphics.renderTexture(pipe1,os3.x,os3.y);
        int a,b,c;
        a=rand()%40;
        b=rand()%40;
        c=rand()%40;
        if(os1.x<-230) {
            os1.x=SCREEN_WIDTH;
            os1.y=-50;
        }

        os1.x-=os1.speed;
        if(os2.x<-230){
            os2.x=SCREEN_WIDTH;
            os2.y=-50;
        }
        os2.x-=os2.speed;
        if(os3.x<-230) {
            os3.x=SCREEN_WIDTH;
            os3.y=-50;
        }
        os3.x-=os3.speed;


        graphics.presentScene();

        SDL_Delay(5);
    }

}

    if (gJump != nullptr) Mix_FreeChunk( gJump);
    if (drop != nullptr) Mix_FreeChunk( drop);

    SDL_DestroyTexture(bird1);
    SDL_DestroyTexture(pipe1);
    SDL_DestroyTexture(pipe2);
    SDL_DestroyTexture(over);
    SDL_DestroyTexture(again);
    SDL_DestroyTexture(home);
    SDL_DestroyTexture(flappybird);
    SDL_DestroyTexture(start);
    SDL_DestroyTexture(exit);
    SDL_DestroyTexture(larrow);
    SDL_DestroyTexture(rarrow);


    graphics.quit();
    return 0;
}
