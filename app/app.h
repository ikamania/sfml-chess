#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "draw.h"
#include "client.h"

void runGame(Client &player)
{
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Chess");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    player.sendMessage("HEY");
        }

        std::cout << player.message << std::endl;

        window.clear();
        window.display();
    }
}

void run()
{
    Client player;

    std::thread clieLoop(&Client::play, &player);
    std::thread gameLoop(runGame, std::ref(player));

    clieLoop.join();
    gameLoop.join();
}
