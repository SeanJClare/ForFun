#ifndef Connect4_H
#define Connect4_H

#include <string>

class Connect4{
    
    /*
    enum Weights : int{
        WIN = 40,  // AKA Connect4
        BLOCK = 35, // Deny player WIN
        CONNECT3 = 30,
        BLOCK3 = 25, 
        CONNECT2 = 20,
        BLOCK2 = 15,
        RANDOM = 10 // AKA 1 piece, no connections
    };
    */

   enum moveType : int{
        WIN = 999,  // AKA Connect4
        BLOCKWIN = 800, // Deny player WIN
        CONNECT3 = 30,
        BLOCK3 = 25, 
        CONNECT2 = 20,
        BLOCK2 = 15,
    };
   
   struct columnAtribute {
       bool present = false;
       int moveValue;
   };

   struct columnAtributes {
       columnAtribute WIN;
       columnAtribute BLOCKWIN;
       columnAtribute CONNECT3;
       columnAtribute BLOCK3;
       columnAtribute CONNECT2;
       columnAtribute BLOCK2;
       int weight=0;
   };

public:
    enum Slot {
        EMPTY = '.',
        NOUGHT = 'O',
        CROSS = 'X'
    };
    Connect4();
    Connect4(Slot player, Slot comp);
    Connect4(Slot player, Slot comp, int colsIn, int rowsIn);
    Connect4(const Connect4 &toCopy);
    ~Connect4();
    void compMove();
    void playerMove();
    bool getGameOver();
    void playGame(bool playerFirst);
    
private:
const int SCORE_PER_PIECE = 10;

bool checkWin();
void dropPiece(int column, Slot toDrop);
// Calculates each columns value for computers move
void weighColumn(int col);  

bool checkWins(int col, int row);
bool checkBlockWins(int col, int row);
bool checkConnect3(int col, int row);
bool checkBlock3(int col, int row);
bool checkConnect2(int col, int row);
bool checkBlock2(int col, int row);

// Utility methods
int getBottomSlot(int column);
void printBoard();
void resetAtributes();

// Private Attributes 
Connect4::Slot** board;
int cols = 7;
int rows = 7;
columnAtributes* weights; // For calculating best col to drop
bool gameOver=false;
int maxTurns=cols*rows; // For ending game with full board
int turnCount=0;

// Default Piece Choices
Slot PLAYER = Slot::NOUGHT;
Slot COMP = Slot::CROSS;
};
#endif