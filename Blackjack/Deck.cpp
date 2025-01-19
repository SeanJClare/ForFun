#include "Deck.h"

#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>

Deck::Deck(){
    playDeck = new std::deque<Card*>();
    playedDeck = new std::deque<Card*>();

    // Ideally iterate over enum, but difficult with specified values
    Card::suit suit = Card::Spades;
    for(int value=2;value<=14;++value){
        playDeck->push_back(new Card(value, suit));
    }
    suit = Card::Hearts;
    for(int value=2;value<=14;++value){
        playDeck->push_back(new Card(value, suit));
    }
    suit = Card::Diamonds;
    for(int value=2;value<=14;++value){
        playDeck->push_back(new Card(value, suit));
    }
    suit = Card::Clubs;
    for(int value=2;value<=14;++value){
        playDeck->push_back(new Card(value, suit));
    }
}

Card* Deck::getCard(){
    Card* toGet;
    if(playDeck->empty()){
        toGet = nullptr;
    }else{
        toGet = playDeck->front();
        playDeck->pop_front();
        playedDeck->push_front(toGet);
    }
    return toGet;
}

void Deck::addCard(Card* toAdd){
    playDeck->push_back(toAdd);
}

void Deck::shuffle(){
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(playDeck->begin(), playDeck->end(), std::default_random_engine(seed));
    // thank god for C++ library!
}

void Deck::resetDeck(){
    // Move all played cards back to player deck
    Card* playedCard;
    while(!playedDeck->empty()){
        playedCard = playedDeck->front();
        playDeck->push_back(playedCard);
        playedDeck->pop_front();
    }


}

Deck::~Deck(){
    delete playDeck;
    delete playedDeck;
}


// Test Deck
int main(){
    Deck* myDeck = new Deck();

    // myDeck->shuffle();

    Card* myCard;
    Card* myOtherCard;

    /*
    // Print deck
    
        for(myCard=myDeck->getCard();myCard!=nullptr;myCard=myDeck->getCard()){
        std::cout<<myCard->toString()<<std::endl;
    }
    */

    /*
    // <= Comparison value test
    for(myCard=myDeck->getCard(),myOtherCard=myDeck->getCard();
    myCard!=nullptr;
    myCard=myDeck->getCard(),myOtherCard=myDeck->getCard()){
        std::cout<<myCard->toString()<<" < ";
        std::cout<<myOtherCard->toString()<<"? ";
        std::cout<<myCard->operator<=(*myOtherCard)<<std::endl;
    }
    */

   
    // < Comparison Test (suit)
    for(myCard=myDeck->getCard(),myOtherCard=myDeck->getCard();
    myCard!=nullptr;
    myCard=myDeck->getCard(),myOtherCard=myDeck->getCard()){
        std::cout<<myCard->toString()<<" < ";
        std::cout<<myOtherCard->toString()<<"? ";
        std::cout<<myCard->operator<(*myOtherCard)<<std::endl;
    }
    
    delete myDeck;
}