#include "Blackjack.h"
using std::cout;
using std::endl;
using std::cin;

int main(){
    
    Blackjack myGame = Blackjack();
    
    myGame.playRound();
    
}



Blackjack::Blackjack(){
    
    deck = new Deck(true);
    playerHand = new std::vector<Card*>();
    dealerHand = new std::vector<Card*>();

    // Optional
    playerHand->reserve(4);
    dealerHand->reserve(4);
}

Blackjack::~Blackjack(){
    delete deck;
    delete playerHand;
    delete dealerHand;
}

void Blackjack::playRound(){
    std::string input="";
    
    deal(playerHand, 2);
    
    deal(dealerHand, 2);

    // Player turn

    bool roundIsOver = false;
    bool turnIsOver = false;
    while(!roundIsOver&&!turnIsOver){
        cout<<"Your hand: "<<sumHand(playerHand)<<endl;
        cout<<strHand(playerHand)<<endl;
        
        roundIsOver = roundOver(playerHand);
        
        if(!roundIsOver){
            cout<<"H: Hit | S: Stand: ";
            cin>>input;
            while(input!="H"&&input!="S"){
                cin.clear();
                cin.ignore(99999);
                cout<<"H: Hit | S: Stand: ";
                cin>>input;
            }
            turnIsOver = input=="S";

            if(!turnIsOver){   // If not standing, hitting
                deal(playerHand, 1);
            }
        }
        if(roundIsOver){
            deck->resetDeck();
        }
    }

    // Dealer turn
    if(!roundIsOver){
        
        while(sumHand(dealerHand)<MIN_STAND_VAL&&sumHand(dealerHand)<21){
            deal(dealerHand,1);
        }
    }
    cout<<endl<<"Dealers Hand: "<<sumHand(dealerHand)<<endl;
    cout<<strHand(dealerHand)<<endl;

    // Game outcome
    int playerSum = sumHand(playerHand);
    int dealerSum = sumHand(dealerHand);
    if(playerSum>21){
        cout<<"Dealer Wins"<<endl;
    }else if(dealerSum>21){
        cout<<"Player Wins!"<<endl;
    }else if(dealerSum>=playerSum){
        cout<<"Dealer Wins"<<endl;
    }else{
        cout<<"Player Wins!"<<endl;
    }

}

void Blackjack::deal(std::vector<Card*>* toDeal, int count){
    
    for(int i=0;i<count;++i){
        
        Card* toAdd = deck->getCard();
        
        toDeal->push_back(toAdd);
    }
}

int Blackjack::sumHand(std::vector<Card*>* toSum){
    int sum = 0;
    for(Card* card : *toSum){
        if(card->getValue()>10){
            if(card->getFace()==Card::Ace){
                if(sum+11>21){
                    sum+=1; // Ace becomes +1 if +11 would be over 21
                }else{
                sum+=11;
                }
            }else{
                sum+=10;
            }
        }else{
            sum+=card->getValue();
        }
    }
    return sum;
}

std::string Blackjack::strHand(std::vector<Card*>* toPrint){
    std::string toReturn = "";
    toReturn+='\n';
    for(unsigned int i=0;i<toPrint->size();++i){    // Evil bool to int conversion
        Card* card = toPrint->at(i);
        toReturn+= card->toString();
        toReturn+='\n';        
    }
    return toReturn;
}

bool Blackjack::roundOver(std::vector<Card*>* toInterpret){
    int handVal = sumHand(toInterpret);
    bool roundOver = false;
    if(handVal>21){
        cout<<"Bust"<<endl;
        roundOver=true;
    }else if(handVal==21){
        cout<<"BLACKJACK!"<<endl;
        roundOver=true;
    }

    return roundOver;
}