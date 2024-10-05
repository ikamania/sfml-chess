#include <iostream>
#include <SFML/Graphics.hpp>

#include "pieces/piece.h"
#include "pieces/pawn.h"
#include "draw.h"

void run()
{
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Chess");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}
