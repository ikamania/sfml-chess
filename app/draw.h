void drawBoard(sf::RenderWindow &window, int s)
{
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

void drawPiece(sf::RenderWindow &window, int R, int s, std::string color, std::string name, int x, int y)
{
    sf::Sprite sprite;
    sf::Texture texture;

    texture.loadFromFile("app/assets/" + color + "/" + name + ".png");

    sprite.setTexture(texture);
    sprite.setPosition(x, y);  

    sf::Vector2f newSize(s, s);
    sprite.setScale(
                newSize.x / sprite.getLocalBounds().width, 
                newSize.y / sprite.getLocalBounds().height
    );

    window.draw(sprite);
}

void drawPieces(sf::RenderWindow &window, std::vector<std::vector<Piece*>> &map, int s, int S, int R)
{
    Piece* movingPiece = nullptr;
    int x; 
    int y;

    for (auto &line : map)
        for (auto &piece : line)
        {
            if (piece == nullptr)
                continue;
            if (piece->m)
                movingPiece = piece;
            else {
                x = R ? S - s - piece->x * s : piece->x * s;
                y = R ? S - s - piece->y * s : piece->y * s;

                drawPiece(window, R, s, piece->color, piece->name, x, y);
            }
        }
    
    if (movingPiece != nullptr) {
        x = movingPiece->mx - s / 2;
        y = movingPiece->my - s / 2;

        drawPiece(window, R, s, movingPiece->color, movingPiece->name, x, y);
    }
}

void drawPromotion(sf::RenderWindow &window, int s, int R, int x, int y)
{
    int l = s - 10;
    x = R ? 7 - x : x;

    std::vector<std::string> pieces = {"queen", "knight", "rook", "bishop"};
    std::string color = R ? "black" : "white";

    sf::RectangleShape rectangle(sf::Vector2f(l, l));

    for (int n = 0; n < 4; n++) {
        rectangle.setPosition(x * s + 5, n * l);
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(1.f);

        window.draw(rectangle);

        drawPiece(window, R, l, color, pieces[n], x * s + 5, n * l);
    }
}
