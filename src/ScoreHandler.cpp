//
// Created by lavreniuk on 26.09.2020.
//

#include <stack>
#include "ScoreHandler.h"

void ScoreHandler::initialize(SDL_Renderer *renderer, std::string texturePath) {
    auto sprite = new DummySprite();
    sprite->load(renderer, texturePath);
    this->numbersTiles = sprite;

    this->numbers[ZERO] = {0,0,8,10};
    this->numbers[ONE] = {8*1,0,8,10};
    this->numbers[TWO] = {8*2,0,8,10};
    this->numbers[THREE] = {8*3,0,8,10};
    this->numbers[FOUR] = {8*4,0,8,10};
    this->numbers[FIVE] = {8*5,0,8,10};
    this->numbers[SIX] = {8*6,0,8,10};
    this->numbers[SEVEN] = {8*7,0,8,10};
    this->numbers[EIGHT] = {8*8,0,8,10};
    this->numbers[NINE] = {8*9,0,8,10};
}

void ScoreHandler::update(int score) {
    this->score = score;
}

void ScoreHandler::render(SDL_Renderer* renderer) {
    if(this->score == 0){
        renderNumber(12,20,ZERO,renderer);
        return;
    }

    auto temp = this->score;

    std::stack<int> stack;
    while(temp){
        stack.push(temp % 10);
        temp /= 10;
    }

    auto count = 0;

    while(!stack.empty()){
        auto x = 10 + (8 * count) + (count * 2);
        auto digit = stack.top();
        renderNumber(x, 20, (Numbers)digit, renderer);
        stack.pop();
        ++count;
    }
}

void ScoreHandler::renderNumber(int x, int y, Numbers number, SDL_Renderer* renderer) {
    this->numbersTiles->render(renderer,x,y,&numbers[number]);
}
