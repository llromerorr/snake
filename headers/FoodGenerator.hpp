#ifndef _FOODGENERATOR_HPP_
#define _FOODGENERATOR_HPP_

#include <vector>
#include "Snake.hpp"
#include "Root.hpp"
#include "random.hpp"
#include "Pixel.hpp"
#include "Screen.hpp"

using namespace std;
using Random = effolkronium::random_static;

class FoodGenerator
{
    static Screen screen;
    static Pixel food; 

    public:

    FoodGenerator ( Screen & screen ) { this->screen = screen; }
    
    static void init (vector<Pixel> body, Position headPosition)
    {
        bool flag = false;
        int tempX = 0;
        int tempY = 0;
        
        while(true)
        {
            tempX = Random::get(0, screen.getPixelByX() - 1);
            tempY = Random::get(0, screen.getPixelByY() - 1);

            if(tempX == headPosition.getx() || tempY == headPosition.gety())
                continue;

            else
            {
                for(vector<Pixel>::iterator i = body.begin(); i != body.end(); ++i)
                    if(tempX == i->getX() || tempY == i->getY())
                        flag = true;

                if(flag == true)
                {
                    flag = false;
                    continue;
                }

                else
                {
                    food = Pixel(Color(0,230,118), Position(tempX, tempY));
                    break;
                }
            }
        }
    }

    static void update ( )
    {
        food.draw();
    }

    static Position getPosition ( ) { return food.getPosition(); }
};

Screen FoodGenerator :: screen = Screen(200, 200);
Pixel FoodGenerator :: food = Pixel();

#endif