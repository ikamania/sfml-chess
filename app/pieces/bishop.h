class Bishop : public Queen
{
public:
    Bishop(std::string color) 
        : Queen(color) 
    {
        name = "bishop";
    }

    Bishop(int x, int y, std::string color)
        : Queen(x, y, color)       
    {
        name = "bishop";
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (!basicCheck(map, nx, ny, c, R))
            return 0;
        if (diagonalAngles(map, nx, ny, c, R) && checkCheck(map, nx, ny))
            return 1;

        return 0;    
    }
};
