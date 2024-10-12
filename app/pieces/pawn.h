class Pawn : public Piece
{
public:
    Pawn(int x, int y, const std::string& color) 
        : Piece(x, y, color) 
    {
        name = "pawn";
    }
};
