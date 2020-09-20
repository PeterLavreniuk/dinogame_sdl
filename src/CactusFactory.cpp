//
// Created by lavreniuk on 20.09.2020.
//

#include "CactusFactory.h"

void CactusFactory::initialize(SDL_Renderer *renderer, std::string texturePath) {
    auto cactusSprite = new DummySprite();
    cactusSprite->load(renderer, texturePath);
    this->sprite = cactusSprite;

    this->frames[SMALL_CACTUS_FRAME_1] = {0,0,34,48};
    this->frames[SMALL_CACTUS_FRAME_2] = {34*1,0,34,48};
    this->frames[BIG_CACTUS_FRAME_1] = {34*2,0,34,48};
    this->frames[BIG_CACTUS_FRAME_2] = {34*3,0,34,48};
}

Cactus *CactusFactory::Create(CactusType type, float speed) {
    if(type == BIG_CACTUS_1) {
        return new Cactus(641,132, speed, this->sprite, this->frames[BIG_CACTUS_FRAME_1]);
    }
    return nullptr;
}

Cactus *CactusFactory::Create(float speed) {
    return nullptr;
}
