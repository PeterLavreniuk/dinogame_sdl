//
// Created by lavreniuk on 20.09.2020.
//

#ifndef DINOGAME_CACTUS_H
#define DINOGAME_CACTUS_H

#include "DummySprite.h"

enum CactusType{
    SMALL_CACTUS_1,
    SMALL_CACTUS_2,
    BIG_CACTUS_1,
    BIG_CACTUS_2
};

enum CactusFrame{
    SMALL_CACTUS_FRAME_1 = 0,
    SMALL_CACTUS_FRAME_2 = 1,
    BIG_CACTUS_FRAME_1 = 2,
    BIG_CACTUS_FRAME_2 = 3,
    CACTUS_FRAME_TOTAL_COUNT = 4
};

class Cactus {
private:
    float x, y, speed;
    CactusType type;
    DummySprite* sprite = nullptr;
    SDL_Rect frame;
public:
    Cactus(float x, float y, float speed, DummySprite* sprite, SDL_Rect frame);
    void update();
    void render(SDL_Renderer* renderer);
    bool isAlive () const { return this->x >= -10; }
};


#endif //DINOGAME_CACTUS_H
