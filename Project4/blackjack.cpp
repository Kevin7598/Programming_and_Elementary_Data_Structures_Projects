#include <iostream>
#include <string>
#include <cstdlib>
#include "player.h"
#include "hand.h"
#include "deck.h"
#include "rand.h"
#include "card.h"

#define MINIMUM 5
#define RESHUFFLE 20
#define NATURAL_COUNT 21

using namespace std;

void shuffle(Deck &deck){
    cout << "Shuffling the deck\n";
    for (int i = 0; i < 7; i++) {
        int cut = get_cut();
        deck.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
}
// Shuffle the card 7 times based on random cuts.

int main(int, char* argv[]){
    unsigned int bankroll = atoi(argv[1]);
    int hand = atoi(argv[2]);
    Player *player;
    if ((string)argv[3] == "simple") player = get_Simple();
    else player = get_Counting();
    Hand player_hand, dealer_hand;
    Deck deck;
    Card dealt{};
    // The initialization of the game, with one player (including his algorithm and hand), one dealer, one deck, as well as an empty card.
    int hand_count = 0;
    for (int thishand = 1; thishand <= hand; thishand++){
        player_hand.discardAll();
        dealer_hand.discardAll();
        if (thishand == 1) {
            shuffle(deck);
        }
        // First shuffle the cards.
        if (bankroll < MINIMUM) {
            hand_count = thishand - 1;
            break;
        }
        // If the player doesn't have enough bankroll, the game will be stopped and the final result will be shown.
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if(deck.cardsLeft() < RESHUFFLE) {
            shuffle(deck);
            player->shuffled();
        }
        // If there are no enough cards, the deck will be reshuffled.
        int wager = player->bet(bankroll, MINIMUM);
        cout << "Player bets " << wager << endl;
        bankroll -= wager;
        // Take the player's bet and take away the wager according to the bet.
        Card first_dealt{}, final_dealt{};
        // Set the two cards that the dealer accepts at the beginning.
        for (int i = 0; i < 4; i++) {
            dealt = deck.deal();
            if ((i == 0) || (i == 2)) {
                player->expose(dealt);
                player_hand.addCard(dealt);
                cout << "Player dealt " << SpotNames[dealt.spot] << " of " << SuitNames[dealt.suit] << endl;
            }
            else{
                dealer_hand.addCard(dealt);
                if (i == 1) {
                    player->expose(dealt);
                    first_dealt = dealt;
                    cout << "Dealer dealt " << SpotNames[dealt.spot] << " of " << SuitNames[dealt.suit] << endl;
                }
                else final_dealt = dealt;
            }
        }
        // The player and the dealer take the cards one by one according to the rule.
        if (player_hand.handValue().count == NATURAL_COUNT) {
            cout << "Player dealt natural 21\n";
            bankroll += (int)(wager * 5 / 2);
        }
        // If the player's hand count is exactly 21, the player will directly win this hand and take the 1.5 times of his wager, in addition to the money he bets.
        else {
            while (player->draw(first_dealt, player_hand)) {
                dealt = deck.deal();
                player->expose(dealt);
                player_hand.addCard(dealt);
                cout << "Player dealt " << SpotNames[dealt.spot] << " of " << SuitNames[dealt.suit] << endl;
            }
            // If the player's hand count is not 21, he will take cards based on his hand count as well as the card the dealer shows.
            int player_count = player_hand.handValue().count;
            cout << "Player's total is " << player_count << endl;
            // Announce the player's total hand count.
            if (player_count <= NATURAL_COUNT) {
                player->expose(final_dealt);
                cout << "Dealer's hole card is " << SpotNames[final_dealt.spot] << " of " << SuitNames[final_dealt.suit] << endl;
                // After the player's turn (if the player doesn't bust), show the dealer's hidden card.
                while (dealer_hand.handValue().count < 17) {
                    dealt = deck.deal();
                    dealer_hand.addCard(dealt);
                    player->expose(dealt);
                    cout << "Dealer dealt " << SpotNames[dealt.spot] << " of " << SuitNames[dealt.suit] << endl;
                }
                // The dealer continuously take cards until his hand count reaches 17.
                int dealer_count = dealer_hand.handValue().count;
                cout << "Dealer's total is " << dealer_count << endl;
                // Announce the dealer's total hand count.
                if (dealer_count > NATURAL_COUNT) {
                    cout << "Dealer busts\n";
                    bankroll += 2 * wager;
                }
                // If the dealer busts, the players wins this hand and the money.
                else {
                    if (dealer_count > player_count) cout << "Dealer wins\n";
                    else if (dealer_count < player_count) {
                        cout << "Player wins\n";
                        bankroll += 2 * wager;
                    }
                    else {
                        cout << "Push\n";
                        bankroll += wager;
                    }
                }
                // Compare the hand counts of the player and the dealer and derive the result.
            }
            else cout << "Player busts\n";
            // The last situation is that when the player busts.
        }
        hand_count++;
        // Record the actual number of hands that the game processes.
    }
    int thishand = hand_count;
    cout << "Player has " << bankroll << " after " << thishand << " hands\n";
}