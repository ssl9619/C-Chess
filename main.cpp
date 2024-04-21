//
//  main.cpp
//  C++ Chess xCode v3
//
//  Created by Saeed Lootah on 10/04/2024.
//

#include <iostream>
#include <string>
#include "headers/sketch.hpp"

using namespace std;


string winMessages(int winType) {

    
    return "null"; // TODO: make
};


string errorMessages(int errorCode) {
    
    
    return "null"; // TODO: make
}

// sets up the sketch class and does everything from there

IntendedMove inputIntededMove(bool whiteTeam) {
    
    cout << "Which piece would you like to move?" << endl;
    string pieceInput;
    string pieceTypeString;
    bool validInput = false;
    int pieceInt = 0;
    cin >> pieceInput;
    do {
        pieceInt = 0;
        bool fullWord = false;
        
        if(pieceInput == "pawn") {
            pieceTypeString = "pawn";
            // piece int already 0
            fullWord = true;
            validInput = true;
        }
        if(pieceInput == "knight") {
            pieceTypeString = "knight";
            pieceInt = 1;
            fullWord = true;
            validInput = true;
        }
        if(pieceInput == "bishop") {
            pieceTypeString = "bishop";
            pieceInt = 2;
            fullWord = true;
            validInput = true;
        }
        if(pieceInput == "rook") {
            pieceTypeString = "rook";
            pieceInt = 3;
            fullWord = true;
            validInput = true;
        }
        if(pieceInput == "queen") {
            pieceTypeString = "queen";
            pieceInt = 4;
            fullWord = true;
            validInput = true;
        }
        if(pieceInput == "king") {
            pieceTypeString = "king";
            pieceInt = 5;
            fullWord = true;
            validInput = true;
        }
        
        if(!fullWord) {
            switch (pieceInput[0]) {
                case 'p':
                case 'P':
                    pieceTypeString = "pawn";
                    validInput = true;
                    break;
                case 'k':
                case 'K':
                    pieceTypeString = "knight";
                    validInput = true;
                    break;
                case 'b':
                case 'B':
                    pieceTypeString = "bishop";
                    validInput = true;
                    break;
                case 'r':
                case 'R':
                    pieceTypeString = "rook";
                    validInput = true;
                    break;
                case 'q':
                case 'Q':
                    pieceTypeString = "queen";
                    validInput = true;
                    break;
                case 'g':
                case 'G':
                    pieceTypeString = "king";
                    validInput = true;
                    break;
                default:
                    validInput = false;
                    break;
            }
        }
        if(!validInput) {
            cout << "Incorrect input. Please try again." << endl;
            cin >> pieceInput;
        }
    } while(!validInput);
    
    // piece square definition
    int pieceXPos = 0;
    int pieceYPos = 0;
    cout << "\nWhich square is your " << pieceTypeString << " on?" << endl;
    string pieceLocationString;
    cin >> pieceLocationString;
    
    do {
        bool firstCharacterCorrect = false;
        bool secondCharacterCorrect = false;
        pieceXPos = 0;
        pieceYPos = 0;
        if(pieceLocationString.length() == 2) {
            
            // checking first character
            switch (pieceLocationString[0]) {
                case 'a':
                case 'A':
                    pieceXPos = 0;
                    firstCharacterCorrect = true;
                    break;
                case 'b':
                case 'B':
                    pieceXPos = 1;
                    firstCharacterCorrect = true;
                    break;
                case 'c':
                case 'C':
                    pieceXPos = 2;
                    firstCharacterCorrect = true;
                    break;
                case 'd':
                case 'D':
                    pieceXPos = 3;
                    firstCharacterCorrect = true;
                    break;
                case 'e':
                case 'E':
                    pieceXPos = 4;
                    firstCharacterCorrect = true;
                    break;
                case 'f':
                case 'F':
                    pieceXPos = 5;
                    firstCharacterCorrect = true;
                    break;
                case 'g':
                case 'G':
                    pieceXPos = 6;
                    firstCharacterCorrect = true;
                    break;
                case 'h':
                case 'H':
                    pieceXPos = 7;
                    firstCharacterCorrect = true;
                    break;
                default:
                    break;
            }
            
            // checking second char
            if(firstCharacterCorrect) {
                switch (pieceLocationString[1]) {
                    case '1':
                        pieceYPos = 0;
                        secondCharacterCorrect = true;
                        break;
                    case '2':
                        pieceYPos = 1;
                        secondCharacterCorrect = true;
                        break;
                    case '3':
                        pieceYPos = 2;
                        secondCharacterCorrect = true;
                        break;
                    case '4':
                        pieceYPos = 3;
                        secondCharacterCorrect = true;
                        break;
                    case '5':
                        pieceYPos = 4;
                        secondCharacterCorrect = true;
                        break;
                    case '6':
                        pieceYPos = 5;
                        secondCharacterCorrect = true;
                        break;
                    case '7':
                        pieceYPos = 6;
                        secondCharacterCorrect = true;
                        break;
                    case 8:
                        pieceYPos = 7;
                        secondCharacterCorrect = true;
                        break;
                    default:
                        break;
                }
            }
            
        } else {
            firstCharacterCorrect = false;
            secondCharacterCorrect = false;
        }
        
        if(!validInput && !firstCharacterCorrect && !secondCharacterCorrect) {
            cout << "Incorrect input. Please try again." << endl;
            cin >> pieceLocationString;
        }
    } while (!validInput);
    
    // for debug purposes
    cout << pieceXPos << ", " << pieceYPos << endl;
    cout << "\nWhich square would you like to move your " << pieceTypeString << " to?" << endl;
    int newXPos = 0;
    int newYPos = 0;
    string newPosititionString;
    do {
        validInput = true;
        cin >> newPosititionString;
        if(newPosititionString.length() == 2) {
            
            // checking first character
            switch (newPosititionString[0]) {
                case 'a':
                case 'A':
                    newXPos = 0;
                    break;
                case 'b':
                case 'B':
                    newXPos = 1;
                    break;
                case 'c':
                case 'C':
                    newXPos = 2;
                    break;
                case 'd':
                case 'D':
                    newXPos = 3;
                    break;
                case 'e':
                case 'E':
                    newXPos = 4;
                    break;
                case 'f':
                case 'F':
                    newXPos = 5;
                    break;
                case 'g':
                case 'G':
                    newXPos = 6;
                    break;
                case 'h':
                case 'H':
                    newXPos = 7;
                    break;
                default:
                    validInput = false;
                    break;
            }
            // checking second char
            if(validInput) {
                switch (newPosititionString[1]) {
                    case '1':
                        newYPos = 0;
                        break;
                    case '2':
                        newYPos = 1;
                        break;
                    case '3':
                        newYPos = 2;
                        break;
                    case '4':
                        newYPos = 3;
                        break;
                    case '5':
                        newYPos = 4;
                        break;
                    case '6':
                        newYPos = 5;
                        break;
                    case '7':
                        newYPos = 6;
                        break;
                    case 8:
                        newYPos = 7;
                        break;
                    default:
                        validInput = false;
                        break;
                }
            }
            
        } else {
            validInput = false;
        }
        
        
        
        if(!validInput) {
            cout << "Incorrect input. Please try again." << endl;
            cout << "Initial square and landing square cannot be the same." << endl;
            cin >> newPosititionString;
        }
        
    } while (!validInput);
    cout << newXPos << ", " << newYPos << endl;
    
    return IntendedMove(pieceXPos, pieceYPos, newXPos, newYPos, pieceInt, whiteTeam);
}

