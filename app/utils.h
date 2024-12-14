void movePiece(Piece *piece, std::vector<std::vector<Piece*>> &map, int nx, int ny, int &c) 
{
    Piece* &cell = map[ny][nx];

    if (cell != nullptr) {
        delete cell;
    }

    if (piece->name == "pawn") {
        cell = new Pawn(nx, ny, piece->color);
    } else if (piece->name == "rook") { 
        cell = new Rook(nx, ny, piece->color);
    } else if (piece->name == "knight") { 
        cell = new Knight(nx, ny, piece->color);
    } else if (piece->name == "bishop") { 
        cell = new Bishop(nx, ny, piece->color);
    } else if (piece->name == "queen") { 
        cell = new Queen(nx, ny, piece->color);
    } else if (piece->name == "king")  {
        cell = new King(nx, ny, piece->color);
    }
    c++;

    map[piece->y][piece->x] = nullptr;
    delete piece;
}

void boardPrint(std::vector<std::vector<Piece*>> &map)
{
    for (auto &line : map)
    {
        for (auto &piece : line)
        {
            if (piece == nullptr) {
                std::cout << "0";
            }
            else {
                std::cout << piece->name[0];
            }
        }
        std::cout << std::endl;
    }
}

void endGame(std::vector<std::vector<Piece*>> &map)
{
    for (auto &line : map)
        for (auto &piece : line)
            delete piece;
}

std::string debugOutput(int x, int y, int nx, int ny)
{
    std::stringstream ss;

    ss << x << " " << y << " " << nx << " " << ny; 

    return ss.str();
}

void debugInput(std::string &message, std::vector<std::vector<Piece*>> &map, int &c)
{
    if (message.at(0) == 'W') {
        std::cout << "W" << std::endl;

        return;
    }

    int x, y, nx, ny;

    std::stringstream ss(message);

    ss >> x >> y >> nx >> ny; 

    Piece *selectedPiece = map[y][x];
    
    movePiece(selectedPiece, map, nx, ny, c);
}

bool checkMate(std::vector<std::vector<Piece*>> &map, int c, int R)
{
    std::string color = R ? "black" : "white";

    for (auto &line : map)
        for(auto &piece : line)
            if (piece != nullptr && piece->color == color && piece->name == "king" && !piece->checkDeath(map))
                return 0;

    for (auto &line : map)
        for(auto &piece : line)
            if (piece != nullptr && piece->color == color)
                for (int x = 0; x < 8; x++)
                    for(int y = 0; y < 8; y++)
                        if (piece->validMoves(map, x, y, c, R))
                            return 0;

    return 1;
}

