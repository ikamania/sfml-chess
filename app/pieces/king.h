class King : public Piece
{
public:
    King(int x, int y, const std::string &color) 
        : Piece(x, y, color) 
    {
        name = "king";
    }

    bool oneAway(int nx, int ny)
    {
        if (abs(nx - x) > 1 || abs(ny - y) > 1)
            return 0;

        return 1;
    }

    bool checkDeath(std::vector<std::vector<Piece*>> &map, int R)
    {
        // CHECKMATE 
        // OR DECLINE MOVE

        return 1;
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (!basicCheck(map, nx, ny, c, R))
            return 0;
        if (oneAway(nx, ny))
            return 1;

        return 0;
    }
};
