#include "simulation.h"
using namespace std;

string get_first_two(string name){
    string output;
    for (int pos = 0; pos < 2; pos++){
        output.push_back(name[pos]);
    }
    return output;
}

void printGrid(const world_t& game){
    for (unsigned int row = 0; row < game.grid.height; row++){
        for (unsigned int column = 0; column < game.grid.width; column++){
            if (game.grid.squares[row][column] == nullptr) cout << "____ ";
            else cout << get_first_two(game.grid.squares[row][column]->species->name) << "_"
                          << directShortName[game.grid.squares[row][column]->direction] << " ";
        }
        cout << endl;
    }
}