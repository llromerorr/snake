#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include "Pixel.hpp"
#include "HandleInput.hpp"
#include "Root.hpp"
#include <vector>
#include "Screen.hpp"
#include "random.hpp"
#include "FoodGenerator.hpp"

using Random = effolkronium::random_static;
using namespace std;

class Snake
{
    Color headColor = Color (33,150,243);
    Color bodyColor = Color (255, 255, 255);
    Screen screen = Screen(200, 200);
    int direction = Random::get(0, 3);
    float speed = 0;
    Position headPosition = Position(0, 0);
    int size = Random::get(3, 12);
    vector<Pixel> body = vector<Pixel>(3);

    public:

    Snake ( Screen screen ) { this->screen = screen; }
    Snake ( Screen screen, int direction ) { this->screen = screen; this->direction = direction; }
    Snake ( Screen screen, int direction, float speed ) { this->screen = screen; this->direction = direction; this->speed = speed; }
    Snake ( Screen screen, int direction, float speed, Color headColor ) { this->screen = screen; this->direction = direction; this->speed = speed; this->headColor = headColor; }

    vector<Pixel> getBodyVector() { return this->body; }
    Position getHeadPosition() { return this->headPosition; }

    void draw() { for(int i = 0; i < body.size(); i++) body[i].draw(); }
    void drawHead ( ) { this->body.front().draw(); }
    void setDirection ( int direction) { this->direction = direction; }
    void setScreen(Screen screen){ this->screen = screen; }
    void setSize ( int size ) { this->size = size; }
    void setHeadPosition(int x, int y) { this->headPosition.setx(x * this->body.front().getSize()); this->headPosition.sety(y * this->body.front().getSize()); }
    void setHeadColor ( Color color ) { this->headColor = color; }
    void setBodyColor ( Color color )
    {
        this->bodyColor = color;
        for(int i = this->body.size(); i > 0; i--)
            body[i].setColor(color);
    }

    void eat ( )
    {
        if(this->body.front().getPixelPositionX() == FoodGenerator :: getPosition().getx() && this->body.front().getPixelPositionY() == FoodGenerator :: getPosition().gety() )
        {
            this->size++;
            body.resize(this->size);
            body[this->size - 1] = Pixel(this->body[size - 2].getPositionByPixel());
            FoodGenerator :: init(body, headPosition);
        }   
    }
    
    bool bodyCollision ( )
    {   bool result = false;

        for(int i = body.size() - 1; i > 0; i--)
            if(this->body.front().getPixelPositionX() == body[i].getPosition().getx() && this->body.front().getPixelPositionY() == body[i].getPosition().gety())
                result = true;
        
        return result;
    }

    void init()
    {
        body.resize(this->size);
        body.front().setPosition(this->headPosition.getx(), this->headPosition.gety());
        body.front().setColor(this->headColor);

        switch(this->direction)
        {
            case 0:
                for(int i = 1, y = this->headPosition.gety(); i < body.size(); i++, y++)
                {
                    body[i] = Pixel(this->headPosition.getx(), y);
                    body[i].setColor(this->bodyColor);
                }
                break;
            case 1:
                for(int i = 1, x = this->headPosition.getx(); i < body.size(); i++, x--)
                {
                    body[i] = Pixel(x, this->headPosition.gety());
                    body[i].setColor(this->bodyColor);
                }
                break;
            case 2:
                for(int i = 1, y = this->headPosition.gety(); i < body.size(); i++, y--)
                {
                    body[i] = Pixel(this->headPosition.getx(), y);
                    body[i].setColor(this->bodyColor);
                }
                break;
            case 3:
                for(int i = 1, x = this->headPosition.getx(); i < body.size(); i++, x++)
                {
                    body[i] = Pixel(x, this->headPosition.gety());
                    body[i].setColor(this->bodyColor);
                }
                break;
        }
    }

    bool update()
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

        this->eat();

        //draw snake
        for(int i = 0; i < body.size(); i++)
            body[i].draw();
        
        if(this->bodyCollision())
            return 1;
        else
            return 0;
    }
};

#endif