//
//  currentBoard.cpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#include "headers/currentBoard.hpp"

//TODO: make
void CurrentBoard::update(IntendedMove i) {
    // remember to update the team pieces if a piece dies
    // assume intended move is valid
    
    /* (unrelated: intendedMove class should do validation on its own
        then when it is valid it can return a chessMove object :O)
     
     -update whiteTeam using the update method
     -turn the chess move from a move to a piece (not needed)
     -See if cM overlaps with an enemy square (
        If so then go to team and kill the enemy piece
     -update the arrangement array
        Look for the original square, make it an empty one
        Look for the updated square and place the new piece there
    
     */
    
    int originalX = i.originalPosX;
    int originalY = i.originalPosY;
    
    int updatedX = i.intendedPosX;
    int updatedY = i.intendedPosY;
    
    int piece = i.desiredPiece;
    int team = i.whiteTeam;
    
    cout << "ogX " << originalX << ", ogY " << originalY << endl;
    cout << "uX " << updatedX << ", uY " << updatedY << endl;
    
    Piece emptySquare(-1, originalX, originalY, false);
    
    arrangement[originalX][originalY] = emptySquare;
    arrangement[updatedX][updatedY] = Piece(piece, updatedX, updatedY, team);
    
}

// might not work
bool CurrentBoard::whiteInCheck() {
    // king square is one of the legal moves for opposing team
    list<ChessMove> blackTeamLegal = teamAllLegalMoves(blackTeam);
    Piece whiteKing = searchForKingSquare(true);
//    list<ChessMove> whiteKingLegalMoves = kingLegalMovesCalculation(whiteKing);
    int kingPosX = whiteKing.posX;
    int kingPosY = whiteKing.posY;
    
    bool overlap = false;
    list<ChessMove>::iterator it = blackTeamLegal.begin();
    for(int x = 0; x<blackTeamLegal.size() && !overlap; x++) {
        ChessMove s = *it;
        if( s.movePosX == kingPosX &&
            s.movePosY == kingPosY
           ) {
            overlap = true;
           }
    }
    
    return overlap;
}

// might not work
bool CurrentBoard::blackInCheck() {
    list<ChessMove> whiteTeamLegal = teamAllLegalMoves(whiteTeam);
    Piece blackKing = searchForKingSquare(false);
//    list<ChessMove> whiteKingLegalMoves = kingLegalMovesCalculation(whiteKing);
    int kingPosX = blackKing.posX;
    int kingPosY = blackKing.posY;
    
    bool overlap = false;
    list<ChessMove>::iterator it = whiteTeamLegal.begin();
    for(int x = 0; x<whiteTeamLegal.size() && !overlap; x++) {
        ChessMove s = *it;
        if( s.movePosX == kingPosX &&
            s.movePosY == kingPosY
           ) {
            overlap = true;
           }
    }
    
    return overlap;
}

// sees if white has no legal moves therefore stalemate
bool CurrentBoard::whiteStalemate() {
    bool b = teamAllLegalMoves(whiteTeam).empty();
    return b;
}

// sees if black has no legal moves therefore stalemate
bool CurrentBoard::blackStalemate() {
    bool b = teamAllLegalMoves(blackTeam).empty();
    return b;
}

bool CurrentBoard::blackKingCheckmated() {
    // check to see if the black king legal moves overlaps with opposing team legal moves
    // then if it does and the king is in check then checkmate
    
    if(blackInCheck()) {
        Piece blackKing = searchForKingSquare(false);
//        int kingPosX = blackKing.posX;
//        int kingPosY = blackKing.posY;
        list<ChessMove> legalSquares = kingLegalMovesCalculation(blackKing);
        list<ChessMove> overlappingSquares;
        list<ChessMove> whiteLegal = teamAllLegalMoves(whiteTeam);
        list<ChessMove>::iterator it = whiteLegal.begin();
        for(int i = 0; i<whiteLegal.size(); i++) {
            ChessMove square = *it;
            // see if square matches any of the legalSquares
            bool match = false;
            do {
                list<ChessMove>::iterator it0 = legalSquares.begin();
                ChessMove selected = *it0;
                if(square.movePosX == selected.movePosX
                && square.movePosY == selected.movePosY) {
                    overlappingSquares.push_front(square);
                } else {
                    advance(it0, 1);
                }
            } while (!match);
        }
        
        // all the squares that overlap are also all the legal squares
        if(compareLists(overlappingSquares, legalSquares)) {
            return true;
        }
    }
    
    return false; // TODO: make it actually work
}

