void drawBoard(sf::RenderWindow &window, const int &SIZE)
{
    int s = SIZE / 8;

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

void drawPieces(sf::RenderWindow &window, std::vector<std::vector<Piece*>> &map, const int &SIZE)
{
    int s = SIZE / 8;

    for (auto &line : map)
        for (auto &piece : line)
        {
            if (piece == nullptr)
                break;
            
            sf::Sprite sprite;
            sf::Texture texture;

            texture.loadFromFile("app/assets/" + piece->color + "/" + piece->name + ".png");

            sprite.setTexture(texture);
            sprite.setPosition(piece->x * s, piece->y * s);  

            sf::Vector2f newSize(s, s);
            sprite.setScale(
                            newSize.x / sprite.getLocalBounds().width, 
                            newSize.y / sprite.getLocalBounds().height
            );

            window.draw(sprite);
        }
}
