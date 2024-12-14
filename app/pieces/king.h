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

    bool checkDeath(std::vector<std::vector<Piece*>> &map)
    {
        int s = (color == "black") ? 1 : -1;
        
        for (int i = 1; i > -2; i -= 2) // Pawn
        {
            if (y + s > 7 || y + s < 0 || x + i > 7 || x + i < 0)
                    break;
            if (map[y + s][x + i] != nullptr && map[y + s][x + i]->color != color && map[y + s][x + i]->name == "pawn")
                return 1;
        }

        for (int dir = -1; dir <= 1; dir += 2) // Queen Rook (x)
        {
            for (int i = 1; i < 8; ++i) 
            {
                int nx = x + i * dir;
                
                if (nx > 7 || nx < 0)
                    break;
                if (map[y][nx] != nullptr)
                {
                    if (map[y][nx]->color != color && (map[y][nx]->name == "queen" || map[y][nx]->name == "rook")) 
                        return 1;
                    break;
                }
            }
        }

        for (int dir = -1; dir <= 1; dir += 2) // Queen Rook (y)
        {
            for (int i = 1; i < 8; ++i) 
            {
                int ny = y + i * dir;
                
                if (ny > 7 || ny < 0)
                    break;
                if (map[ny][x] != nullptr)
                {
                    if (map[ny][x]->color != color && (map[ny][x]->name == "queen" || map[ny][x]->name == "rook")) 
                    {
                        return 1;
                    }
                    break;
                }
            }
        }

        for (int dir = -1; dir <= 1; dir += 2) // Queen Bishop (l p) (r d)
        {
            for (int i = 1; i < 8; ++i) 
            {
                int ny = y + i * dir;
                int nx = x + i * dir;
                
                if (ny > 7 || ny < 0 || nx > 7 || nx < 0)
                    break;
                if (map[ny][nx] != nullptr)
                {
                    if (map[ny][nx]->color != color && (map[ny][nx]->name == "queen" || map[ny][nx]->name == "bishop")) 
                        return 1;
                    break;
                }
            }
        }

        for (int dir = -1; dir <= 1; dir += 2) // Queen Bishop (r p) (l d)
        {
            for (int i = 1; i < 8; ++i) 
            {
                int ny = y - i * dir;
                int nx = x + i * dir;
                
                if (ny > 7 || ny < 0 || nx > 7 || nx < 0)
                    break;
                if (map[ny][nx] != nullptr)
                {
                    if (map[ny][nx]->color != color && (map[ny][nx]->name == "queen" || map[ny][nx]->name == "bishop")) 
                        return 1;
                    break;
                }
            }
        }
        
        for (int cy = 2; cy > -4; cy -= 4) // Knight
            for (int cx = 1; cx > -2; cx -= 2)
            {
                int ny = y + cy;
                int nx = x + cx;

                if (ny > 7 || ny < 0 || nx > 7 || nx < 0)
                    break;
                if (map[ny][nx] != nullptr)
                {
                    if (map[ny][nx]->color != color && map[ny][nx]->name == "knight")
                        return 1;
                    break;
                }
            }

        for (int cx = 2; cx > -4; cx -= 4) // Knight
            for (int cy = 1; cy > -2; cy -= 2)
            {
                int ny = y + cy;
                int nx = x + cx;

                if (ny > 7 || ny < 0 || nx > 7 || nx < 0)
                    break;
                if (map[ny][nx] != nullptr)
                {
                    if (map[ny][nx]->color != color && map[ny][nx]->name == "knight")
                        return 1;
                    break;
                }
            }

        return 0;
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if (!basicCheck(map, nx, ny, c, R))
            return 0;
        if (oneAway(nx, ny) && checkCheck(map, nx, ny))
            return 1;
        
        return 0;
    }
};
