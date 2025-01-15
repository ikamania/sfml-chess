#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <sstream>

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
    const int S = 600;
    const int s = S / 8;

    int R = player->counter ? 1 : 0;
    int c = 1;
    int x;
    int y;
    int ox;
    int oy;

    bool mouseDown = false;
    bool promotion = false;

    Piece *selectedPiece = nullptr;
    std::string name = " ";

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
                if (event.mouseButton.button == sf::Mouse::Left && selectedPiece == nullptr) {
                    

                    if (promotion) {
                        name = checkPromotion(x, y, event.mouseButton.x / s, event.mouseButton.y / s, R);

                        if (name != " ") {
                            promotion = false;
                            
                            player->sendToOpponent(debugOutput(ox, oy, x, y, name));
                            changePiece(name, map, x, y);
                        }
                    }
                    else {
                        x = R ? 7 - event.mouseButton.x / s : event.mouseButton.x / s;
                        y = R ? 7 - event.mouseButton.y / s : event.mouseButton.y / s;

                        selectedPiece = map[y][x];
                    }
                }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left && selectedPiece != nullptr) {
                    x = R ? 7 - event.mouseButton.x / s : event.mouseButton.x / s;
                    y = R ? 7 - event.mouseButton.y / s : event.mouseButton.y / s;

                    ox = selectedPiece->x;
                    oy = selectedPiece->y;

                    if (selectedPiece->validMoves(map, x, y, c, R))
                    {
                        movePiece(selectedPiece, map, x, y);
                        c++;

                        if (selectedPiece->name == "pawn" && ((R && y == 7) || (!R && y == 0)))
                            promotion = 1;
                        else
                            player->sendToOpponent(debugOutput(ox, oy, x, y, " "));           
                    } else {
                        selectedPiece->m = 0;
                    }
                    
                    selectedPiece = nullptr;
                }

            if (event.type == sf::Event::MouseMoved && selectedPiece != nullptr)
                if (!(selectedPiece->move(event.mouseMove.x, event.mouseMove.y, S)))
                    selectedPiece = nullptr;
        }
        
        if (message[0] != '\0') {
            debugInput(message, map, c);
            
            message.clear();
            message.resize(1024, '\0');

            if (checkMate(map, c, R)) {

                player->sendToOpponent("W");

                std::cout << "L" << std::endl;
            }
        }

        window.clear();

        drawBoard(window, s);
        drawPieces(window, map, s, S, R);

        if (promotion)
            drawPromotion(window, s, R, x, y);
        
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

