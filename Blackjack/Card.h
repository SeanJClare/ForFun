#ifndef Card_H
#define Card_H


#include <string>

class Card{
    public:
    enum suit : char{   // Index indicates hierachy value
        Clubs = 'C',
        Diamonds = 'D',
        Hearts = 'H',
        Spades = 'S'
    };
    enum face : char{   // for when value > 10
        Jack = 'J', 
        Queen = 'Q',
        King = 'K',
        Ace = 'A'
    };

    Card(int value, suit suit){
        if(value>10){   
            switch(value){  // Dynamic assignment impossible (i.e face(value-11))
                case 11: 
                    cardFace = Jack;
                    break;
                case 12: 
                    cardFace = Queen;
                    break;
                case 13: 
                    cardFace = King;
                    break;
                case 14: 
                    cardFace = Ace;
                    break;
            }
        }
        cardValue = value;  // Included in face cards for comparison reasons
        cardSuit = suit;
    }

    int getValue(){
        return cardValue;
    }

    face getFace(){
        return cardFace;
    }

    suit getSuit(){
        return cardSuit;
    }

    std::string toString(){
        std::string toReturn = "";
        if(cardValue>10){
            switch(cardFace){
                case Jack: 
                    toReturn="Jack";
                    break;
                case Queen :
                    toReturn="Queen";
                    break;
                case King :
                    toReturn="King";
                    break;
                case Ace :
                    toReturn="Ace";
                    break;
            }            
        }else{
            toReturn = std::to_string(cardValue);            
        }
        toReturn += " of ";
        switch(cardSuit){
            case Spades :
                toReturn+="Spades";
                break;
            case Hearts :
                toReturn+="Hearts";
                break;
            case Diamonds :
                toReturn+="Diamonds";
                break;
            case Clubs :
                toReturn+="Clubs";
                break;
        }
        return toReturn;
    }

    // Card can only be equal if suit is not compared

    // Compare card value
    inline bool operator<=(Card& other) {
        if(other.getValue()>=cardValue){
            return true;
        }else {
            return false;
        }
    }

    inline bool operator>=(Card& other) {
        if(other.getValue()<=cardValue){
            return true;
        }else {
            return false;
        }
    }

    // Compare card Value 
    inline bool operator==(Card& other) {
            if(other.getValue()==cardValue){
                return true;
            }else{
                return false;
            }
        }

    inline bool operator!=(Card& other) {
        return !operator==(other);
    }

    // Compare value & suit (if equal)
    inline bool operator<(Card& other) {
        if(other.getValue()>cardValue){
            return true;
        }else if(operator==(other)){
            return other.getSuit()>cardSuit;
        }else{
            return false;
        }
    }

    inline bool operator>(Card& other) {
        return !operator<(other);
    }
    
    private:
    suit cardSuit;
    int cardValue;
    face cardFace;

};
#endif