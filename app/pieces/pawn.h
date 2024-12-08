class Pawn : public Piece
{
public:
    Pawn(int x, int y, const std::string &color) 
        : Piece(x, y, color) 
    {
        name = "pawn";
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        return basicCheck(c, R);
    }
};
