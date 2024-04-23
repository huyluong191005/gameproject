#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <vector>
#include <SDL_mixer.h>
#include <bits/stdc++.h>
struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 ) { scrollingOffset = width; }
    }
};

struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;

	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
        }

    }

	void prepareScene(SDL_Texture * background = nullptr)
    {
        SDL_RenderClear(renderer);
        if (background != nullptr) SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()
    {
        Mix_Quit();
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void render(const ScrollingBackground& background) {
        renderTexture(background.texture, background.scrollingOffset, 0);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0);
    }
    void renderTexture2(SDL_Texture* texture, int x, int y, float angle) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;


    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

    SDL_Point center = { dstRect.w / 2, dstRect.h / 2 };

    SDL_RenderCopyEx(renderer, texture, NULL, &dstRect, angle, &center, SDL_FLIP_NONE);
}


        Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }
     Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
               "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }
    void startPage(SDL_Texture *background,SDL_Texture* flappybird,SDL_Texture* bird,SDL_Texture* start,SDL_Texture* larrow,SDL_Texture* rarrow)
    {
        renderTexture(background,0,0);
        renderTexture(flappybird,185,50);
        renderTexture(start,510,570);
       // renderTexture(larrow,400,340);
        // renderTexture(rarrow,670,340);
        renderTexture(bird,550,350);

        presentScene();
    }
    bool mouseClickrect(int Tx,int Ty,int w,int h)
    {
        int x,y;
        SDL_Event event;
        while(SDL_WaitEvent(&event))
        {
            SDL_GetMouseState(&x, &y);

            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                if(x>=Tx&&x<=Tx+w)
                {
                    if(y>=Ty&&y<=Ty+h)
                    {
                        return true;
                    }
                }
            }


        }
        return false;

    }
 bool mouseClickstart() {
    int x, y;
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&x, &y);
            if (x >= 510 && x <= 510 + 166 && y >= 570 && y <= 570 + 70) {
                return true;
            }
        }
    }
    return false;
}



};
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
void adjustVolume(int change) {
    int volume = Mix_Volume(-1, -1);
    volume += change;
    if(volume < 0) volume = 0;
    if(volume > 128) volume = 128;
    Mix_Volume(-1, volume);
}
void setVolume(int volume) {
    if(volume < 0) volume = 0;
    if(volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
    Mix_Volume(-1, volume);
}

#endif // _GRAPHICS__H
