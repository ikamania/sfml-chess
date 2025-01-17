std::vector<std::vector<Piece*>> map = {
    {
        new Rook("b"), new Knight("b"), new Bishop("b"), new Queen("b"), new King("b"), new Bishop("b"), new Knight("b"), new Rook("b")
    },
    {
        new Pawn("b"), new Pawn("b"), new Pawn("b"), new Pawn("b"), new Pawn("b"), new Pawn("b"), new Pawn("b"), new Pawn("b")
    },

    {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    },
    
    {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    },

    {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    },

    {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    },

    {
        new Pawn("w"), new Pawn("w"), new Pawn("w"), new Pawn("w"), new Pawn("w"), new Pawn("w"), new Pawn("w"), new Pawn("w")
    },

    {
        new Rook("w"), new Knight("w"), new Bishop("w"), new Queen("w"), new King("w"), new Bishop("w"), new Knight("w"), new Rook("w")
    }
};
