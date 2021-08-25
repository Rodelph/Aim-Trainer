#include "Game.h"

int main()
{
    //Init srand
    srand(static_cast<unsigned>(time(NULL)));

    //Window init
    Game game;

    //Game loop
    while (game.running() && !game.getEndGame())
    {
        //Update the game
        game.update();

        //Render the game
        game.render();
    }

    return 0;
}