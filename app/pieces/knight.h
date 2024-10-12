class Knight : public Piece
{
public:
    Knight(int x, int y, const std::string& color) 
        : Piece(x, y, color) 
    {
        name = "knight";
    }
};
