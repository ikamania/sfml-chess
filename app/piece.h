class Piece
{
public:
    int x;
    int y;
    bool m = 0;
    int mx = 0;
    int my = 0;

    std::string color;
    std::string name;

    Piece(int x, int y, std::string color) 
        : x(x)
        , y(y)
        , color(color)
    {
    };

    bool move(int new_x, int new_y, int S)
    {   
        if (mx > S || mx < 0 || my > S || my < 0)
        {
            m = 0;
            mx = 0;
            my = 0;
        }   
        else 
        {
            m = 1;
            mx = new_x;
            my = new_y;
            
            return 1;
        }
        return 0;
    }

    bool basicCheck(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        if ((color == "white" && R) || (color == "black" && !R))
            return 0;
        if ((!R && c % 2 == 0) || (R && c % 2 == 1))
            return 0;
        if (map[ny][nx] != nullptr && map[ny][nx]->color == color)
            return 0;
        
        return 1;
    }

    bool checkCheck(std::vector<std::vector<Piece*>> &map, int nx, int ny)
    {
        bool check = 0;  

        Piece* oldPiece = map[ny][nx];
        Piece* newPiece = map[y][x];
        
        int ox = x;
        int oy = y;

        map[ny][nx] = newPiece; 
        map[y][x] = nullptr;
        
        newPiece->x = nx;
        newPiece->y = ny;

        for (auto &line : map)
            for (auto &piece : line)
                if (piece != nullptr && piece->color == color && piece->name == "king")
                {
                    if (piece->checkDeath(map))
                        check = 1;
                }

        map[ny][nx] = oldPiece; 
        map[oy][ox] = newPiece;

        newPiece->x = ox;
        newPiece->y = oy;

        if (check)
            return 0;
        return 1;
    }

    bool virtual validMoves(std::vector<std::vector<Piece*>> &map, int nx, int ny, int c, int R)
    {
        return 1;
    }

    bool virtual checkDeath(std::vector<std::vector<Piece*>> &map)
    {
        return 1;
    }
};
