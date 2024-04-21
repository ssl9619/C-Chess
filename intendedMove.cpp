//
//  intendedMove.cpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#include "headers/intendedMove.hpp"

IntendedMove::IntendedMove(int originalPosX, int originalPosY, int intendedPosX, int intendedPosY, int desiredPiece, bool whitePiece) {
    this->originalPosX = originalPosX;
    this->originalPosY = originalPosY;
    this->intendedPosX = intendedPosX;
    this->intendedPosY = intendedPosY;
    this->desiredPiece = desiredPiece;
    this->whiteTeam = whitePiece;
}

//int IntendedMove::validation() {
//    
//    // figure out the error codes first and how to do validation for strings
//    
//    return 0;
//}
