#ifndef _PIXEL_H_
#define _PIXEL_H_

#include "miniwin.h"
#include "Root.hpp"

using namespace Root;

class Pixel
{
    int         size = 20;
    int         x = 0, y = 0;
    Color       color = Color(255, 255, 255);

    public:
    Pixel(void) { }
    Pixel(Color color) { this->color = color; }
    Pixel(Color color, Position position) { this->color = color; this->setX(position.getx()); this->setY(position.gety()); }
    Pixel(Color color, int size) { this->color = color; this->size = size; }
    Pixel(Color color, int size, Position position) { this->color = color; this->size = size; this->setX(position.getx()); this->setY(position.gety()); }
    Pixel(Position position) { this->setX(position.getx()); this->setY(position.gety()); }
    Pixel(int x, int y) { this->setX(x); this->setY(y); }

    void setSize (int size) { this->size = size; }
    void setColor (Color color) { this->color = color; }
    void setPosition (int x, int y) { this->x = x; this->y = y; }
    
    // void setPixelPositionX (int x) { this->x = x; }
    // void setPixelPositionY (int y) { this->y = y; }
    int getPixelPositionX () { return this->x; }
    int getPixelPositionY () { return this->y; }

    void setX (int x) { this->x = (this->size * x); }
    void setY (int y) { this->y = (this->size * y); }    
    int getX () { return this->x / this->size; }
    int getY () { return this->y / this->size; }

    void moveX ( int x ) { this->x += this->size * x; }
    void moveY ( int y ) { this->y += this->size * y; }

    int getSize(){return this->size;}
    Color getColor() { return this->color; }
    Position getPosition() { return Position(this->x, this->y); }
    Position getPositionByPixel() { return Position(this->x / this->size, this->y / this->size); }

    void draw(void)
    {
        miniwin::color_rgb(this->color.getr(), this->color.getg(), this->color.getb());
        miniwin::rectangulo_lleno(this->x, this->y, this->x + this->size, this->y + this->size);
    }

    void drawFlat()
    {
        miniwin::color_rgb(this->color.getr(), this->color.getg(), this->color.getb());
        miniwin::rectangulo_lleno(this->x, this->y, this->x + this->size - 1, this->y + this->size - 1);
    }

    void erase(void)
    {
        miniwin::color(miniwin::NEGRO);
        miniwin::rectangulo_lleno(this->x, this->y, this->size, this->size);
    }

    void erase(Color color)
    {
        miniwin::color_rgb(color.getr(), color.getb(), color.getb());
        miniwin::rectangulo_lleno(this->x, this->y, this->size, this->size);
    }
};

#endif
