#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "player/client.h"
#include "player/server.h"
#include "piece.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

#include "map.h"
#include "draw.h"

template <class Player>
void runGame(Player *player)
{
    const int SIZE = 600;

    sf::RenderWindow window(sf::VideoMode({SIZE, SIZE}), "Chess");
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
        
        drawBoard(window, SIZE);
        drawPieces(window, map, SIZE);

        window.display();
    }

    player->running = false;
    player->sendToOpponent("OUT");

    for (auto& row : map) 
        for (auto& piece : row) 
            delete piece;   
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
