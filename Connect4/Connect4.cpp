#include "Connect4.h"
#include <iostream>
#include <chrono>
#include <random>
#include <cstdio>


using std::cout;
using std::cin;
using std::endl;

Connect4::Connect4(){
    // cout<<"DEBUG: rows: "<<rows<<", cols: "<<cols<<"."<<endl;
    board = new Slot* [cols];
    for(int x=0;x<cols;++x){
        board[x] = new Slot[rows];
        for(int y=0;y<rows;++y){
            board[x][y] = Slot::EMPTY;
            // cout<<"board["<<x<<"]["<<y<<"]: "<<board[x][y]<<endl;
        }
    }

    weights = new columnAtributes[cols];
    for(int x=0;x<cols;++x){
        weights[x].WIN.moveValue = WIN;
        weights[x].BLOCKWIN.moveValue = BLOCKWIN;
        weights[x].CONNECT3.moveValue = CONNECT3;
        weights[x].BLOCK3.moveValue = BLOCK3;
        weights[x].CONNECT2.moveValue = CONNECT2;
        weights[x].BLOCK2.moveValue = BLOCK2;
    }

    // this->playGame();
}

Connect4::Connect4(Slot player, Slot comp){

    Connect4::PLAYER = player;
    Connect4::COMP = comp;
    
    // cout<<"DEBUG: playerSlot: "<<(char)PLAYER<<", compSlot: "<<(char)COMP<<"."<<endl;
    
    Connect4();

}
Connect4::Connect4(Slot player, Slot comp, int colsIn, int rowsIn){

    cols = colsIn;
    rows = rowsIn;
    maxTurns = cols*rows;
    
    Connect4(player, comp);
}

Connect4::Connect4(const Connect4 &toCopy){
    this->board = new Slot* [cols];
    for(int x=0;x<cols;++x){
        board[x] = new Slot[rows];
        for(int y=0;y<rows;++y){
            this->board[x][y] = toCopy.board[x][y];
            // cout<<"board["<<x<<"]["<<y<<"]: "<<board[x][y]<<endl;
        }
    }
}

Connect4::~Connect4(){
    for(int x=0;x<cols;++x){
        delete[] board[x];
    }
    delete[] board;
    delete[] weights;
}

void Connect4::playGame(bool playerFirst){
    /*
    cout<<"DEBUG: Player to go First? ";
    if(playerFirst){
        cout<<"TRUE"<<endl;
    }else{
        cout<<"FALSE"<<endl;
    }
    */
    bool playerTurn = playerFirst;

    while(!getGameOver()){
        // cout<<"DEBUG: Player to go? ";
        if(playerTurn){
            // cout<<"TRUE"<<endl;
            printBoard();
            playerMove();
        }else{
            // cout<<"FALSE"<<endl;
            compMove();
        }
    }
}

void Connect4::dropPiece(int column, Slot toDrop){
    
    board[column][getBottomSlot(column)] = toDrop;
    cout<<char(toDrop)<<":"<<std::to_string(column+1)<<endl;
    // printBoard();
    ++turnCount;
    if (checkWin()){
        cout<<"GAME OVER!"<<endl;
    }
}

void Connect4::playerMove(){
    
    printf("Select a column (1 to %i) to drop your piece: ", Connect4::cols);
    int choice = -1;
    cin>>choice;
    while(choice < 1 || choice > cols){
        cout<<"Try again: ";
        cin>>choice;
    }
    dropPiece(choice-1, Connect4::PLAYER);
    // printf("Board slot value: '%c'.\n", board[choice][bottom]);
}

int Connect4::getBottomSlot(int column){
    int bottom = 0;
    while(board[column][bottom] == Slot::EMPTY){
        ++bottom;
    }
    // printf("Column: %i, Bottom: %i\n",column, bottom);
    return bottom -1;
}

bool Connect4::getGameOver(){
    return gameOver;
}

/*  Idea 1: Each tpye of move has a preset weight (connect3, connect2 etc...)
            and each column is assigned the identified moves weight.

            Pros: 
            -Allows for more tactics like building up a column
            
            Cons:
            -Lots of if statements
    
    Idea 2: Count all adjacent same slots and multiply a score by the count,
            which is assigned to a columns value.

            Pros:
            -Dynamic weighting

            Cons:
            -Could be difficult to identify advanced moves, like building up columns
            
 ⭐ Idea 3:  Have an enumeration of boolean flags with values for each column indicating possible moves/outcomes,
            and then accumulate total value of all flags for all columns to determine best move.

            Pros:
            -Clean
            -Allows for extended analysis of possible moves
                -Allows for convienient identification of blocking moves (as the AI goes second)
                -Allows for advanced moves

            Cons:
            -Extensive checking for all possible outcomes in a column
    Idea 4: You just lose.
    
            Cons:
            -You just lose
*/

