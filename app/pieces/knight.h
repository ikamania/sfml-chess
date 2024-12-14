class Knight : public Piece
{
public:
    Knight(int x, int y, const std::string &color) 
        : Piece(x, y, color) 
    {
        name = "knight";
    }

    bool swastika(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        for (int cy = 2; cy > -4; cy -= 4)
            for (int cx = 1; cx > -2; cx -= 2)
                if (nx == x + cx && ny == y + cy)
                    return 1;

        for (int cx = 2; cx > -4; cx -= 4)
            for (int cy = 1; cy > -2; cy -= 2)
                if (nx == x + cx && ny == y + cy)
                    return 1;

        return 0;
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (!basicCheck(map, nx, ny, c, R))
            return 0;
        if (swastika(map, nx, ny, c, R) && checkCheck(map, nx, ny))
            return 1;

        return 0;
    }
};
