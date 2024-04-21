//
//  sketch.hpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#ifndef sketch_hpp
#define sketch_hpp

#include <stdio.h>
#include <string>
#include <list>
#include "intendedMove.hpp"
#include "currentBoard.hpp"
#include "deadBoard.hpp"

using namespace std;

class Sketch {
public:
    bool whitePlayerTurn;
    
    Sketch(bool whitePlayerTurn);
    int intendedMoveVerification(IntendedMove i); // returns error code
    void updateChessBoard(IntendedMove i);
    int winDrawConditionSatisfied();
    int returnPossibleError(Piece p, ChessMove move);
    void printBoard();
    
private:
    bool elementInChessMoveList(list<ChessMove> input, ChessMove desired);
    bool whiteKingInCheck;
    bool blackKingInCheck;
    bool whiteKingHasLegalMoves;
    bool blackKingHasLegalMoves;
    bool stalemate;
    bool drawByChoice;
    bool whiteWon;
    bool blackWon;
    IntendedMove intendedMove; // intended move has both the original location and the updated
    CurrentBoard currentBoard;
    list<DeadBoard> prevBoardList;
    
//    Sketch();
    // i dont think any of this is necessary anymore
//    bool intendedMovePieceExists();
//    bool intendedMoveFriendlyOnSquare();
//    bool intendedMoveLeadsToCheck();
//    bool intendedMoveEnemyPiece(); // The piece thats trying to be moved is an enemy piece
//    bool intendedMoveWhileKingInCheck(); // Moving piece while friendly king in check
};

#endif /* sketch_hpp */
