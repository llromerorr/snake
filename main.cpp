#include "headers/Pixel.hpp"
#include "headers/Screen.hpp"
#include "headers/Snake.hpp"
#include "headers/HandleInput.hpp"

int update(bool & gameOver)
{
    HandleInput :: updateKey();
    
    switch(HandleInput :: getKey())
    {
        case ESCAPE:
            if(pregunta("Do you want to exit?"))
                gameOver = true;
    }
}


int main ( )
{
    bool gameOver = false;
    Screen game(640, 480);
    Snake player(game);

    game.init();
    player.init(5, 12);

    game.setColorBackground(Color(38,50,56));

    while(!gameOver)
    {
        update(gameOver);
        game.drawBackgroud();

        player.update();
        game.update(60);
    }

    game.close();
    return 0;
}