void Connect4::weighColumn(int column){
    int bottomY = getBottomSlot(column);
    if(bottomY<0){  // Full column
        weights[column].weight=bottomY;
    }else{  // Set column flags

        // Fall row
        // Check wins
        if (checkWins(column, bottomY)){
            weights[column].WIN.present=true;
        }

        // Block Win
        if(checkBlockWins(column, bottomY)){
            weights[column].BLOCKWIN.present=true;
        }

        // Connect 3
        if(checkConnect3(column, bottomY)){
            weights[column].CONNECT3.present=true;
        }
        
        //Block 3
        if(checkBlock3(column, bottomY)){
            weights[column].BLOCK3.present=true;
        }

        //Connect 2
        if(checkConnect2(column, bottomY)){
            weights[column].CONNECT2.present=true;
        }

        //Block 2
        if(checkBlock2(column, bottomY)){
            weights[column].BLOCK2.present=true;
        }

        // Calculate total weight
        if(weights[column].WIN.present){
            weights[column].weight = int(weights[column].WIN.moveValue);
        }else if(weights[column].BLOCKWIN.present){
            weights[column].weight = int(weights[column].BLOCKWIN.moveValue);
        }else if(weights[column].CONNECT3.present){
            weights[column].weight = int(weights[column].CONNECT3.moveValue);
        }else if(weights[column].BLOCK3.present){
            weights[column].weight = int(weights[column].BLOCK3.moveValue);            
        }else if(weights[column].CONNECT2.present){
            weights[column].weight = int(weights[column].CONNECT2.moveValue);            
        }else if(weights[column].BLOCK2.present){
            weights[column].weight = int(weights[column].BLOCK2.moveValue);            
        }

        // Predict Player Move
        // Check possible blocks for one row higher
        
        if(bottomY-1>=0){
            --bottomY;                       
            if(checkBlockWins(column, bottomY)){    // Block Win
                weights[column].weight -= int(weights[column].WIN.moveValue);
            }/*else if(checkBlock3(column, bottomY)){ // Block 3
                weights[column].weight -= int(weights[column].BLOCK3.moveValue);
            }else if(checkBlock2(column, bottomY)){ // Block 2
                weights[column].weight -= int(weights[column].BLOCK2.moveValue);
            }
            */
        }
        
    }
    
    // printf("Column: %i, Weight: %i\n",column+1, int(weights[column].weight));
}

bool Connect4::checkWins(int column, int row){
    /*
    if(column-3>=0){   // Left
        if(board[column-2][row]==Connect4::COMP&&board[column-1][row]==Connect4::COMP){
            weights[column].WIN.present=true;
        }
    }else if(column+3<cols&&board[column+3][row]==Connect4::COMP){     //Right
        if(board[column+2][row]==Connect4::COMP&&board[column+1][row]==Connect4::COMP){
            weights[column].WIN.present=true;
        }
    }else if(row+3<rows&&board[column][row+3]==Connect4::COMP){     //Down
        if(board[column][row+2]==Connect4::COMP&&board[column][row+1]==Connect4::COMP){
            weights[column].WIN.present=true;
        }
    }else if((column-3>=0&&row+3<rows)&&board[column-3][row+3]==Connect4::COMP){     //Down Left
        if(board[column-2][row+2]==Connect4::COMP&&board[column-1][row+1]==Connect4::COMP){
            weights[column].WIN.present=true;
        }
    }else if((column+3<cols&&row+3<rows)&&board[column+3][row+3]==Connect4::COMP){     //Down Right
        if(board[column+2][row+2]==Connect4::COMP&&board[column+1][row+1]==Connect4::COMP){
            weights[column].WIN.present=true;
        }
    }
    */

   bool toReturn = false;
    // Horizontal count
   int countLeft=0;
   int countRight=0;
   while(column-countLeft-1>=0&&board[column-countLeft-1][row]==Connect4::COMP){
       ++countLeft;
   }
   while(column+countRight+1<cols&&board[column+countRight+1][row]==Connect4::COMP){
       ++countRight;
   }
   if(countLeft+countRight>2){
       toReturn=true;
   }

    // Vertical
    if(row+3<rows&&board[column][row+3]==Connect4::COMP){
        if(board[column][row+2]==Connect4::COMP&&board[column][row+1]==Connect4::COMP){
            toReturn=true;
        }
    }

    // Diagonal
    // Down Left
    int dlCount=0;
    while((column-dlCount-1>=0&&row+dlCount+1<rows)&&board[column-dlCount-1][row+dlCount+1]==Connect4::COMP){
       ++dlCount;
    }
    // Down Right
    int drCount=0;
    while((column+drCount+1<cols&&row+drCount+1<rows)&&board[column+drCount+1][row+drCount+1]==Connect4::COMP){
       ++drCount;
    }
    
    // Up Left
    int ulCount=0;
    while((column-ulCount-1>=0&&row-ulCount-1>=0)&&board[column-ulCount-1][row-ulCount-1]==Connect4::COMP){
       ++ulCount;
    }
    // Up Right
    int urCount=0;
    while((column+urCount+1<cols&&row-urCount-1>=0)&&board[column+urCount+1][row-urCount-1]==Connect4::COMP){
       ++urCount;
    }

    if(dlCount+urCount>2||ulCount+drCount>2){
        toReturn=true;
    }

    return toReturn;
}

