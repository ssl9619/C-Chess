//
//  piece.hpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#ifndef piece_hpp
#define piece_hpp

#include <stdio.h>
#include <list>
#include "chessMove.hpp"

class Piece {
public:
    int pieceType;
    int posX;
    int posY;
    bool whitePiece;
    
    Piece(int pieceType, int posX, int posY, bool whitePiece);
    void updatePosition(int posX, int posY);
//    std::list<ChessMove> possibleMove();
    
};

/*
 Piece values
    Pawn = 0
    Knight = 1
    Bishop = 2
    Rook = 3
    Queen = 4
    King = 5
 */


#endif /* piece_hpp */
