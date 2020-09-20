//
// Created by lavreniuk on 20.09.2020.
//

#ifndef DINOGAME_CACTUSFACTORY_H
#define DINOGAME_CACTUSFACTORY_H


#include "DummySprite.h"
#include "Cactus.h"

class CactusFactory {
private:
    DummySprite* sprite;
    SDL_Rect frames[CACTUS_FRAME_TOTAL_COUNT];
public:
    void initialize(SDL_Renderer* renderer, std::string texturePath);
    Cactus* Create(CactusType type, float speed);
    Cactus* Create(float speed);
};


#endif //DINOGAME_CACTUSFACTORY_H
