#ifndef _CHAR__H
#define _CHAR__H
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

const int birdWidth=70;
const int birdHeight=60;
const int pipeWidth=118;
const int pipeHeight=748;
const int GAP_WIDTH = 118 ;
const int GAP_HEIGHT = 173;
const int GAP_TOP = 337 ;

struct Mouse {
    int x, y,speed;
    bool isJumping;
    Uint32 lastJumpTime;
    int tiltAngle;
    int dx = 0, dy = 0;
    void move() {
        x += dx;
        y += dy;
    }
    void freeFall()
    {
        dx=0;
        dy=GRAVITY;
        isJumping=false;
    }
    void makeAjump()
    {
        if(!isJumping){
        dx=0;
        dy=-speed;}
        isJumping=true;
        SDL_Delay(5);

    }

};
  bool isCollision (SDL_Rect rect1,SDL_Rect rect2)
{
    return SDL_HasIntersection(&rect1, &rect2);
}

bool isCollisionwithpipe(Mouse mouse,Mouse os1,Mouse os2,Mouse os3)
{
    SDL_Rect birdRect = { mouse.x, mouse.y, birdWidth, birdHeight };
    SDL_Rect pipe1Rect = { os1.x, os1.y, pipeWidth, pipeHeight };
    SDL_Rect pipe2Rect = { os2.x, os2.y, pipeWidth, pipeHeight };
    SDL_Rect pipe3Rect = { os3.x, os3.y, pipeWidth, pipeHeight };

    if ((birdRect.x + birdWidth > pipe1Rect.x && birdRect.x < pipe1Rect.x + pipeWidth) ||
    (birdRect.x + birdWidth > pipe2Rect.x && birdRect.x < pipe2Rect.x + pipeWidth) ||
    (birdRect.x + birdWidth > pipe3Rect.x && birdRect.x < pipe3Rect.x + pipeWidth)) {

        if (!(birdRect.y > GAP_TOP && birdRect.y + birdHeight < GAP_TOP + GAP_HEIGHT)) {

        if (isCollision(birdRect, pipe1Rect)  || isCollision(birdRect, pipe3Rect)) {

            return true;
        }
    }
        if (!(birdRect.y > 152 && birdRect.y + birdHeight < 152 + GAP_HEIGHT))
     {
         if(isCollision(birdRect,pipe2Rect))
         {
             return true;
         }
     }


}
    return false;
}



bool gameOver(const Mouse& mouse,Mouse os1,Mouse os2,Mouse os3) {
    if(mouse.y < 0 || mouse.y >= SCREEN_HEIGHT-60) return 1;
    if(isCollisionwithpipe(mouse,os1,os2,os3)) return 1;
    return 0;
}

#endif
