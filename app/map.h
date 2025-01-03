std::vector<std::vector<Piece*>> map = {
    {
        new Rook(0, 0, "black"),
        new Knight(1, 0, "black"),
        new Bishop(2, 0, "black"),
        new Queen(3, 0, "black"),
        new King(4, 0, "black"),
        new Bishop(5, 0, "black"),
        new Knight(6, 0, "black"),
        new Rook(7, 0, "black")
    },
    {
        new Pawn(0, 1, "black"),
        new Pawn(1, 1, "black"),
        new Pawn(2, 1, "black"),
        new Pawn(3, 1, "black"),
        new Pawn(4, 1, "black"),
        new Pawn(5, 1, "black"),
        new Pawn(6, 1, "black"),
        new Pawn(7, 1, "black")
    },

    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},

    {
        new Pawn(0, 6, "white"),
        new Pawn(1, 6, "white"),
        new Pawn(2, 6, "white"),
        new Pawn(3, 6, "white"),
        new Pawn(4, 6, "white"),
        new Pawn(5, 6, "white"),
        new Pawn(6, 6, "white"),
        new Pawn(7, 6, "white")
    },
    {
        new Rook(0, 7, "white"),
        nullptr,
        nullptr,
        nullptr,
        new King(4, 7, "white"),
        nullptr,
        nullptr,
        new Rook(7, 7, "white")
    }
};
