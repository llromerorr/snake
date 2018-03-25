#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include "Pixel.hpp"
#include "HandleInput.hpp"
#include <vector>
#include "Screen.hpp"

using namespace std;

class Snake
{
    Color headColor = Color (33,150,243);
    Color bodyColor = Color (255, 255, 255);
    Screen screen = Screen(200, 200);
    vector<Pixel> body;
    int direction = 1;
    float speed = 0;
    int size = 12;

    public:

    Snake ( ) { }
    Snake ( Screen screen ) { this->screen = screen; }
    Snake ( Screen screen, int direction ) { this->screen = screen; this->direction = direction; }
    Snake ( Screen screen, int direction, float speed ) { this->screen = screen; this->direction = direction; this->speed = speed; }
    Snake ( Screen screen, int direction, float speed, Color headColor ) { this->screen = screen; this->direction = direction; this->speed = speed; this->headColor = headColor; }

    void setScreen(Screen screen){ this->screen = screen; }
    void setHeadColor ( Color color ) { this->headColor = color; }
    void setBodyColor ( Color color )
    {
        this->bodyColor = color;
        for(int i = this->body.size(); i > 0; i--)
            body[i].setColor(color);
    }

    void init(int x, int y)
    {
        body.resize(this->size);
        for(int i = 0; i < body.size(); i++, x--)
        {
            body[i] = Pixel(x, y);
            body[i].setColor(this->bodyColor);
        }

        body.front().setColor(this->headColor);
    }

    void init(int x, int y, int direction)
    {
        this->direction = direction;

        body.resize(this->size);
        for(int i = 0; i < body.size(); i++, x--)
            body[i] = Pixel(x, y);

        body.front().setColor(Color(33,150,243));
    }

    void update()
    {
        if(HandleInput :: getKey() == ARRIBA && this->direction != 2)
            this->direction = 0;
        else if(HandleInput :: getKey() == DERECHA && this->direction != 3)
            this->direction = 1;
        else if(HandleInput :: getKey() == ABAJO && this->direction != 0)
            this->direction = 2;
        else if(HandleInput :: getKey() == IZQUIERDA && this->direction != 1)
            this->direction = 3;
        
        //move body
        for(int i = body.size() - 1; i > 0; i--)
        {
            body[i].setX(body[i - 1].getX());
            body[i].setY(body[i - 1].getY());
        }

        //move head
        switch(this->direction)
        {
            case 0:
                if(body.front().getY() <= 0)
                    body.front().moveY(screen.getPixelByY() - 1);
                else
                    body.front().moveY(-1);
                break;
            case 1:
                if(body.front().getX() >= screen.getPixelByX() - 1)
                    body.front().moveX(-(screen.getPixelByX() - 1));
                else
                    body.front().moveX(1);
                break;
            case 2:
                if(body.front().getY() >= screen.getPixelByY() - 1)
                    body.front().moveY(-(screen.getPixelByY() - 1));
                else
                    body.front().moveY(1);
                break;
            case 3:
                if(body.front().getX() <= 0)
                    body.front().moveX(screen.getPixelByX() - 1);
                else
                    body.front().moveX(-1);
                break;
        }

        //draw snake
        for(int i = 0; i < body.size(); i++)
            body[i].draw();
    }
};

#endif