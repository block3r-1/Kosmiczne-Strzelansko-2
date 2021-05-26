#include "Game.h"

int main()
{
    Game game;
    game.startGame();
   /* sf::RenderWindow window(sf::VideoMode(1920, 1080), "PIERDOLE POLSKA POLICJE"); //sf::Style::Fullscreen);
    sf::Texture sebi;
    sebi.loadFromFile("sebi.png");
    sf::Sprite sebus;
    sebus.setTexture(sebi);
    sebus.setOrigin(20, 20);
    sebus.setPosition(100, 80);
    sebus.setScale(0.5, 0.5);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close(); // zamkniecie okna guzkiem na pasku
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close(); // zamkniecie okna poprzez esc

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) sebus.move(0, -20);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) sebus.move(0, 20);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) sebus.move(-20, 0);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) sebus.move(20, 0);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) sebus.rotate(5);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) sebus.rotate(-5);

        }
        //window.clear(sf::Color::White);
        window.draw(sebus);
        window.display();
    }
    */
    return 0;
}