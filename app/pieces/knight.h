class Knight : public Piece
{
public:
    Knight(int x, int y, const std::string &color) 
        : Piece(x, y, color) 
    {
        name = "knight";
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        return true;
    }
};
