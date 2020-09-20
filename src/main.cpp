#include <iostream>
#include <SDL2/SDL.h>
#include "Dino.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
DummySprite* backGround = nullptr;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT= 240;
int backgroundOffset = 0;

bool init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << SDL_GetError();
        return false;
    }

    gWindow = SDL_CreateWindow("Dino game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if(gWindow == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void clear(){
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    SDL_Quit();
}

int main() {
    if(!init()){
        std::cout << "init failed" << std::endl;
        clear();
        return 0;
    }

    auto quit = false;
    SDL_Event e;

    auto sleep = 0;
    Uint32 next_game_tick = SDL_GetTicks();

    const Uint8* state = SDL_GetKeyboardState(NULL);

    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    auto dino = new Dino(64,132);
    dino->initialize(gRenderer, "dino.bmp");

    backGround = new DummySprite();
    backGround->load(gRenderer, "background.bmp");

    Uint32 animationTicks = 1;

    while(!quit){
        if(state[SDL_SCANCODE_ESCAPE]){
            quit = true;
        }

        if(state[SDL_SCANCODE_SPACE])
            dino->jump();

        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }

        dino->update(animationTicks);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(gRenderer);

        --backgroundOffset;
        if(backgroundOffset < -backGround->getW()){
            backgroundOffset = 0;
        }

        backGround->render(gRenderer, backgroundOffset, 0);
        backGround->render(gRenderer, backgroundOffset + backGround->getW(), 0);

        dino->render(gRenderer);

        SDL_RenderPresent(gRenderer);

        next_game_tick += 1000 / 60;
        sleep = next_game_tick - SDL_GetTicks();

        if( sleep >= 0 ) {
            SDL_Delay(sleep);
            ++animationTicks;
            if(animationTicks > 257)
                animationTicks = 1;
        }
    }

    clear();

    return 0;
}