bool Connect4::checkBlockWins(int column, int row){
    bool toReturn=false;

     // Horizontal count
   int countLeft=0;
   int countRight=0;
   while(column-countLeft-1>=0&&board[column-countLeft-1][row]==Connect4::PLAYER){
       ++countLeft;
   }
   while(column+countRight+1<cols&&board[column+countRight+1][row]==Connect4::PLAYER){
       ++countRight;
   }
   if(countLeft+countRight>2){
        toReturn=true;
   }

    // Vertical
    if(row+3<rows&&board[column][row+3]==Connect4::PLAYER){
        if(board[column][row+2]==Connect4::PLAYER&&board[column][row+1]==Connect4::PLAYER){
             toReturn=true;
        }
    }

    // Diagonal
    // Down Left
    int dlCount=0;
    while(column-dlCount-1>=0&&board[column-dlCount-1][row+dlCount+1]==Connect4::PLAYER){
       ++dlCount;
    }
    // Down Right
    int drCount=0;
    while(column+drCount+1<cols&&board[column+drCount+1][row+drCount+1]==Connect4::PLAYER){
       ++drCount;
    }
    
    // Up Left
    int ulCount=0;
    while((column-ulCount-1>=0&&row-ulCount-1>=0)&&board[column-ulCount-1][row-ulCount-1]==Connect4::PLAYER){
       ++ulCount;
    }

    // Up Right
    int urCount=0;
    while((column+urCount+1<cols&&row-urCount-1>=0)&&board[column+urCount+1][row-urCount-1]==Connect4::PLAYER){
       ++urCount;
    }

    if(dlCount+urCount>2||ulCount+drCount>2){
        toReturn=true;
    }

    return toReturn;
}

bool Connect4::checkConnect3(int column, int row){
    bool toReturn = false;
    // Horizontal count
   int countLeft=0;
   int countRight=0;
   while(column-countLeft-1>=0&&board[column-countLeft-1][row]==Connect4::COMP){
       ++countLeft;
   }
   while(column+countRight+1<cols&&board[column+countRight+1][row]==Connect4::COMP){
       ++countRight;
   }
   if(countLeft+countRight>1){
       toReturn=true;
   }

    // Vertical
    if(row+2<rows&&board[column][row+2]==Connect4::COMP){
        if(board[column][row+1]==Connect4::COMP){
            toReturn=true;
        }
    }

    // Diagonal
    // Down Left
    int dlCount=0;
    while((column-dlCount-1>=0&&row+dlCount+1<rows)&&board[column-dlCount-1][row+dlCount+1]==Connect4::COMP){
       ++dlCount;
    }
    // Down Right
    int drCount=0;
    while((column+drCount+1<cols&&row+drCount+1<rows)&&board[column+drCount+1][row+drCount+1]==Connect4::COMP){
       ++drCount;
    }
    
    // Up Left
    int ulCount=0;
    while((column-ulCount-1>=0&&row-ulCount-1>=0)&&board[column-ulCount-1][row-ulCount-1]==Connect4::COMP){
       ++ulCount;
    }
    // Up Right
    int urCount=0;
    while((column+urCount+1<cols&&row-urCount-1>=0)&&board[column+urCount+1][row-urCount-1]==Connect4::COMP){
       ++urCount;
    }

    if(dlCount+urCount>1||ulCount+drCount>1){
        toReturn=true;
    }

    return toReturn;
}