void playChess() {
    // TODO: make

    //TODO:  for aesthetics put the text on what to do and the win condition beside the chess board
    cout << "\n=~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~" << endl;
    cout << "\n" << endl;
    Sketch sketchObject(true);
    sketchObject.printBoard();
    
    // piece selection
    bool whiteTurn = true;
    bool gameOver = false;
    do {
        // thing
        if(whiteTurn) {
            cout << "\nWhite's turn:" << endl;
        } else {
            cout << "\nBlack's turn:" << endl;
        }
        
        IntendedMove i = inputIntededMove(whiteTurn);
        // check if valid
        /// check for an error
        Piece p(i.desiredPiece, i.originalPosX, i.originalPosY, i.whiteTeam);
        
        ChessMove move(i.intendedPosX, i.intendedPosY);
        
        int possibleE = sketchObject.returnPossibleError(p, move);
        
        cout << "legality: "<< possibleE << endl;; // should be 0 or 3 as of writing
        
        sketchObject.updateChessBoard(i);
        
        cout << "\n=~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~\n" << endl;
        
        sketchObject.printBoard();
        
        whiteTurn = !whiteTurn;
        
        //TODO: something is wrong with the initial square and landing square cannot be the same message
        
        
    } while (!gameOver);
    cout << "\nWhite's turn:" << endl;
    
    
    
    
}

