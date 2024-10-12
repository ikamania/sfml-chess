class Piece
{
public:
    int x;
    int y;

    std::string color;
    std::string name;

    Piece(int x, int y, std::string color) 
        : x(x)
        , y(y)
        , color(color)
    {
    };
};
