//
// Created by lavreniuk on 26.09.2020.
//

#ifndef DINOGAME_SCOREHANDLER_H
#define DINOGAME_SCOREHANDLER_H


#include <SDL2/SDL_rect.h>
#include "DummySprite.h"

class ScoreHandler {
private:
    enum Numbers{
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TOTAL_NUMBERS_COUNT
    };
    SDL_Rect numbers[TOTAL_NUMBERS_COUNT]{};
    DummySprite* numbersTiles = nullptr;
    int score = 0;
    void renderNumber(int x, int y, Numbers number, SDL_Renderer* renderer);
public:
    ScoreHandler() { }
    void initialize(SDL_Renderer* renderer, std::string texturePath);
    void update(int score);
    void render(SDL_Renderer* renderer);
};


#endif //DINOGAME_SCOREHANDLER_H
