//
// Created by lavreniuk on 20.09.2020.
//

#include <iostream>
#include "Dino.h"

Dino::Dino(int x, int y) {
    this->x = x;
    this->y = this->floorPosition = y;
    this->currentState = DINO_STATE_RUN;
}

Dino::~Dino() {
    if(this->sprite == nullptr)
        return;

    this->sprite->free();
    this->sprite = nullptr;
}

void Dino::render(SDL_Renderer *renderer) {
    if(this->sprite == nullptr)
        return;

    this->sprite->render(renderer, this->x, this->y, &this->frames[this->currentFrame]);
}

void Dino::update(Uint32 tickCount) {
    switch (this->currentState) {
        case DINO_STATE_RUN: {
            if(tickCount % 6 != 0)
                break;

            DinoFrame frame = (DinoFrame) (this->currentFrame + 1);
            if (frame >= 2)
                frame = DINO_FRAME_RUN_1;
            this->currentFrame = frame;
            break;
        }
        case DINO_STATE_JUMP: {
            if(this->jumpPower > 0.0f) {
                this->currentFrame = DINO_FRAME_JUM;
            }
            else{
                if(this->y == this->floorPosition) {
                    this->currentState = DINO_STATE_RUN;
                }
            }
            break;
        }
        case DINO_STATE_DIE: {
            this->currentFrame = DINO_FRAME_DIE;
            break;
        }
    }

    if(this->jumpPower > 0){
        this->y -= 4.0f;
        this->jumpPower -= 1.8f;
    }

    if(this->y != this->floorPosition && this->jumpPower <= 0.0f){
        this->y += 4.0f;
    }
}

void Dino::initialize(SDL_Renderer *renderer, std::string texturePath) {
    auto dinoSprite = new DummySprite();
    dinoSprite->load(renderer, "dino.bmp");
    this->sprite = dinoSprite;

    this->frames[DINO_FRAME_RUN_1] = {0,0,42,44};
    this->frames[DINO_FRAME_RUN_2] = {42*1,0,42,44};
    this->frames[DINO_FRAME_JUM] = {42*2,0,42,44};
    this->frames[DINO_FRAME_DIE] = {42*3,0,42,44};
    this->currentFrame = DINO_FRAME_RUN_1;
}

SDL_Rect *Dino::getCollisionBox() {
    return new SDL_Rect{(int)this->x, (int)this->y, this->frames[this->currentFrame].w, this->frames[this->currentFrame].h};
}

void Dino::kill() {
    if(this->currentState == DINO_STATE_DIE)
        return;

    this->currentState = DINO_STATE_DIE;
    update(0);
}

void Dino::jump() {
    if(this->currentState == DINO_STATE_JUMP || this->currentState == DINO_STATE_DIE)
        return;
    this->currentState = DINO_STATE_JUMP;
    this->jumpPower = 40.0f;
}
