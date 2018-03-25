#ifndef _ROOT_H_
#define _ROOT_H_

#include "../miniwin.h"

using namespace miniwin;

namespace Root
{
    class Position
    {
        float x, y;
        public:

        void setx(int x){this->x = x;}
        void sety(int y){this->y = y;}
        
        int getx(){return this->x;}
        int gety(){return this->y;}

        Position(void)
        {
            this->x = 0;
            this->y = 0;
        }

        Position(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
    };

    class Color
    {
        int r = 255, g = 255, b = 255;
        public:
        Color(){
            this->r = 255;
            this->g = 255;
            this->b = 255;
        }

        Color(int r, int g, int b){
            this->r = r;
            this->g = g;
            this->b = b;
        }

        void setColor(Color color){
            this->r = color.getr();
            this->g = color.getg();
            this->b = color.getb();
        }
        void setr(int R){this->r = r;}
        void setg(int G){this->g = g;}
        void setb(int B){this->b = b;}

        int getr(){return this->r;}
        int getg(){return this->g;}
        int getb(){return this->b;}
    };
}

#endif
