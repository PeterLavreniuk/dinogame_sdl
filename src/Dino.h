//
// Created by lavreniuk on 20.09.2020.
//

#ifndef DINOGAME_DINO_H
#define DINOGAME_DINO_H


#include "DummySprite.h"

class Dino {
private:
    enum DinoState{
        DINO_STATE_RUN,
        DINO_STATE_JUMP,
        DINO_STATE_DIE
    };
    enum DinoFrame{
        DINO_FRAME_RUN_1 = 0,
        DINO_FRAME_RUN_2 = 1,
        DINO_FRAME_JUM = 2,
        DINO_FRAME_DIE = 3,
        DINO_FRAME_TOTAL_COUNT = 4
    };

    float x, y, floorPosition;
    float jumpPower = 0.0f;
    DinoState currentState;
    DinoFrame currentFrame;
    SDL_Rect frames[DINO_FRAME_TOTAL_COUNT];
    DummySprite* sprite = nullptr;

public:
    Dino(int x, int y);
    ~Dino();
    void initialize(SDL_Renderer* renderer, std::string texturePath);
    bool isAlive() const {return this->currentState != DINO_STATE_DIE;}
    int getX() const {return this->x;}
    int getY() const {return this->y;}
    SDL_Rect* getCollisionBox();
    void render(SDL_Renderer* renderer);
    void update(Uint32 tickCount);
    void kill();
    void jump();
};


#endif //DINOGAME_DINO_H
