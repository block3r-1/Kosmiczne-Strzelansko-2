#include "Game.h"
#include <iostream>

int main()
{
    Game game;
    game.startGame();

    try {
        game.endGame();
    }
    catch (int kodBledu) {
        if (kodBledu == 5) std::cout << "Nie mozna otworzyc pliku!" << std::endl;
    }

    return 0;
}