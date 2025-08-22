#include "player.h"

class Player_simple : public Player {
public:
    int bet(unsigned int bankroll, unsigned int minimum) override {
        return (int)minimum;
    }
    bool draw(Card dealer, const Hand &player) override {
        if (!player.handValue().soft) {
            if (player.handValue().count <= 11) return true;
            else if (player.handValue().count == 12){
                if ((dealer.spot >= FOUR) && (dealer.spot <= SIX)) return false;
                else return true;
            }
            else if ((player.handValue().count >= 13) && (player.handValue().count <= 16)){
                if ((dealer.spot >= TWO) && (dealer.spot <= SIX)) return false;
                else return true;
            }
            else return false;
        }
        else {
            if (player.handValue().count <= 17) return true;
            else if (player.handValue().count == 18){
                if ((dealer.spot == TWO) || (dealer.spot == SEVEN) || (dealer.spot == EIGHT)) return false;
                else return true;
            }
            else return false;
        }
        // The draw is based on whether the hand is soft and the rules provided.
    }
    void expose(Card c)override{};
    void shuffled()override{};
};

class Player_counting : public Player_simple{
    int count;
    // Count is initialized to simulate the process of counting of the counting player based on the rules.
public:
    Player_counting(): count(0){};
    int bet(unsigned int bankroll, unsigned int minimum) override {
        if ((bankroll >= 2 * minimum) && (this->count >= 2)) return (int) (2 * minimum);
        else return (int) minimum;
    }
    void expose(Card c) override {
        if ((c.spot >= TWO) && (c.spot <= SIX)) this->count++;
        else if ((c.spot >= TEN) && (c.spot <= ACE)) this->count--;
    }
    void shuffled() override { this->count = 0;};
};

Player *get_Simple(){
    static Player_simple simple_player;
    return &simple_player;
}

Player *get_Counting(){
    static Player_counting counting_player;
    return &counting_player;
}