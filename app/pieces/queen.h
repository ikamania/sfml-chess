class Queen : public Piece
{
public:
    Queen(int x, int y, const std::string& color) 
        : Piece(x, y, color) 
    {
        name = "queen";
    }
};
