#ifndef Deck_H
#define Deck_H

#include "Card.h"
#include <deque>

class Deck{
public:
    Deck();
    ~Deck();
    Card* getCard();
    void shuffle();
    void addCard(Card* toAdd);
    void resetDeck();
private:
    std::deque<Card*>* playDeck;
    std::deque<Card*>* playedDeck;  // Played cards for deletion
};

#endif