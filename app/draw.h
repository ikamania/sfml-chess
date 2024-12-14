void drawBoard(sf::RenderWindow &window, const int &S)
{
    int s = S / 8;

    sf::RectangleShape rectangle(sf::Vector2f(s, s));
    std::vector<sf::Color> colors = {sf::Color(238, 238, 210), sf::Color(75, 72, 71)};

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            rectangle.setPosition(x * s, y * s);
            rectangle.setFillColor(colors[(x + y) % 2]);

            window.draw(rectangle);
        }
    }
}

void drawPiece(sf::RenderWindow &window, Piece* piece, const int S, int R)
{
    int s = S / 8;
    int x;
    int y;

    x = piece->m ? piece->mx - s / 2 : (R ? S - s - piece->x * s : piece->x * s);
    y = piece->m ? piece->my - s / 2 : (R ? S - s - piece->y * s : piece->y * s);
            
    sf::Sprite sprite;
    sf::Texture texture;

    texture.loadFromFile("app/assets/" + piece->color + "/" + piece->name + ".png");

    sprite.setTexture(texture);
    sprite.setPosition(x, y);  

    sf::Vector2f newSize(s, s);
    sprite.setScale(
                newSize.x / sprite.getLocalBounds().width, 
                newSize.y / sprite.getLocalBounds().height
    );

    window.draw(sprite);
}

void drawPieces(sf::RenderWindow &window, std::vector<std::vector<Piece*>> &map, const int S, const int R)
{
    Piece* movingPiece = nullptr;

    for (auto &line : map)
        for (auto &piece : line)
        {
            if (piece == nullptr)
                continue;
            if (piece->m)
                movingPiece = piece;
            else             
                drawPiece(window, piece, S, R);
        }
    
    if (movingPiece != nullptr)
        drawPiece(window, movingPiece, S, R);
}
