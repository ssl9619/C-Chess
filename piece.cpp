//
//  piece.cpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#include "headers/piece.hpp"

Piece::Piece(int pieceType, int posX, int posY, bool whitePiece) {
    this->pieceType = pieceType;
    this->posX = posX;
    this->posY = posY;
    this->whitePiece = whitePiece;
}

void Piece::updatePosition(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}

/*
std::list<ChessMove> Piece::possibleMove() {
    
    // posX, posY = 0 is bottom left of the chessboard
    
    // 7 [][][][][][][][]
    // 6 [][][][][][][][]
    // 5 [][][][][][][][]
    // 4 [][][][][][][][]
    // 3 [][][][][][][][]
    // 2 [][][][][][][][]
    // 1 [][][][][][][][]
    // 0 [][][][][][][][]
    //   0 1 2 3 4 5 6 7
    
    std::list<ChessMove> possibleMovesList;
    // push_front
    // the location doesnt matter i.e. whether it is at the front or the back
    
    // TODO, later on need to check to make sure that a possible move doesn't overlap, actually i'll just use the friendly piece validation thing
    // so it probably doesn't matter
    switch(pieceType) {
        case 0: // Pawn
            if(whitePiece) {
                
                // white piece
                if(posX+1 <= 7 && posY+1 <= 7) {
                    possibleMovesList.push_front(ChessMove(posX-1,  posY+1)); // move diagonal left
                    possibleMovesList.push_front(ChessMove(posX+1,  posY+1)); // move diagonal right
                    possibleMovesList.push_front(ChessMove(posX,    posY+1)); // move forwards
                };
                
            } else {
                
                // black piece
                if(posX-1 >= 0 && posY-1 >= 0) {
                    possibleMovesList.push_front(ChessMove(posX-1,  posY-1)); // move diagonal left
                    possibleMovesList.push_front(ChessMove(posX+1,  posY-1)); // move diagonal right
                    possibleMovesList.push_front(ChessMove(posX,    posY-1)); // move forwards
                };
                
            };
            
            break;
        case 1: // Knight
            
            // piece color doesn't matter
            
            // vertical up
            if(posY+2 <= 7 && posX-1 >= 0 && posX+1 <= 7) {
                possibleMovesList.push_front(ChessMove(posX-1, posY+2)); // Up and to the left
                possibleMovesList.push_front(ChessMove(posX+1, posY+2)); // Up and to the right
            };
            
            // horizontal right
            if(posX+2 <= 7 && posY+1 <= 7 && posY-1 >= 0) {
                possibleMovesList.push_front(ChessMove(posX+2, posY+1)); // Right and up
                possibleMovesList.push_front(ChessMove(posX+2, posY-1)); // Right and down
            };
            
            // horizontal left
            if(posX-2 >= 0 && posY+1 <= 7 && posY-1 >= 0) {
                possibleMovesList.push_front(ChessMove(posX-2, posY+1)); // Left and up
                possibleMovesList.push_front(ChessMove(posX-2, posY-1)); // Left and down
                
            };
            
            // vertical down
            if(posY-2 >= 0 && posX+1 <= 7 && posX-1 >= 0) {
                possibleMovesList.push_front(ChessMove(posX-1, posY-2)); // Down and left
                possibleMovesList.push_front(ChessMove(posX+1, posY-2)); // Down and right
            }
            
            break;
        case 2: // Bishop
            
            // diagonal up-right
            for(int i = 1; posX+i < 7 && posY+i < 7; i++) {
                possibleMovesList.push_front(ChessMove(posX+i, posY+i));
            }
            
            // diagonal up-left
            for(int i = 1; posX-i > 0 && posY+i; i++) {
                possibleMovesList.push_front(ChessMove(posX-i, posY+i));
            }
            
            // diagonal down-right
            for(int i = 1; posX+i < 7 && posY-i > 0; i++) {
                possibleMovesList.push_front(ChessMove(posX+i, posY-i));
            }
            
            // diagonal down-left
            for(int i = 1; posX-i > 0 && posY-i > 0; i++) {
                possibleMovesList.push_front(ChessMove(posX-i, posY-i));
            }
            
            break;
        case 3: // Rook
            
            // not super sure about this code
            // check later if everything doesn't work lol
            
            // up
            for(int y = 1; posY+y < 7; y++) {
                possibleMovesList.push_front(ChessMove(posX, posY+y));
            };
            
            // down
            for(int y = -1; posY+y > 0; y--) {
                possibleMovesList.push_front(ChessMove(posX, posY+y));
            };
            
            // left
            for(int x = 1; posX+x < 7; x++) {
                possibleMovesList.push_front(ChessMove(posX+x, posY));
            };
            
            for(int x = -1; posX+x > 0; x--) {
                possibleMovesList.push_front(ChessMove(posX+x, posY));
            };
            
            break;
        case 4: // Queen
            
            // copy pasted from rook
            // up
            for(int y = 1; posY+y < 7; y++) {
                possibleMovesList.push_front(ChessMove(posX, posY+y));
            };
            
            // down
            for(int y = -1; posY+y > 0; y--) {
                possibleMovesList.push_front(ChessMove(posX, posY+y));
            };
            
            // left
            for(int x = 1; posX+x < 7; x++) {
                possibleMovesList.push_front(ChessMove(posX+x, posY));
            };
            
            for(int x = -1; posX+x > 0; x--) {
                possibleMovesList.push_front(ChessMove(posX+x, posY));
            };
            
            // copy pasted from bishop
            // diagonal up-right
            for(int i = 1; posX+i < 7 && posY+i < 7; i++) {
                possibleMovesList.push_front(ChessMove(posX+i, posY+i));
            }
            
            // diagonal up-left
            for(int i = 1; posX-i > 0 && posY+i; i++) {
                possibleMovesList.push_front(ChessMove(posX-i, posY+i));
            }
            
            // diagonal down-right
            for(int i = 1; posX+i < 7 && posY-i > 0; i++) {
                possibleMovesList.push_front(ChessMove(posX+i, posY-i));
            }
            
            // diagonal down-left
            for(int i = 1; posX-i > 0 && posY-i > 0; i++) {
                possibleMovesList.push_front(ChessMove(posX-i, posY-i));
            }
            
            break;
        case 5: // King
            
            if(posY+1 <= 7) {
                possibleMovesList.push_front(ChessMove(posX, posY+1)); // directly up
                if(posX+1 <= 7) {
                    possibleMovesList.push_front(ChessMove(posX+1, posY+1)); // up and right
                };
                if(posX-1 >= 0) {
                    possibleMovesList.push_front(ChessMove(posX-1, posY+1)); // up and left
                };
                
            };
            if(posY-1 >= 0) {
                possibleMovesList.push_front(ChessMove(posX, posY-1)); // directly down
                if(posX+1 <= 7) {
                    possibleMovesList.push_front(ChessMove(posX+1, posY-1)); // down and right
                };
                if(posX-1 >= 0) {
                    possibleMovesList.push_front(ChessMove(posX-1, posY-1)); // down and left
                };
                
            };
            if(posX+1 <= 7) {
                possibleMovesList.push_front(ChessMove(posX+1, posY)); // directly right
            };
            if(posX-1 >= 0) {
                possibleMovesList.push_front(ChessMove(posX-1, posY)); // directly left
                
            };
            
            break;
        default: // Error, should never get more than 5
            break;
    }
    
    
    return possibleMovesList;
}
*/
