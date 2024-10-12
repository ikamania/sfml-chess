class Rook : public Piece
{
public:
    Rook(int x, int y, const std::string& color) 
        : Piece(x, y, color) 
    {
        name = "rook";
    }
};
