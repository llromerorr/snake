#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Pixel.hpp"
#include "Screen.hpp"
#include "Snake.hpp"
#include "HandleInput.hpp"
#include "FoodGenerator.hpp"

class Game
{
    float refresh = 60;
    bool gameOver = false;
    Screen screen = Screen(640, 480);
    Snake player = Snake(screen);
    FoodGenerator food = FoodGenerator(screen);

    public:
    Game ( ) { }
    int keyboardInput();
    void init();
    void start();
};

int Game::keyboardInput()
{
    HandleInput :: updateKey();
    
    switch(HandleInput :: getKey())
    {
        case ESCAPE:
            if(pregunta("Do you want to exit?"))
                this->gameOver = true;
    }
}

void Game::init()
{
    this->screen.init();
    screen.setColorBackground(Color(38,50,56));

    this->player.setHeadPosition(Random::get(0, this->screen.getPixelByX() - 1), Random::get(0, this->screen.getPixelByY() - 1));
    this->player.setSize(Random::get(3, 5));
    this->player.setDirection(Random::get(0, 3));
    this->player.setHeadColor(Color(33,150,243));
    this->player.init();
    this->food.init();
}

void Game::start()
{   
    while(!this->gameOver)
    {
        keyboardInput();
        this->screen.drawBackgroud();
        this->food.update();

        // head-body collision
        if(this->player.update())
        {
            this->screen.setColorBackground(Color(200, 10, 45));
            this->screen.drawBackgroud();
            this->player.draw();
            this->player.drawHead();
            this->screen.update();
            if (!miniwin :: pregunta("Game Over, do you want to try again?"))
            {
                this->gameOver = true;
                break;
            }
            else
            {
                this->init();
                continue;
            }
        }

        this->screen.update(refresh);
    }

    screen.close();
}

#endif
