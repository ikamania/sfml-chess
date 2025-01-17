void loadPieceCoordinates(std::vector<std::vector<Piece*>> &map)
{
    int x = 0;
    int y = 0;

    for (auto &line : map) {
        for(auto &piece : line) {
            if (piece != nullptr) {
                piece->x = x;
                piece->y = y;
            }
            x++;
        }
        x = 0;

        y++;
    }
}

void movePiece(Piece *piece, std::vector<std::vector<Piece*>> &map, int nx, int ny) 
{
    if (piece->name == "king" && abs(piece->x - nx) > 1) {
        int x = nx > piece->x ? 7 : 0;
        int d = nx > piece->x ? -1 : 1;

        movePiece(map[piece->y][x], map, nx + d, piece->y);
    }

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
    cell->o = 1; // moved indicator

    map[piece->y][piece->x] = nullptr;
    delete piece;
}

void changePiece(std::string name, std::vector<std::vector<Piece*>> &map, int x, int y)
{
    std::string color = map[y][x]->color;

    if (name == "queen") 
        map[y][x] = new Queen(x, y, color);
    else if (name == "knight")
        map[y][x] = new Knight(x, y, color);
    else if (name == "rook")
        map[y][x] = new Rook(x, y, color);
    else if (name == "bishop")
        map[y][x] = new Bishop(x, y, color);
}

void endGame(std::vector<std::vector<Piece*>> &map)
{
    for (auto &line : map)
        for (auto &piece : line)
            delete piece;
}

std::string debugOutput(int x, int y, int nx, int ny, std::string message)
{
    std::stringstream ss;

    ss << x << " " << y << " " << nx << " " << ny << " " << message << " "; 

    return ss.str();
}

void debugInput(std::string &message, std::vector<std::vector<Piece*>> &map, int &c)
{
    if (message.at(0) == 'W') {
        std::cout << "W" << std::endl;

        return;
    }

    int x, y, nx, ny;
    std::string name;

    std::stringstream ss(message);

    ss >> x >> y >> nx >> ny >> name;

    Piece *selectedPiece = map[y][x];
    
    movePiece(selectedPiece, map, nx, ny);
    c++;
    
    if (name != " ")
        changePiece(name, map, nx, ny);
}

bool checkMate(std::vector<std::vector<Piece*>> &map, int c, int R)
{
    std::string color = R ? "b" : "w";

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

std::string checkPromotion(int ox, int oy, int x, int y, int R)
{
    std::vector<std::string> pieces = {"queen", "knight", "rook", "bishop"};

    x = R ? 7 - x : x;

    if (ox == x && y < 4)
        return pieces[y];
    return " ";
}
