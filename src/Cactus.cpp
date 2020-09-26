//
// Created by lavreniuk on 20.09.2020.
//

#include "Cactus.h"

Cactus::Cactus(float x, float y, CactusType type,
               DummySprite *sprite, SDL_Rect frame) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->frame = frame;
    this->sprite = sprite;
}

void Cactus::update(float speed) {
    this->x -= speed;
}

void Cactus::render(SDL_Renderer* renderer) {
    if(this->sprite == nullptr)
        return;

    this->sprite->render(renderer, this->x, this->y, &this->frame);
}