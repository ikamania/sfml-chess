class Queen : public Piece
{
public:
    Queen(int x, int y, const std::string &color) 
        : Piece(x, y, color) 
    {
        name = "queen";
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        return true;
    }
};
