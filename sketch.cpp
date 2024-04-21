//
//  sketch.cpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#include "headers/sketch.hpp"

Sketch::Sketch(bool whitePlayerTurn) : intendedMove(0,0,0,0,0,true), currentBoard() {
    this->whitePlayerTurn = whitePlayerTurn; // this will always be true when the object is made but whatever
}

bool Sketch::elementInChessMoveList(list<ChessMove> input, ChessMove desired) {
    
    list<ChessMove>::iterator it = input.begin();
    ChessMove selected = *it;
    for(int i = 0; i < input.size(); i++) {
        if(
           selected.movePosX == desired.movePosX
        && selected.movePosY == desired.movePosY
           ) {
               return true;
           }
    }
    
    return false;
}

// returns an error code
int Sketch::intendedMoveVerification(IntendedMove i) {
    // error codes assuming selected square is correct since validation checks for it already ( or at least it should )
    /*
     0 = no errors
     1 = selected piece does not exist
     2 = selected piece does not exist on square
     3 = illegal move
     */
    int oX = i.originalPosX;
    int oY = i.originalPosY;
    int x = i.intendedPosX;
    int y = i.intendedPosY;
    int pieceType = i.desiredPiece;
    bool team = i.whiteTeam;
    
    // selected piece does not exist verification
    if(!currentBoard.pieceExists(pieceType)) { // does not work as of writing
        return 1;
    }
    
    // exists on square
    if(!currentBoard.pieceExistsOnSquare(Piece(pieceType, oX, oY, team))) {
        return 2;
    }
    
    list<ChessMove> legalMoves = currentBoard.checkLegalMovesOfPiece(Piece(pieceType, oX, oY, team));
    ChessMove intendedMove0(x, y);
    bool moveLegal = false;
    // illegal move
    // TODO: make
    switch (pieceType) {
            // see if there is overlap, i.e. intendedMove0 is an element of legalMoves
            // there is a find() method but i'm not going to try learning it right now
        case 0: // pawn
            moveLegal = elementInChessMoveList(legalMoves, intendedMove0);
            break;
        case 1: // knight
            moveLegal = elementInChessMoveList(legalMoves, intendedMove0);
            break;
        case 2: // bishop
            moveLegal = elementInChessMoveList(legalMoves, intendedMove0);
            break;
        case 3: // rook
            moveLegal = elementInChessMoveList(legalMoves, intendedMove0);
            break;
        case 4: // queen
            moveLegal = elementInChessMoveList(legalMoves, intendedMove0);
            break;
        case 5: // king
            moveLegal = elementInChessMoveList(legalMoves, intendedMove0);
            break;
        default:
            break;
    }
    
    if(!moveLegal) {
        return 3;
    }
    
    
    return 0;
}

// might make this private
void Sketch::updateChessBoard(IntendedMove i) {
    // assume intended move is valid by this point
//    ChessMove c = ChessMove(intendedMove.intendedPosX, intendedMove.intendedPosY);
//    ChessMove o = ChessMove(intendedMove.originalPosX, intendedMove.originalPosY);
    currentBoard.update(i); // assume valid
}

int Sketch::winDrawConditionSatisfied() {
    // Win Values:
    /*
     0 = continue as normal
     1 = white won by checkmate
     2 = black won by checkmate
     3 = draw by stalemate
     4 = draw by repetition
     */
    
    int winDrawType = 0;
    
    if(currentBoard.blackKingCheckmated()) {
        winDrawType = 1;
    }
    if(currentBoard.whiteKingCheckmated()) {
        winDrawType = 2;
    }
    if(currentBoard.whiteStalemate() || currentBoard.blackStalemate()) {
        winDrawType = 3; // could specify later which king was stalemated but it will be obvious... I think
    }
    if(currentBoard.drawByRepetition()) { // when you call upon the function not only does it check it also adds to the list so its important that the function is called after every move
        winDrawType = 4;
    }
    
    return winDrawType;
}

int Sketch::returnPossibleError(Piece p, ChessMove move) {
    
    // wont be needed
    // defunct
    /*
     0 = no error
     1 = piece does not exist
     2 = piece not on square
     3 = illegal move
     */
    
    list<ChessMove> legalMoves = currentBoard.checkLegalMovesOfPiece(p);
    
    list<ChessMove>::iterator it = legalMoves.begin();
    
    
    
    bool found = false;
    
    cout << "size: " << legalMoves.size() << endl;
    
    for(int x = 0; x<legalMoves.size(); x++) {
        ChessMove selected = *it;
        if(selected.movePosX == move.movePosX && selected.movePosY == move.movePosY) {
            found = true;
        }
        advance(it, 1);
    }
    if(!found) {
        return 3;
    }
    
    return 0; // no errors;
}

void Sketch::printBoard() {
    currentBoard.drawBoard();
//    cout << "\ndebug:" << endl;
//    currentBoard.drawDebug();
}
