class Pawn : public Piece
{
public:
    Pawn(int x, int y, const std::string &color) 
        : Piece(x, y, color) 
    {
        name = "pawn";
    }

    bool leftRight(std::vector<std::vector<Piece*>> &map, int nx, int ny, int R)
    {
        if ((R && y == 1 && ny == y + 2) || (!R && y == 6 && ny == y - 2))
        {
            int e = R ? 1 : -1;

            if (nx == x && map[y + e][nx] == nullptr && map[ny][nx] == nullptr)   
                return 1;
        }

        if (((R && ny == y + 1) || (!R && ny == y - 1)))
        {
            if (nx == x && map[ny][nx] == nullptr)
                return 1;
            
            for (int i = 1; i > -2; i -= 2)
                if (nx == x + i && map[ny][nx] != nullptr && map[ny][nx]->color != color )
                    return 1;
        }
        
        return 0;
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (!basicCheck(map, nx, ny, c, R))
            return 0;
        if (leftRight(map, nx, ny, R) && checkCheck(map, nx, ny))
            return 1;
        
        return 0;
    }
};
