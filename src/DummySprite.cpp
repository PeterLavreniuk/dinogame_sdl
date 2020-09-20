//
// Created by lavreniuk on 20.09.2020.
//

#include "DummySprite.h"

DummySprite::DummySprite() {

}

bool DummySprite::load(SDL_Renderer* renderer, std::string texturePath) {
    free();
    SDL_Surface* loadedSurface = SDL_LoadBMP(texturePath.c_str());

    if(loadedSurface == nullptr)
        return false;

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));

    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(loadedTexture == nullptr){
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    this->w = loadedSurface->w;
    this->h = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    this->texture = loadedTexture;

    return loadedTexture != nullptr;
}

void DummySprite::free() {
    if(this->texture == nullptr)
        return;
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
    this->w = 0;
    this->h = 0;
}

DummySprite::~DummySprite() {
    free();
}

void DummySprite::render(SDL_Renderer *renderer, float x, float y) {
    const SDL_Rect renderShape = { (int)x, (int)y, this->w, this->h };
    SDL_RenderCopy(renderer, this->texture, nullptr, &renderShape);
}

void DummySprite::render(SDL_Renderer *renderer, float x, float y, SDL_Rect* clip) {
    SDL_Rect renderShape = { (int)x, (int)y, this->w, this->h };
    if(clip != nullptr){
        renderShape.w = clip->w;
        renderShape.h = clip->h;
    }
    SDL_RenderCopy(renderer, this->texture, clip, &renderShape);
}
