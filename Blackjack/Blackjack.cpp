#include "Blackjack.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main(){
    
    Blackjack myGame = Blackjack();
    
    myGame.playRound();
    
}



Blackjack::Blackjack(){
    
    deck = new Deck();
    playerHand = new std::vector<Card*>();
    dealerHand = new std::vector<Card*>();

    // Optional
    playerHand->reserve(4);
    dealerHand->reserve(4);

    // Be sure to shuffle!
    deck->shuffle();
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
        int guessValue = 0;
        if(dealerHand->at(0)->getFace()==Card::Ace){
                guessValue=11;
            }else if(dealerHand->at(0)->getValue()>10){ 
                guessValue=10;
            }else{
                guessValue=dealerHand->at(0)->getValue();
            }
        cout<<endl<<"Dealers Hand: "<<"MAX: "<<(guessValue+11)<<endl; // No total to give away hidden card
        cout<<strHand(dealerHand)<<endl;
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
        int dealSum = sumHand(dealerHand); 
        int playHand = sumHand(playerHand);
        while(dealSum<playHand&&dealSum<21){
            deal(dealerHand,1);
            dealSum = sumHand(dealerHand);
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
    for(int i=toSum->size()-1;i>=0;--i){
        if(toSum->at(i)->getValue()>10){
            if(toSum->at(i)->getFace()==Card::Ace){
                sum+=11;
            }else{
                sum+=10;
            }
        }else{
            sum+=toSum->at(i)->getValue();
        }
    }
    //Acount for Aces if over
    if(sum>21){
        for(Card* card : *toSum){
            if(card->getFace()==Card::Ace && sum>21){
                sum-=10;    // was 11, becomes 1
            }
        }
    }
    return sum;
}

std::string Blackjack::strHand(std::vector<Card*>* toPrint){
    std::string toReturn = "";
    toReturn+='\n';
    for(unsigned int i=0;i<toPrint->size();++i){
        if(hideDealerSecondCard&&toPrint==dealerHand&&i==1){
            hideDealerSecondCard=false;
            toReturn+="Hidden Card";
            toReturn+='\n';
            return toReturn;
        }
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