bool Connect4::checkBlock3(int column, int row){
     bool toReturn=false;

     // Horizontal count
   int countLeft=0;
   int countRight=0;
   while(column-countLeft-1>=0&&board[column-countLeft-1][row]==Connect4::PLAYER){
       ++countLeft;
   }
   while(column+countRight+1<cols&&board[column+countRight+1][row]==Connect4::PLAYER){
       ++countRight;
   }
   if(countLeft+countRight>1){
        toReturn=true;
   }

    // Vertical
    if(row+2<rows&&board[column][row+2]==Connect4::PLAYER){
        if(board[column][row+1]==Connect4::PLAYER){
             toReturn=true;
        }
    }

    // Diagonal
    // Down Left
    int dlCount=0;
    while(column-dlCount-1>=0&&board[column-dlCount-1][row+dlCount+1]==Connect4::PLAYER){
       ++dlCount;
    }
    // Down Right
    int drCount=0;
    while(column+drCount+1<cols&&board[column+drCount+1][row+drCount+1]==Connect4::PLAYER){
       ++drCount;
    }
    
    // Up Left
    int ulCount=0;
    while((column-ulCount-1>=0&&row-ulCount-1>=0)&&board[column-ulCount-1][row-ulCount-1]==Connect4::PLAYER){
       ++ulCount;
    }

    // Up Right
    int urCount=0;
    while((column+urCount+1<cols&&row-urCount-1>=0)&&board[column-urCount+1][row-urCount-1]==Connect4::PLAYER){
       ++urCount;
    }

    if(dlCount+urCount>1||ulCount+drCount>1){
        toReturn=true;
    }

    return toReturn;
}

bool Connect4::checkConnect2(int column, int row){
    bool toReturn=false;
    if(column-1>=0&&board[column-1][row]==Connect4::COMP){ // Left
            toReturn=true;
        }
    if(column+1<cols&&board[column+1][row]==Connect4::COMP){     //Right
        toReturn=true;
    }
    if(row+1<rows&&board[column][row+1]==Connect4::COMP){     //Down
        toReturn=true;
    }
    if((column-1>=0&&row+1<rows)&&board[column-1][row+1]==Connect4::COMP){     //Down Left
        toReturn=true;
    }
    if((column+1<cols&&row+1<rows)&&board[column+1][row+1]==Connect4::COMP){     //Down Right
        toReturn=true;
    }

    return toReturn;
}

bool Connect4::checkBlock2(int column, int row){
    bool toReturn=false;
    bool downPossible = false;
    if(column-1>=0&&board[column-1][row]==Connect4::PLAYER){   // Left
        toReturn=true;            
    }
    if(column+1<cols&&board[column+1][row]==Connect4::PLAYER){     //Right
        toReturn=true;            
    }
    if(row+1<rows){     //Down
        if(board[column][row+1]==Connect4::PLAYER){
            toReturn=true;            
        }
        downPossible=true;
    }
    if(downPossible){
        if((column-1>=0)&&board[column-1][row+1]==Connect4::PLAYER){     //Down Left
            toReturn=true;            
        }
        if((column+1<cols)&&board[column+1][row+1]==Connect4::PLAYER){     //Down Right
            toReturn=true;
        }
    }

    return toReturn;
}

void Connect4::resetAtributes(){
    for(int i=0;i<cols;++i){
       weights[i].WIN.present=false;
       weights[i].BLOCKWIN.present=false;
       weights[i].CONNECT3.present=false;
       weights[i].BLOCK3.present=false;
       weights[i].CONNECT2.present=false;
       weights[i].BLOCK2.present=false;
       weights[i].weight=0;
   }
}

void Connect4::compMove(){

    resetAtributes();
    
    int maxWeight = -1;
    int dropIndex = -1;
    for(int i = 0;i<cols;++i){
        weighColumn(i);
        if(weights[i].weight>maxWeight){
            dropIndex=i;
            maxWeight=weights[i].weight;
        }
    }
    // printf("Weights: 1:%i, 2:%i, 3:%i, 4:%i, 5:%i, 6:%i, 7:%i\n",
    //     weights[0].totalWeight,weights[1].totalWeight,weights[2].totalWeight
    //     ,weights[3].totalWeight,weights[4].totalWeight,weights[5].totalWeight
    //     ,weights[6].totalWeight);
    // printf("ToDrop: %i\n", dropIndex+1);
    dropPiece(dropIndex, Connect4::COMP);
}

