//
//  currentBoard.hpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#ifndef currentBoard_hpp
#define currentBoard_hpp

#include <stdio.h>
#include <vector>
#include <list>
#include "intendedMove.hpp"
#include "piece.hpp"
#include "deadBoard.hpp"
#include "team.hpp"
#include "chessMove.hpp"

using namespace std;

class CurrentBoard {
public:
    
    
    CurrentBoard(); // will make the new arrangement
    void update(IntendedMove i); // meant to update the piece arrangement variable
    bool whiteInCheck();
    bool blackInCheck();
    bool whiteStalemate();
    bool blackStalemate();
    bool blackKingCheckmated(); // means that the black king has been checkmated
    bool whiteKingCheckmated();
    bool drawByRepetition(); // TODO: make
    bool pieceExists(int pieceType);
    bool pieceExistsOnSquare(Piece p);
    DeadBoard returnDeadBoard();
    void drawBoard();
    void drawDebug();
    list<ChessMove> checkLegalMovesOfPiece(Piece p); // does not output an error based on whether a friendly is there or not but it does check for it
    
    
private:
    Team whiteTeam;
    Team blackTeam;
    vector<vector<Piece>> arrangement;
    list<DeadBoard> deadBoardList;
    
    vector<vector<Piece>> makeEmptyArrangmentArr();
    vector<vector<Piece>> turnEmptyToStartingBoard(vector<vector<Piece>> emptyArr);
//    vector<Piece> makeStartPieces(bool whiteTeam);
    void drawPieceBox(int pieceType, bool end, bool whitePiece);
    void drawMiddleRow();
    void drawTopRow();
    void drawBottomRow();
    bool blackHasLegalMoves(); // each of these methods will do the calculations then called by the methods above to calculate stalemates or checkmates
    bool whiteHasLegalMoves();
    bool whiteKingHasLegalMoves();
    bool blackKingHasLegalMoves();
    Piece searchForKingSquare(bool whiteTeamKing); // goes through arrangement looks for king and returns its position
    list<ChessMove> pawnLegalMovesCalculation(Piece p);
    list<ChessMove> knightLegalMovesCalculation(Piece p);
    list<ChessMove> bishopLegalMovesCalculation(Piece p);
    list<ChessMove> rookLegalMovesCalculation(Piece p);
    list<ChessMove> queenLegalMovesCalculation(Piece p);
    list<ChessMove> kingLegalMovesCalculation(Piece p);
    list<ChessMove> teamAllLegalMoves(Team t);
    list<ChessMove> mergeV2(list<ChessMove> a, list<ChessMove> b);
    bool compareLists(list<ChessMove> a, list<ChessMove> b);
    
};

#endif /* currentBoard_hpp */
