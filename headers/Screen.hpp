#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "../miniwin.h"
#include "Pixel.hpp"
#include "Root.hpp"

using namespace miniwin;
using namespace Root;

class Screen
{
    int width = 200, height = 200;
    int pixelSize = 20;
    int pixelByX = 10, pixelByY = 10;
    Color BackgroundColor = Color(100, 100, 100);

    public:

    Screen (void) { }
    Screen (int width, int height)
    {
        this->width = width;
        this->height = height;
        this->pixelByX = width / pixelSize;
        this->pixelByY = height / pixelSize;
    }
    Screen (int width, int height, int pixelSize)
    {
        this->pixelSize = pixelSize;
        this->width = width;
        this->height = height;
        this->pixelByX = width / pixelSize;
        this->pixelByY = height / pixelSize;
    }

    void init() { miniwin :: vredimensiona(this->width, this->height); }
    void init(int width, int height) { this->resize(width, height); }
    void check()
    {
        Pixel punto(Color(255,255,255), pixelSize);

        for(int i = 0; i <= this->pixelByY; i++)
        {
            for(int j = 0; j <= this->pixelByX; j++)
            {
                punto.drawFlat();
                punto.setX(j);
            }
            punto.setY(i);
            punto.setX(0);
        }
    }

    void drawBackgroud()
    {
        miniwin :: color_rgb(this->BackgroundColor.getr(), this->BackgroundColor.getg(), this->BackgroundColor.getb());
        miniwin :: rectangulo_lleno(0, 0, this->width, this->height);
    }

    void setColorBackground(Color color)
    {
        this->BackgroundColor = color;
    }

    void clear ( ) { miniwin :: borra(); }
    void update ( ) { miniwin :: refresca(); }
    void update ( float millisecods ) { miniwin :: refresca(); miniwin :: espera(millisecods); }
    void wait (float millisecods) { miniwin :: espera(millisecods); }
    void close ( ) { vcierra(); }
    void resize (int width, int height)
    {
        this->width = width;
        this->height = height;
        this->pixelByX = width / pixelSize;
        this->pixelByY = height / pixelSize;
        miniwin :: vredimensiona(this->width, this->height);
    }

    int getPixelByX ( ) { return this->pixelByX; }
    int getPixelByY ( ) { return this->pixelByY; }
};

#endif