bool Connect4::checkWin(){
    if(turnCount>=maxTurns){
        gameOver=true;
    }
    for(int x=0;x<cols&&!gameOver;++x){
        for(int y=0;y<rows&&!gameOver;++y){
            
            // Filled Slot
            if(board[x][y]!=Slot::EMPTY){
                // printf("Location [%i][%i]\n",x+1,y+1);
                Slot piece = board[x][y];   // Get piece type (Player or Comp)
                int count=1;
                // Check Down
                if(y+3<rows){
                    while(count<4&&piece==board[x][y+count]){
                        ++count;
                    }
                    if(count>=4){
                        printf("Count for [%i][%i]: %i\n",x+1,y+1,count);
                        gameOver=true;
                    }else{
                        count=1;
                    }
                }
                
                if(!gameOver&&x+3<cols){
                    while(count<4&&piece==board[x+count][y]){
                        ++count;
                    }
                    if(count>=4){
                        printf("Count for [%i][%i]: %i\n",x+1,y+1,count);
                        gameOver=true;
                    }else{
                        count=1;
                    }
                }
                // Check Diagonal (down) Right
                if(!gameOver&&(x+3<cols&&y+3<rows)){
                    while(count<4&&piece==board[x+count][y+count]){
                        ++count;
                    }
                    if(count>=4){
                        printf("Count for [%i][%i]: %i\n",x+1,y+1,count);
                        gameOver=true;
                    }else{
                        count=1;
                    }
                }
                // Check Diagonal (down) Left
                if(!gameOver&&(x-3>=0&&y+3<rows)){
                    while(count<4&&piece==board[x-count][y+count]){
                        ++count;
                    }
                    if(count>=4){
                        printf("Count for [%i][%i]: %i\n",x+1,y+1,count);
                        gameOver=true;
                    }else{
                        count=1;
                    }
                }
                
            }
        }
    }
    return gameOver;
}

void Connect4::printBoard(){

    cout<<" ";
    for(int i=1;i<=cols;++i){
        printf(" %i",i);
    }
    cout<<endl;
    
    for(int y=0;y<cols;++y){
        cout<<(char)y+1<<'|';
        for(int x=0;x<rows;++x){
            cout << (char)board[x][y] << '|';   // Print row at a time
        }
        cout<<(char)y+1<<endl;
    }

    cout<<" ";
    for(int i=1;i<=cols;++i){
       printf(" %i",i);
    }
    cout<<endl;
}

int main(int argc, char** argv){
    cout<<"Play as Noughts (O) or Crosses (X)?"<<endl;
    char playerPieceIn = '\0';
    Connect4::Slot playerSlot;
    Connect4::Slot compSlot;
    while(playerPieceIn=='\0'){
        cin>>playerPieceIn;
        if(playerPieceIn==(char)Connect4::Slot::CROSS){
            playerSlot=Connect4::Slot::CROSS;
            compSlot=Connect4::Slot::NOUGHT;
        }else if(playerPieceIn==(char)Connect4::Slot::NOUGHT){
            compSlot=Connect4::Slot::CROSS;
            playerSlot=Connect4::Slot::NOUGHT;
        }else{
            cout<<"Try Again... Noughts (O) or Crosses (X)?"<<endl;
            playerPieceIn='\0';
        }
    }

    /*
    bool DEBUG = playerSlot==Connect4::Slot::CROSS;
    cout<<"DEBUG: PlayerIsCrosses: "<< DEBUG <<endl;
    DEBUG = playerSlot==Connect4::Slot::NOUGHT;
    cout<<"DEBUG: PlayerIsNoughts: "<< DEBUG <<endl;
    */

    cout<<"Play first? (Y/N)"<<endl;
    char playerFirstIn;
    bool playerFirst = false;
    cin>>playerFirstIn;
    if(playerFirstIn=='Y'){
        playerFirst = true;
    }

    // cout<<"DEBUG: playerSlot: "<<(char)playerSlot<<", compSlot: "<<(char)compSlot<<", PlayerFirst? "<<playerFirst<<"."<<endl;
    Connect4* game; 
    game = new Connect4(playerSlot, compSlot);
    game->playGame(playerFirst);
    // cout<<"Game over?: "<<game->checkWin()<<endl;
    delete game;
}
