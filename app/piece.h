class Piece
{
public:
    int x;
    int y;
    int m = 0;
    int mx = 0;
    int my = 0;

    std::string color;
    std::string name;

    Piece(int x, int y, std::string color) 
        : x(x)
        , y(y)
        , color(color)
    {
    };
};
