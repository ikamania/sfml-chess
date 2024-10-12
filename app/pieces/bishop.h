class Bishop : public Piece
{
public:
    Bishop(int x, int y, const std::string& color) 
        : Piece(x, y, color) 
    {
        name = "bishop";
    }
};
