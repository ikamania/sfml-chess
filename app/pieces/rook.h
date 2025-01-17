class Rook : public Queen
{
public:
    Rook(std::string color) 
        : Queen(color) 
    {
        name = "rook";
    }

    Rook(int x, int y, std::string color)
        : Queen(x, y, color)
    {
        name = "rook";
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (!basicCheck(map, nx, ny, c, R))
            return 0;
        if (VerticalHorizontal(map, nx, ny, c, R) && checkCheck(map, nx, ny))
            return 1;

        return 0;
    }
};
