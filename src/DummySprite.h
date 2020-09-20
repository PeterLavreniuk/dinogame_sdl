//
// Created by lavreniuk on 20.09.2020.
//

#ifndef DINOGAME_DUMMYSPRITE_H
#define DINOGAME_DUMMYSPRITE_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <string>

class DummySprite {
private:
    SDL_Texture* texture;
    int w,h;
public:
    DummySprite();
    bool load(SDL_Renderer* renderer, std::string texturePath);
    ~DummySprite();
    void free();
    void render(SDL_Renderer* renderer, float x, float y);
    void render(SDL_Renderer* renderer, float x, float y, SDL_Rect* clip);
    int getW() const {return this->w;}
    int getH() const {return this->h;}
};


#endif //DINOGAME_DUMMYSPRITE_H
