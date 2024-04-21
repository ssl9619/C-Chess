//
//  intendedMove.hpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#ifndef intendedMove_hpp
#define intendedMove_hpp

#include <stdio.h>

class IntendedMove {
public:
    int intendedPosX;
    int intendedPosY;
    int originalPosX;
    int originalPosY;
    int desiredPiece;
    bool whiteTeam;
    IntendedMove(int originalPosX, int originalPosY, int intendedPosX, int intendedPosY, int desiredPiece, bool whitePiece);
    int validation(); // returns an error code
    
};

#endif /* intendedMove_hpp */