bool CurrentBoard::whiteKingCheckmated() {
    
    if(whiteInCheck()) {
        Piece whiteKing = searchForKingSquare(true);
//        int kingPosX = blackKing.posX;
//        int kingPosY = blackKing.posY;
        list<ChessMove> legalSquares = kingLegalMovesCalculation(whiteKing);
        list<ChessMove> overlappingSquares;
        list<ChessMove> blackLegal = teamAllLegalMoves(blackTeam);
        list<ChessMove>::iterator it = blackLegal.begin();
        for(int i = 0; i<blackLegal.size(); i++) {
            ChessMove square = *it;
            // see if square matches any of the legalSquares
            bool match = false;
            do {
                list<ChessMove>::iterator it0 = legalSquares.begin();
                ChessMove selected = *it0;
                if(square.movePosX == selected.movePosX
                && square.movePosY == selected.movePosY) {
                    overlappingSquares.push_front(square);
                } else {
                    advance(it0, 1);
                }
            } while (!match);
        }
        
        // all the squares that overlap are also all the legal squares
        if(compareLists(overlappingSquares, legalSquares)) {
            return true;
        }
    }
    
    return false; // TODO: make it actually work
}

bool CurrentBoard::drawByRepetition() {
    
    // go through list of deadboards
    // check through the list if the current board has been repeated before if it has add one to the repetition value
    // then if the repetition value is 3 return true
    
    // looks messy but i think its kind of cool
    // will be a pain to go through afterwards but not really after you disect a little
    if(deadBoardList.empty()) {
        deadBoardList.push_front(returnDeadBoard());
    } else {
        list<DeadBoard>::iterator it = deadBoardList.begin();
        DeadBoard selected = *it;
        DeadBoard current = returnDeadBoard();
        for(int i = 0; i<deadBoardList.size(); i++) {
            if(selected.arrangementSame(current.storedArrangement)) {
                selected.addRepitition();
                if(selected.repetitionNumber() == 3) {
                    return true;
                }
            }
            advance(it,1);
        }
    }
    
    return false;
}

DeadBoard CurrentBoard::returnDeadBoard() {
    return DeadBoard(arrangement); // idk why i like deadboard so much as a class
}

void CurrentBoard::drawBoard() {
    
    for(int y = 7; y>=0; y--) {
        switch(y) {
            case 7:
                drawTopRow();
                break;
            default:
                drawMiddleRow();
                break;
        }
        for(int x = 0; x<8; x++) {
            
            if(x == 0) {
                cout << "\t" << y+1 << " ";
            }
            
            int blackWhite = arrangement[x][y].whitePiece;
            int pieceType = arrangement[x][y].pieceType;
            
            if(x == 7) {
                drawPieceBox(pieceType, true, blackWhite);
            } else {
                drawPieceBox(pieceType, false, blackWhite);
            }
            
            // left hand side column labeling
            
            
        }
    }
    drawBottomRow();
    
}

void CurrentBoard::drawMiddleRow() {
    cout << "\t  ├───┼───┼───┼───┼───┼───┼───┼───┤" << endl;
}

void CurrentBoard::drawTopRow() {
    cout << "\t  ┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl;
}

void CurrentBoard::drawBottomRow() {
    cout << "\t  └───┴───┴───┴───┴───┴───┴───┴───┘" << endl;
    cout << "\t    a   b   c   d   e   f   g   h  " << endl;
}

