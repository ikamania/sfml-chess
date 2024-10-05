class Pawn : public Piece
{
    Pawn(int x, int y, std::string name, std::string color) 
        : x(x)
        , y(y)
        , name(name)
        , color(color)
    {
    };
};
