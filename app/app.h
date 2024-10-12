#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "draw.h"
#include "player/client.h"
#include "player/server.h"

template <class Player>
void runGame(Player *player)
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
                    player->sendToOpponent("Hi there !");      
        }

        window.clear();
        window.display();
    }

    player->running = false;
    player->sendToOpponent("OUT");
}

template <class Player>
void runThreads(Player *player)
{
    std::thread t1(&Player::run, player);
    std::thread t2(runGame<Player>, player);

    t1.join();
    t2.join();
}

void run()
{
    Client *client = new Client;

    if (client->connectToServer())
        runThreads(client); 
    else
    {
        Server *server = new Server;         
        
        runThreads(server);       

        delete client;
        delete server;
    }
}