void CurrentBoard::drawPieceBox(int pieceType, bool end, bool whitePiece) {
    
    cout << "| ";
    
    //♔♕♖♗♘♙♚♛♜♝♞♟︎
    
    switch(pieceType) {
        case -1: // Empty
            cout << " ";
            break;
            
        case 0: // Pawn
            if(whitePiece) {
                cout << "♟︎";
            } else {
                cout << "♙";
            }
            
            break;
            
        case 1: // Knight
            if(whitePiece) {
                cout << "♞";
            } else {
                cout << "♘";
            }
            break;
            
        case 2: // Bishop
            if(whitePiece) {
                cout << "♝";
            } else {
                cout << "♗";
            }
            break;
            
        case 3: // Rook
            if(whitePiece) {
                cout << "♜";
            } else {
                cout << "♖";
            }
            break;
        case 4: // Queen
            if(whitePiece) {
                cout << "♛";
            } else {
                cout << "♕";
            }
            break;
        case 5: // King
            if(whitePiece) {
                cout << "♚";
            } else {
                cout << "♔";
            }
            break;
        default:
            break;
    }
    cout << " ";
    
    if(end) {
        cout << "│" << endl;
    }
    
}

/// wow, just found out how to "epxlicitly ..." initialize these team variables
CurrentBoard::CurrentBoard() : whiteTeam(true), blackTeam(false) {
    
    this->whiteTeam = Team(true);
    this->blackTeam = Team(false);
    
    this->arrangement = turnEmptyToStartingBoard(makeEmptyArrangmentArr());
}

// This function makes an arrangement where all pieces are -1 (i.e. empty)
vector<vector<Piece>> CurrentBoard::makeEmptyArrangmentArr() {
    
    // placeholder if you can call it that
    // all pieces set to one value but will be changed in the following for loop
    vector<vector<Piece>> arr(8,vector<Piece>(8,Piece(-1, 0, 0, true)));
    
    for(int y = 7; y>= 0; y--) {
        for(int x = 0; x<8; x++) {
            arr[x][y] = Piece(-1, x, y, true);
        }
    }
    
    return arr;
    
}

// this vector uses an empty arrangement as all the posX and posY are defined then adds in the pieces where they should be
vector<vector<Piece>> CurrentBoard::turnEmptyToStartingBoard(vector<vector<Piece>> emptyArr) {
    
    vector<vector<Piece>> updated = emptyArr;
    
    int y0 = 0; // white back row
    int y1 = 1; // white pawn row
    int y7 = 7; // black back row
    int y6 = 6; // black pawn row
    
    // Piecetype, xPos, yPos, w/b
    
    for(int x = 0; x<8; x++) {
        // pawns
        updated[x][y1] = Piece(0, x, y0, true);
        updated[x][y6] = Piece(0, x, y6, false);
//        updated[x][y1] = Piece(0, x, y1, true);
        
    }
//    
    // rooks
    updated[0][y0] = Piece(3, 0, y0, true);
    updated[7][y0] = Piece(3, 7, y0, true);
    updated[0][y7] = Piece(3, 0, y7, false);
    updated[7][y7] = Piece(3, 7, y7, false);
    
    // knights
    updated[1][y0] = Piece(1 ,1, y0, true);
    updated[6][y0] = Piece(1 ,1, y0, true);
    updated[1][y7] = Piece(1 ,1, y7, false);
    updated[6][y7] = Piece(1 ,1, y7, false);
    
    // bishops
    updated[2][y0] = Piece(2 ,1, y0, true);
    updated[5][y0] = Piece(2 ,1, y0, true);
    updated[2][y7] = Piece(2 ,1, y7, false);
    updated[5][y7] = Piece(2 ,1, y7, false);
    
    // queen
    updated[3][y0] = Piece(4 ,3, y0, true);
    updated[3][y7] = Piece(4 ,3, y7, false);
    
    // king
    updated[4][y0] = Piece(5 ,4, y0, true);
    updated[4][y7] = Piece(5 ,4, y7, false);
    
    return updated;
    
}


bool CurrentBoard::blackHasLegalMoves() {
    // go through all the pieces until a single legal move is found
    
    return false; // TODO: make it actually work
}

