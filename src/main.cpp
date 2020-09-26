#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "Dino.h"
#include "CactusFactory.h"
#include "ScoreHandler.h"

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
    auto cactusFactory = new CactusFactory();
    auto scoreHandler = new ScoreHandler();
    cactusFactory->initialize(gRenderer, "cactuses.bmp");
    dino->initialize(gRenderer, "dino.bmp");
    scoreHandler->initialize(gRenderer, "numbers.bmp");

    backGround = new DummySprite();
    backGround->load(gRenderer, "background.bmp");

    std::vector<Cactus*> cactuses;

    Uint32 animationTicks = 0;
    float gameSpeed = 2.0f;
    int offsetSpeed = 1;
    int score = 0;

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

        if(animationTicks % 128 == 0){
            auto cactus = cactusFactory->Create(BIG_CACTUS_1);
            cactuses.push_back(cactus);
        }

        dino->update(animationTicks);
        scoreHandler->update(score);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(gRenderer);

        backgroundOffset -= offsetSpeed;
        if(backgroundOffset < -backGround->getW()){
            backgroundOffset = 0;
        }

        backGround->render(gRenderer, backgroundOffset, 0);
        backGround->render(gRenderer, backgroundOffset + backGround->getW(), 0);
        scoreHandler->render(gRenderer);

        dino->render(gRenderer);
        for(auto &cactus : cactuses){
            cactus->update(gameSpeed);
            cactus->render(gRenderer);
        }

        cactuses.erase(std::remove_if(
                cactuses.begin(), cactuses.end(),
                [](Cactus* cactus){
                    return !cactus->isAlive();
                }), cactuses.end());

        SDL_RenderPresent(gRenderer);

        next_game_tick += 1000 / 60;
        sleep = next_game_tick - SDL_GetTicks();

        ++animationTicks;

        if(animationTicks % 16 == 0){
            ++score;
        }

        if(animationTicks % 1024 == 0){
            animationTicks = 0;
            if(gameSpeed < 15.0f){
                gameSpeed += 0.5f;
                offsetSpeed += 1;
                std::cout<<"Speed up!"<<std::endl;
            }
        }

        if( sleep >= 0 ) {
            SDL_Delay(sleep);
        }
    }

    clear();

    return 0;
}
