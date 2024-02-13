#ifndef Blackjack_h
#define Blackjack_h

#include "Deck.h"
#include <vector>

class Blackjack{

public:
     
    Blackjack();
    ~Blackjack();
    void playRound();

    std::string strHand(std::vector<Card*>* toPrint);
    

private:
    const int MIN_STAND_VAL = 16;   // Value for dealer to reach before sitting
    int sumHand(std::vector<Card*>* toSum);
    void deal(std::vector<Card*>* toDeal, int count);
    bool roundOver(std::vector<Card*>* toInterpret); // Bust, Blackjack etc..

    Deck* deck;
    std::vector<Card*>* playerHand;
    std::vector<Card*>* dealerHand;
};

#endif