bool CurrentBoard::whiteHasLegalMoves() {
    // go through all the pieces until a single legal move is found
    
    return false; // TODO: make it actually work
}

bool CurrentBoard::whiteKingHasLegalMoves() {
    // go through all legal moves of opposite team and if they cover the legal squares for the king and the king
    // is not in check then this is true
    
    return false; // TODO: make it actually work
}

bool CurrentBoard::blackKingHasLegalMoves() {
    // go through all legal moves of opposite team and if they cover the legal squares for the king and the king
    // is not in check then this is true
    
    return false; // TODO: make it actually work
}

Piece CurrentBoard::searchForKingSquare(bool whiteTeamKing) {
    Piece king(-1, 0, 0, true); // placeholder
    if(whiteTeamKing) {
        list<Piece> whitePieces = whiteTeam.alivePieces;
        list<Piece>::iterator it = whitePieces.begin();
//        Piece s = *it;
        bool kingFound = false;
        for(int x = 0; x<whitePieces.size() && !kingFound; x++) {
            Piece s = *it;
            if(s.pieceType == 5) {
                kingFound = true;
                king = s;
            }
            advance(it, 1);
        }
    } else {
        list<Piece> blackPieces = blackTeam.alivePieces;
        list<Piece>::iterator it = blackPieces.begin();
//        Piece s = *it;
        bool kingFound = false;
        for(int x = 0; x<blackPieces.size() && !kingFound; x++) {
            Piece s = *it;
            if(s.pieceType == 5) {
                kingFound = true;
                king = s;
            }
            advance(it, 1);
        }
    }
    
    return king;
}

// do not input piecetype -1, i.e. empty square
list<ChessMove> CurrentBoard::checkLegalMovesOfPiece(Piece p) {
    list<ChessMove> legal;
    int t = p.pieceType;
    
    // need to test this since everything relies on it
    // switch statements wouldn't work so here is some bad code
    if(t == 0) {
        legal = pawnLegalMovesCalculation(p);
    }
    
    if(t == 1) {
        legal = knightLegalMovesCalculation(p);
    }
    
    if(t == 2) {
        legal = bishopLegalMovesCalculation(p);
    }
    
    if(t == 3) {
        legal = rookLegalMovesCalculation(p);
    }
    
    if(t == 4) {
        legal = queenLegalMovesCalculation(p);
    }
    
    if(t == 5) {
        legal = kingLegalMovesCalculation(p);
    }
    
    
    return legal;
}

// it is possible that all of these may not work :/
// same goes for everything but yk
list<ChessMove> CurrentBoard::pawnLegalMovesCalculation(Piece p) {
    
    list<ChessMove> legal;
    
    // Pawn
    
    int x = p.posX;
    int y = p.posY;
    //    int t = p.pieceType; not needed since its just for pawns
    bool wT = p.whitePiece;
    
    // i might just redo all of this
    
    if(wT) {
        // white team
        // top right
        // im doing it this way because idk
        if(x+1 <= 7 && y+1 <= 7) {
            if(arrangement[x+1][y+1].pieceType > -1) {
                if(arrangement[x+1][y+1].pieceType != 5) {
                    legal.push_front(ChessMove(x+1,y+1));
                }
            }
        }
        
        // top left
        if(x-1 > 0 && y+1 <= 7) {
            if(arrangement[x-1][y+1].pieceType > -1) {
                if(arrangement[x-1][y+1].pieceType != 5) {
                    legal.push_front(ChessMove(x-1,y+1));
                }
            }
        }
    
        // move forwards twice at the start
        if(y == 1) {
            if(arrangement[x][y+1].pieceType == -1 && arrangement[x][y+2].pieceType == -1) {
                legal.push_front(ChessMove(x, y+2));
            }
        }
        
        // forwards
        if(y+1 <= 7) {
            if(arrangement[x][y+1].pieceType == -1) {
                legal.push_front(ChessMove(x,y+1));
            }
        }
        
    } else {
        // black team
        // bottom right
        if(x+1 <= 7 && y-1 <= 7) {
            if(arrangement[x+1][y-1].pieceType > -1) {
                if(arrangement[x+1][y-1].pieceType != 5) {
                    legal.push_front(ChessMove(x+1,y-1));
                }
            }
        }
        
        // bottom left
        if(x-1 > 0 && y-1 <= 7) {
            if(arrangement[x-1][y-1].pieceType > -1) {
                if(arrangement[x-1][y-1].pieceType != 5) {
                    legal.push_front(ChessMove(x-1,y-1));
                }
            }
        }
    
        // move forwards twice at the start
        if(y == 6) {
            if(arrangement[x][y-1].pieceType == -1 && arrangement[x][y-2].pieceType == -1) {
                legal.push_front(ChessMove(x, y-2));
            }
        }
        
        // forwards
        if(y-1 >= 0) {
            if(arrangement[x][y-1].pieceType == -1) {
                legal.push_front(ChessMove(x,y-1));
            }
        }
        
    }
        return legal;
}

