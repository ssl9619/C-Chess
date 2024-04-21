//
//  team.cpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#include "headers/team.hpp"

Team::Team(bool whiteTeam) {
    this->whiteTeam = whiteTeam;
    
    // pain in the ass
    // spent so much unnecesary time trying to do this in current board but its here now, where it should have been... i knew this from the beginning :,,(
    if(whiteTeam) {
        // pawns
        for(int x = 0 ; x<8; x++) {
            alivePieces.push_front(Piece(0, x, 1, true));
        }
        // rooks
        alivePieces.push_front(Piece(3,0,0,true));
        alivePieces.push_front(Piece(3,7,0,true));
        
        // knights
        alivePieces.push_front(Piece(1,1,0,true));
        alivePieces.push_front(Piece(1,6,0,true));
        
        // bishops
        alivePieces.push_front(Piece(2,2,0,true));
        alivePieces.push_front(Piece(2,5,0,true));
        
        // queen
        alivePieces.push_front(Piece(4,3,0,true));
        
        // king
        alivePieces.push_front(Piece(5,4,0,true));
        
    } else {
        // pawns
        for(int x = 0 ; x<8; x++) {
            alivePieces.push_front(Piece(0, x, 6, false));
        }
        // rooks
        alivePieces.push_front(Piece(3,0,7,false));
        alivePieces.push_front(Piece(3,7,7,false));
        
        // knights
        alivePieces.push_front(Piece(1,1,7,false));
        alivePieces.push_front(Piece(1,6,7,false));
        
        // bishops
        alivePieces.push_front(Piece(2,2,7,false));
        alivePieces.push_front(Piece(2,5,7,false));
        
        // queen
        alivePieces.push_front(Piece(4,3,7,false));
        
        // king
        alivePieces.push_front(Piece(5,4,7,false));
    }
    
}

// TODO: Output cout errors if things break... helpful for later
void Team::update(Piece previousPiecePos, Piece updatedPiecePos) {

//    vector<Piece>::iterator it = alivePieces.begin();
    
    for(int x = 0; x<alivePieces.size(); x++) {
        
        
        
    }
}

void Team::killPiece(Piece dead) {
    
    deadPieces.push_front(dead);
    list<Piece> toBeReturned;
    list<Piece>::iterator it = alivePieces.begin();
    Piece selected = *it;
    
    bool b = true;
    for(int x = 0; x<alivePieces.size() && b; x++) {
        bool b = selected.pieceType == dead.pieceType
        && selected.posX == dead.posX
        && selected.posY == dead.posY;
        if(!b) {
            toBeReturned.push_front(selected);
            advance(it, 1);
        }
    }
    
    alivePieces.end();
    alivePieces = toBeReturned;
    
    
    
    
}
