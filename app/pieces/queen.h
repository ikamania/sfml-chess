class Queen : public Piece
{
public:
    Queen(std::string color) 
        : Piece(color) 
    {
        name = "queen";
    }
    
    Queen(int x, int y, std::string color)
        : Piece(x, y, color)
    {
        name = "queen";
    }

    bool VerticalHorizontal(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {  
        if (nx == x)
        {
            if (ny > y)
                for (int j = 1; j < 8; j++)
                {
                    if (y + j == ny)
                        return 1;
                    if (map[y + j][nx] != nullptr)
                        return 0;
                }
            if (ny < y)
                for (int j = 1; j < 8; j++)
                {
                    if (y - j == ny)    
                        return 1;
                    if (map[y - j][nx] != nullptr)
                        return 0;
                }
        } 
        if (ny == y)
        {
            if (nx > x)
                for (int i = 1; i < 8; i++)
                {
                    if (x + i == nx)
                        return 1;
                    if (map[ny][x + i] != nullptr)
                        return 0;
                }
            if (nx < x)
                for (int i = 1; i < 8; i++)
                {
                    if (x - i == nx)    
                        return 1;
                    if (map[ny][x - i] != nullptr)
                        return 0;
                }
        }

        return 0;
    }

    bool diagonalAngles(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (nx > x && ny > y) // r up
            for (int t = 1; t < 8; t++) 
            {
                if (x + t == nx && y + t == ny)
                    return 1;
                if (map[y + t][x + t] != nullptr)
                    return 0;
            }
        if (nx < x && ny < y) // l do
            for (int t = 1; t < 8; t++)
            {
                if (x - t == nx && y - t == ny)
                    return 1;
                if (map[y - t][x - t] != nullptr)
                    return 0;
            }
        if (nx < x && ny > y) // l up
            for (int t = 1; t < 8; t++)
            {
                if (x - t == nx && y + t == ny)
                    return 1;
                if (map[y + t][x - t] != nullptr)
                    return 0;
            }
        if (nx > x && ny < y) // r do
            for (int t = 1; t < 8; t++)
            {
                if (x + t == nx && y - t == ny)
                    return 1;
                if (map[y - t][x + t] != nullptr)
                    return 0;
            }
        
        return 0;
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (!basicCheck(map, nx, ny, c, R))
            return 0;
        if ((VerticalHorizontal(map, nx, ny, c, R) || diagonalAngles(map, nx, ny, c, R)) && checkCheck(map, nx, ny))
            return 1;

        return 0;
    }
};