list<ChessMove> CurrentBoard::knightLegalMovesCalculation(Piece p) {
    // knight
        // top left
        /*
         [][]
           []
           --[][]
               []
         */
    
    list<ChessMove> legal;
    
    int x = p.posX;
    int y = p.posY;
//    int t = p.pieceType; not needed since just knights
    bool wT = p.whitePiece;
     
    
    return legal;
}

list<ChessMove> CurrentBoard::bishopLegalMovesCalculation(Piece p) {
    
    // this probably wont work
    
    list<ChessMove> legal;
    
    int x = p.posX;
    int y = p.posY;
//    int t = p.pieceType;
    int desiredX = x;
    int desiredY = y;
    
    
    bool pieceOrSquareHit = false;
//
//    // top right
//    do {
//        desiredX++;
//        desiredY++;
//        pieceOrSquareHit =
//        arrangement[desiredX][desiredY].pieceType >= 0 || // piece
//        desiredX <= 7 || desiredY <= 7; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(desiredX, desiredY));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            } else {
//                if(arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//    
//    // top left
//    desiredX = 0;
//    desiredY = 0;
//    pieceOrSquareHit = false;
//    do {
//        desiredX--;
//        desiredY++;
//        pieceOrSquareHit =
//        arrangement[desiredX][desiredY].pieceType >= 0 || // piece
//        desiredX >= 0 || desiredY < 7; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(desiredX, desiredY));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            } else {
//                if(arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//
//    // bot left
//    desiredX = 0;
//    desiredY = 0;
//    pieceOrSquareHit = false;
//    do {
//        desiredX--;
//        desiredY--;
//        pieceOrSquareHit =
//        arrangement[desiredX][desiredY].pieceType >= 0 || // piece
//        desiredX >= 0 || desiredY >= 7; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(desiredX, desiredY));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            } else {
//                if(arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//
//    // bot right
//    desiredX = 0;
//    desiredY = 0;
//    pieceOrSquareHit = false;
//    do {
//        desiredX++;
//        desiredY--;
//        pieceOrSquareHit =
//        arrangement[desiredX][desiredY].pieceType >= 0 || // piece
//        desiredX <= 7 || desiredY >= 0; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(desiredX, desiredY));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            } else {
//                if(arrangement[desiredX][desiredY].whitePiece
//                   && arrangement[desiredX][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, desiredY));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//    
//    
    return legal;
    
}

