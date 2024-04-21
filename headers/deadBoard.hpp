//
//  deadBoard.hpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#ifndef deadBoard_hpp
#define deadBoard_hpp

#include <stdio.h>
#include <copyfile.h>
#include <vector>
#include "piece.hpp"

using namespace std;

class DeadBoard {
public:
    
    vector<vector<Piece>> storedArrangement;
    DeadBoard(vector<vector<Piece>> arrangement);
    bool arrangementSame(vector<vector<Piece>> comparisonArrangement);
    void addRepitition();
    int repetitionNumber();
    
private:
    int repetitions;
    
};

#endif /* deadBoard_hpp */
