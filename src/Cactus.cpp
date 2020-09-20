//
// Created by lavreniuk on 20.09.2020.
//

#include "Cactus.h"

Cactus::Cactus(float x, float y, float speed, DummySprite *sprite, SDL_Rect frame) {
    this->x = x;
    this->y = y;
    this->frame = frame;
    this->sprite = sprite;
    this->speed = speed;
}

void Cactus::update() {
    this->x -= speed;
}

void Cactus::render(SDL_Renderer* renderer) {
    if(this->sprite == nullptr)
        return;

    this->sprite->render(renderer, this->x, this->y, &this->frame);
}