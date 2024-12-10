#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "config.h"
#include "piece.h"
#include "player/client.h"
#include "player/server.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "map.h"
#include "draw.h"
#include "utils.h"

template <class Player>
void runGame(Player *player, std::string &message)
{
    int R = player->counter ? 1 : 0;
    int c = 1;
    int x;
    int y;

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
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left && selectedPiece == nullptr)
                {
                    x = R ? 7 - event.mouseButton.x / s : event.mouseButton.x / s;
                    y = R ? 7 - event.mouseButton.y / s : event.mouseButton.y / s;

                    selectedPiece = map[y][x];
                    
                    /*if (selectedPiece != nullptr)*/
                    /*    std::cout << selectedPiece->color << " " << selectedPiece->name << std::endl;*/
                }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left && selectedPiece != nullptr)
                {
                    x = R ? 7 - event.mouseButton.x / s : event.mouseButton.x / s;
                    y = R ? 7 - event.mouseButton.y / s : event.mouseButton.y / s;

                    if (selectedPiece->validMoves(map, x, y, c, R))
                    {
                        player->sendToOpponent(debugOutput(selectedPiece->x, selectedPiece->y, x, y));                       
                        movePiece(selectedPiece, map, x, y, c);
                    } else {
                        selectedPiece->m = 0;
                    }
                    
                    selectedPiece = nullptr;
                    /*boardPrint(map);*/
                }

            if (event.type == sf::Event::MouseMoved && selectedPiece != nullptr)
                if (!(selectedPiece->move(event.mouseMove.x, event.mouseMove.y, S)))
                    selectedPiece = nullptr;
        }
        
        if (message[0] != '\0') {
            debugInput(message, map, c);
        }

        window.clear();

        drawBoard(window, S);
        drawPieces(window, map, S, R);
        
        window.display();
    }
    
    for (auto &row : map)
        for (auto &piece : row)
            delete piece;
    delete player;

    std::exit(0);
}

template <class Player>
void runThreads(Player *player)
{
    std::string message(1024, '\0');

    std::thread t1(&Player::run, player, std::ref(message));
    std::thread t2(runGame<Player>, player, std::ref(message));

    t1.join();
    t2.join();
}

