#include "hand.h"

Hand::Hand() { this->discardAll();}

void Hand::discardAll() {
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card c) {
    if ((c.spot >= TWO) && (c.spot <= TEN)) this->curValue.count += c.spot + 2;
    // When the spot of the card is between 2 and 10, directly take the number on the card.
    else if (c.spot == ACE) {
        if (this->curValue.soft) this->curValue.count++;
        // When the hand is already a soft hand, the ACE card can only be counted as 1.
        else {
                this->curValue.count += 11;
                this->curValue.soft = true;
            // When the hand is a hard hand and the incoming card is an ACE card, first count it as 11 and turn the hand into a soft hand.
        }
    }
    else this->curValue.count += 10;
    // When the card is Jack, Queen, or King, the card is counted as 10.
    if ((this->curValue.soft) && (this->curValue.count > 21)) {
        this->curValue.count -= 10;
        this->curValue.soft = false;
    }
    // When the hand is already a soft hand but there is no space for the newly added card (of course it can be an ACE),
    // the soft count needs to be canceled to provide space for the newly added card to avoid busting.
}

HandValue Hand::handValue() const {
    return this->curValue;
}