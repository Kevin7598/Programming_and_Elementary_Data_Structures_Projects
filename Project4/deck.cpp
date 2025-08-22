#include "deck.h"

Deck::Deck() {
    this->reset();
    this->next = 0;
}

void Deck::reset() {
    int count = 0;
    for (int i = 0; i < DeckSize; i++) {
        if (count == 13) count = 0;
        this->deck[i].spot = Spot(count);
        this->deck[i].suit = Suit(i / 13);
        count++;
    }
    this->next = 0;
}
// Initialize the spots and the suits, as well as the number of card to be dealt according to the rules.

void Deck::shuffle(int n) {
    Deck new_deck;
    if (n <= DeckSize / 2) {
        for (int i = 0; i < 2 * n; i++) {
            if (i % 2 == 1) new_deck.deck[i] = this->deck[i / 2];
            else new_deck.deck[i] = this->deck[n + i / 2];
        }
        if (n < DeckSize / 2) {
            for (int i = 2 * n; i < DeckSize; i++)
                new_deck.deck[i] = this->deck[i];
        }
    }
    else {
        for (int i = 0; i < 2 * (DeckSize - n); i++) {
            if (i % 2 == 1) new_deck.deck[i] = this->deck[i / 2];
            else new_deck.deck[i] = this->deck[n + i / 2];
        }
        for (int i = 2 * (DeckSize - n); i < DeckSize; i++)
            new_deck.deck[i] = this->deck[i - (DeckSize - n)];
    }
    for (int i = 0; i < DeckSize; i++){
        this->deck[i] = new_deck.deck[i];
    }
    this->next = 0;
}
// Shuffle the deck according to the cut. Each time take one card from either sides cut and one by one.
// When the cards at one side are used up, fill the deck with the cards at the other side.

Card Deck::deal() {
    this->next++;
    return this->deck[this->next - 1];
}

int Deck::cardsLeft() {
    return 52 - this->next;
}