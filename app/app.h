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
    const int S = 600;
    const int s = S / 8;
    const int R = player->counter ? 1 : 0;

    bool mouseDown = false;
    Piece *selectedPiece = nullptr;

    sf::RenderWindow window(sf::VideoMode({S, S}), "Chess");
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

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left && selectedPiece == nullptr)
                {
                    selectedPiece = map[event.mouseButton.y / s][event.mouseButton.x / s];
                
                    if (selectedPiece != nullptr)
                        std::cout << selectedPiece->color << " " << selectedPiece->name << std::endl;
                }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left && selectedPiece != nullptr)
                {
                    if (selectedPiece->validMove())
                        // make move && send to opponent
                    else
                    {
                        selectedPiece->m = 0;
                        selectedPiece = nullptr;
                    }
                }
            
            if (event.type == sf::Event::MouseMoved && selectedPiece != nullptr)
            {
                selectedPiece->m = 1;
                selectedPiece->mx = event.mouseMove.x - s / 2;
                selectedPiece->my = event.mouseMove.y - s / 2;
            }
        }
        window.clear();

        drawBoard(window, S);
        drawPieces(window, map, S, R);

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