list<ChessMove> CurrentBoard::rookLegalMovesCalculation(Piece p) {
    list<ChessMove> legal;
    
    int x = p.posX;
    int y = p.posY;
//    int t = p.pieceType;
    int desiredX = x;
    int desiredY = y;
    
    
    bool pieceOrSquareHit = false;
//    
//    // top
//    do {
////        desiredX++;
//        desiredY++;
//        pieceOrSquareHit =
//        arrangement[x][desiredY].pieceType >= 0 || // piece
//        /*desiredX <= 7 ||*/ desiredY <= 7; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(x, desiredY));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[x][desiredY].whitePiece
//                   && arrangement[x][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(x, desiredY));
//                }
//            } else {
//                if(arrangement[x][desiredY].whitePiece
//                   && arrangement[x][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(x, desiredY));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//    
//    // bot
//    do {
////        desiredX++;
//        desiredY--;
//        pieceOrSquareHit =
//        arrangement[x][desiredY].pieceType >= 0 || // piece
//        /*desiredX <= 7 ||*/ desiredY >=0; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(x, desiredY));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[x][desiredY].whitePiece
//                   && arrangement[x][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(x, desiredY));
//                }
//            } else {
//                if(arrangement[x][desiredY].whitePiece
//                   && arrangement[x][desiredY].pieceType !=5) {
//                    legal.push_front(ChessMove(x, desiredY));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//    
//    // right
//    do {
//        desiredX++;
////        desiredY++;
//        pieceOrSquareHit =
//        arrangement[desiredX][y].pieceType >= 0 || // piece
//        desiredX <= 7 /*|| desiredY <= 7*/; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(desiredX, y));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[desiredX][y].whitePiece
//                   && arrangement[desiredX][y].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, y));
//                }
//            } else {
//                if(arrangement[desiredX][y].whitePiece
//                   && arrangement[desiredX][y].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, y));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//    
//    // left
//    do {
//        desiredX--;
////        desiredY++;
//        pieceOrSquareHit =
//        arrangement[desiredX][y].pieceType >= 0 || // piece
//        desiredX >= 0 /*|| desiredY <= 7*/; // invalid square
//        
//        if(!pieceOrSquareHit) {
//            legal.push_front(ChessMove(desiredX, y));
//        }
//        
//        if(pieceOrSquareHit) {
//            if(p.whitePiece) {
//                if(!arrangement[desiredX][y].whitePiece
//                   && arrangement[desiredX][y].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, y));
//                }
//            } else {
//                if(arrangement[desiredX][y].whitePiece
//                   && arrangement[desiredX][y].pieceType !=5) {
//                    legal.push_front(ChessMove(desiredX, y));
//                }
//            }
//        }
//    } while (!pieceOrSquareHit);
//    
    return legal;
}

list<ChessMove> CurrentBoard::queenLegalMovesCalculation(Piece p) {
    list<ChessMove> legal;
//    
//    list<ChessMove> rookMovement = rookLegalMovesCalculation(p);
//    list<ChessMove> bishopMovement = bishopLegalMovesCalculation(p);
//    // merge function doesn't want to work and idk why
//    
//    list<ChessMove>::iterator it = bishopMovement.begin();
//    ChessMove selected = *it;
//    for(int i = 0; i<bishopMovement.size(); i++) {
//        rookMovement.push_front(selected);
//        advance(it, 1);
//    }
//    bishopMovement.end();
//    legal = rookMovement;
//    
    return legal;
}

