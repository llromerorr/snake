#ifndef _FOODGENERATOR_HPP_
#define _FOODGENERATOR_HPP_

#include <vector>
#include "Snake.hpp"
#include "Root.hpp"
#include "random.hpp"
#include "Pixel.hpp"
#include "Screen.hpp"

using Random = effolkronium::random_static;

class FoodGenerator
{
    static Screen screen;
    static Pixel food; 

    public:

    FoodGenerator ( Screen & screen ) { this->screen = screen; }
    
    static void init ( )
    {
        food = Pixel(Color(0,230,118), Position(Random::get(0, screen.getPixelByX() - 1), Random::get(0, screen.getPixelByY() - 1)));
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