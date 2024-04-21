//
//  team.hpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#ifndef team_hpp
#define team_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include "chessMove.hpp"
#include "piece.hpp"

using namespace std;

class Team {
public:
    bool whiteTeam;
    list<Piece> alivePieces;
    list<Piece> deadPieces;
    
    Team(bool whiteTeam);
    void update(Piece previousPiecePos, Piece updatedPiecePos); // updates positions
    void killPiece(Piece dead);
    
};

#endif /* team_hpp */
