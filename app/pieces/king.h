class King : public Piece
{
public:
    King(int x, int y, const std::string& color) 
        : Piece(x, y, color) 
    {
        name = "king";
    }
};