void printTutorialMessage() {
    cout << "\n" << endl;
    cout << "=~=~=~=TUTORIAL=~=~=~=~=~=~=~=~=TUTORIAL=~=~=~=~=~=~=~=~=TUTORIAL=~=~=~=" << endl;
    cout << "           (You are expected to know how to play chess)" << endl;
    cout << "             (This is just how to type in the inputs)" << endl;
    cout << "                   (No input is case sensitive)\n" << endl;
    cout << "1. Type in a letter to           2. Type in the row and column that you" << endl;
    cout << "indicate which piece to              would like the piece to land" << endl;
    cout << "move                                   -For example:" << endl;
    cout << "\t-P for pawn                            P e2 e4" << endl; // TODO: on first move pawn can move two pieces, need to program that
    cout << "\t-K for knight                          i.e. Pawn on e2 to e4" << endl;
    cout << "\t-B for bishop" << endl;
    cout << "\t-Q for queen                   3. In the event that the move is invalid" << endl;
    cout << "\t-G for king                       you'll be told the correct input\n" << endl; // TODO: continue
    cout << "=~=~=~=TUTORIAL=~=~=~=~=~=~=~=~=TUTORIAL=~=~=~=~=~=~=~=~=TUTORIAL=~=~=~=" << endl;
    cout << "\nWould you like to play xCode Chess or quit the program?" << endl;
    cout << "q for quit and p for play (not case sensitive)" << endl;
    char input;
    bool validInput = false;
    do {
        cin >> input;
        switch(input) {
            case 'p':
            case 'P':
                playChess();
                validInput = true;
                break;
            case 'q':
            case 'Q':
                std::exit(0);

                break;
            default:
                validInput = false;
                cout << "Incorrect input. Please try again." << endl;
                break;
        }
    } while (!validInput);
    
}

void tutorialOrPlay(char input) {
    
    bool b = input == 'p' || input == 'P' || input == 't' || input == 'T';
    
    if(!b) {
        cout << "Input written incorrectly. Please type in 'p' to play or 't' to see the tutorial";
        char input2;
        cin >> input2;
        tutorialOrPlay(input2); // there is probably a better way of doing this than recursion but who cares
    }
    
    bool p = input == 'p' || input == 'P';
    
    if(p) {
        playChess(); // TODO: make
    } else {
        printTutorialMessage();
    }
    
    
}

void printLogo() {
    cout << "\n\n\n=~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~=~=" << endl;
    char str[] =  {"                __   __   __   ___     __        ___  __   __ "};
    char str0[] = {"           \\_/ /  ` /  \\ |  \\ |__     /  ` |__| |__  /__` /__`"};
    char str1[] = {"           / \\ \\__, \\__/ |__/ |___    \\__, |  | |___ .__/ .__/\n"};
    for(char s : str) {
        cout << s;
    } cout << "\n";
    
    for(char s : str0) {
        cout << s;
    } cout << "\n";
    
    for(char s : str1) {
        cout << s;
    } cout << "\n";
    cout << "=~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~=~=" << endl;
    cout << "                   │ Made by Saeed Lootah │ ssl9619 │                   " << endl;
    cout << "      ♔ ♔ ♔        ├──────────────────────┴─────────┤        ♚ ♚ ♚      " << endl;
    cout << "                   │  Special thanks to Abdulraheem │                   " << endl;
    cout << "=~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~==~=~=~=~=\n" << endl;
    
}

int main(int argc, const char * argv[]) {
    
    printLogo();
    cout << "Would you like to play?" << endl;
    cout << "Type in t for tutorial or p to play (not case-sensitive)" << endl;
    char input;
    cin >> input;
    tutorialOrPlay(input);
    
    
    return 0;
}
