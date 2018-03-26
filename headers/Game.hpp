#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Pixel.hpp"
#include "Screen.hpp"
#include "Snake.hpp"
#include "HandleInput.hpp"

class Game
{
    float refresh = 60;
    bool gameOver = false;
    Screen screen = Screen(640, 480);
    Snake player = Snake(screen);

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
            break;
        case ESPACIO:
            this->start();
            break;
        case F1:
            if(refresh < 90)
                refresh += 30;
            break;
        case F2:
            if(refresh > 30)   
                refresh -= 30;
            break;
        case F3:
            this->screen.setColorBackground(Color(200, 10, 45));
            break;
        case F4:
            this->screen.setColorBackground(Color(38, 50, 56));
            break;
    }
}

void Game::init()
{
    this->screen.init();
    screen.setColorBackground(Color(38,50,56));

    this->player.init();
}

void Game::start()
{
    this->init();
    
    while(!this->gameOver)
    {
        keyboardInput();
        this->screen.drawBackgroud();
        this->player.update();
        this->screen.update(refresh);
    }

    screen.close();
}

#endif
