//
//  deadBoard.cpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#include "headers/deadBoard.hpp"

DeadBoard::DeadBoard(vector<vector<Piece>> arrangement) {
    
    storedArrangement = arrangement;
    repetitions = 0;
    
}

bool DeadBoard::arrangementSame(vector<vector<Piece>> comparisonArrangement) {
    
    bool b = true;
    
    for(int y = 0; y<8 && b; y++) {
        for(int x=0; x<8 && b; x++) {
            
            int i0 = comparisonArrangement[x][y].pieceType;
            int i1 = storedArrangement[x][y].pieceType;
            
            if(i0 != i1) {
                b = false;
            }
            
        }
    }
    
    return b;
    
}

void DeadBoard::addRepitition() {
    repetitions++;
}

int DeadBoard::repetitionNumber() {
    return repetitions;
}