list<ChessMove> CurrentBoard::kingLegalMovesCalculation(Piece p) {
    list<ChessMove> legal;
    
    int x = p.posX;
    int y = p.posY;
//    int t = p.pieceType; not needed
    int w = p.whitePiece;
//    
//    if(w) {
//        // top right
//        if(!arrangement[x+1][y+1].whitePiece
//           && x+1 <= 7 && y+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x+1,y+1));
//        }
//        // top left
//        if(!arrangement[x-1][y+1].whitePiece
//           && x-1 >= 0 && y+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x-1,y+1));
//        }
//        // bot left
//        if(!arrangement[x-1][y-1].whitePiece
//           && x-1 >= 0 && y-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x-1,y-1));
//        }
//        // bot right
//        if(!arrangement[x+1][y-1].whitePiece
//           && x+1 <= 7 && y-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x+1,y-1));
//        }
//        // forwards
//        if(!arrangement[x][y+1].whitePiece
//           && y+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x,y+1));
//        }
//        // backwards
//        if(!arrangement[x][y-1].whitePiece
//           && y-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x,y-1));
//        }
//        // left
//        if(!arrangement[x-1][y].whitePiece
//           && x-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x-1,y));
//        }
//        // right
//        if(!arrangement[x+1][y].whitePiece
//           && x+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x+1,y));
//        }
//    } else {
//        // top right
//        if(arrangement[x+1][y+1].whitePiece
//           && x+1 <= 7 && y+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x+1,y+1));
//        }
//        // top left
//        if(arrangement[x-1][y+1].whitePiece
//           && x-1 >= 0 && y+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x-1,y+1));
//        }
//        // bot left
//        if(arrangement[x-1][y-1].whitePiece
//           && x-1 >= 0 && y-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x-1,y-1));
//        }
//        // bot right
//        if(arrangement[x+1][y-1].whitePiece
//           && x+1 <= 7 && y-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x+1,y-1));
//        }
//        // forwards
//        if(arrangement[x][y+1].whitePiece
//           && y+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x,y+1));
//        }
//        // backwards
//        if(arrangement[x][y-1].whitePiece
//           && y-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x,y-1));
//        }
//        // left
//        if(arrangement[x-1][y].whitePiece
//           && x-1 >= 0
//           ) {
//            legal.push_front(ChessMove(x-1,y));
//        }
//        // right
//        if(arrangement[x+1][y].whitePiece
//           && x+1 <= 7
//           ) {
//            legal.push_front(ChessMove(x+1,y));
//        }
//    }
    
    return legal;
}

list<ChessMove> CurrentBoard::teamAllLegalMoves(Team t) {
    
    list<Piece> allPieces = t.alivePieces;
    list<ChessMove> allMoves;
//    // may not work, like so many other things
//    list<Piece>::iterator it = allPieces.begin();
//    Piece selected = *it;
//    for(int i = 0; i<allPieces.size(); i++) {
//        allMoves = mergeV2(checkLegalMovesOfPiece(selected), allMoves);
//        advance(it, 1);
//    }
    
    return allMoves;
}

list<ChessMove> CurrentBoard::mergeV2(list<ChessMove> a, list<ChessMove> b) {
    
    list<ChessMove>::iterator it = b.begin();
    ChessMove selected = *it;
    for(int i = 0; i<a.size(); i++) {
        a.push_front(selected);
        advance(it, 1);
    }
    return a;
}

bool CurrentBoard::compareLists(list<ChessMove> a, list<ChessMove> b) {
    bool allMatch = true;
    
    if(a.size() != b.size()) {
        return false;
    }
    
    list<ChessMove>::iterator aIterator = a.begin();
    list<ChessMove>::iterator bIterator = b.begin();
    
    do {
        ChessMove aS = *aIterator;
        ChessMove bS = *bIterator;
        
        if(
           aS.movePosX != bS.movePosX &&
           aS.movePosY != bS.movePosY
           ) {
               allMatch = false;
        }
        
        advance(aIterator, 1);
        advance(bIterator, 1);
        
    } while (allMatch);
    
    return allMatch;
}

void CurrentBoard::drawDebug() {
    
    for(int y = 7; y>= 0; y--) {
        for(int x = 0; x<8; x++) {
            int n = arrangement[x][y].pieceType;
            cout << "[" << n;
            if(!(n == -1)) {
                cout << " ";
            }
            cout << "]";
            
        }
        cout << "\n";
    }
    
    cout << "\n";
    
    for(int y = 7; y>= 0; y--) {
        for(int x = 0; x<8; x++) {
            cout << "[" << x << "," << y << "]";
        }
        cout << "\n";
    }
    
}

bool CurrentBoard::pieceExists(int pieceType) {
    
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(arrangement[x][y].pieceType == pieceType) {
                return true;
            }
        }
    }
    return false;
}

bool CurrentBoard::pieceExistsOnSquare(Piece p) {
    if(
       arrangement[p.posX][p.posY].pieceType == p.pieceType // same piece type
    && arrangement[p.posX][p.posY].whitePiece == p.whitePiece // same team
       ) {
           return true;
       }
    return false;
}
