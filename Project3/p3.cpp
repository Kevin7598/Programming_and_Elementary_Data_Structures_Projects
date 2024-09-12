#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "world_type.h"
#include "simulation.h"
using namespace std;

string get_first(const string& instruct){
    string reached;
    for (char i : instruct){
        if ((i != ' ') && (i != '\n')) reached.push_back(i);
        else break;
    }
    return reached;
}
// In many cases the first string of a line needs to be derived so that the
// operation in the instruction as well as the creature name in the world file
// can be known.

string get_second(const string& instruct){
    string reached;
    int count = 0;
    for (unsigned int i = 0; i < instruct.size(); i++){
        if (instruct[i] == ' ') {
            i++;
            count++;
        }
        if (count == 1) {
            if ((instruct[i] != ' ') && (instruct[i] != '\n')) reached.push_back(instruct[i]);
            else break;
        }
    }
    return reached;
}
// In many cases the second string of a line needs to be derived so that the
// address of the operations in the instruction as well as the creature
// direction in the world file can be known.

string get_third(const string& instruct){
    string reached;
    int count = 0;
    for (unsigned int i = 0; i < instruct.size(); i++){
        if (instruct[i] == ' ') {
            i++;
            count++;
        }
        if (count == 2) {
            if ((instruct[i] != ' ') && (instruct[i] != '\n')) reached.push_back(instruct[i]);
            else break;
        }
    }
    return reached;
}
// The third string of a line needs to be derived to get the row number of the
// creature in the world file.

string get_fourth(const string& instruct){
    string reached;
    int count = 0;
    for (unsigned int i = 0; i < instruct.size(); i++){
        if (instruct[i] == ' ') {
            i++;
            count++;
        }
        if (count == 3) {
            if ((instruct[i] != ' ') && (instruct[i] != '\n')) reached.push_back(instruct[i]);
            else break;
        }
    }
    return reached;
}
// The fourth string of a line needs to be derived to get the column number of
// the creature in the world file.

bool have_second(const string& instruct){
    int count = 0;
    for (unsigned int i = 1; i < instruct.size(); i++) {
        if ((instruct[i] == ' ') && (instruct[i - 1] != ' ')) count++;
        if (((instruct[i] == ' ') && (instruct[i - 1] == ' ')) || ((instruct[i] == ' ') && (instruct[i - 1] >= '1')
        && (instruct[i - 1] <= '9'))) break;
    }
    if ((instruct[instruct.size() - 1] >= '0') && (instruct[instruct.size() - 1] <= '9')) {
        unsigned int pos = instruct.size() - 1;
        while ((instruct[pos] >= '0') && (instruct[pos] <= '9')) pos--;
        if (instruct[pos] == ' ') count++;
    }
    if (count == 2) return true;
    else return false;
}
// After trying to derive the address of some operations, it needs to be
// determined in advance whether there is a second string of the address to
// avoid runtime error.

int main(int argc, char* argv[]) {
    world_t game;
    string file1 = argv[1];
    string file2 = argv[2];
    string name[100];
    string test;
    string get_name;
    int round = atoi(argv[3]);
    bool more;
    if (argc == 5){
        string additional = argv[4];
        if ((additional == "v") ||(additional == "verbose")) more = true;
        else more = false;
    } else more = false;
    int line = 0;
    string instruction[100][100] = {{"0"}};
    vector<int> instruction_line;
    vector<int> instruction_real_line;
    ifstream species(file1);
    ifstream world(file2);
    // This part is mainly the initialization of variables in the game.

    if (argc < 4) {
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
        return 0;
    }
    if (round < 0) {
        cout << "Error: Number of simulation rounds is negative!" << endl;
        return 0;
    }
    if (!world.is_open()) {
        cout << "Error: Cannot open file " << file2 << "!" << endl;
        return 0;
    }
    while (getline(species, name[line])) line++;
    get_name = name[0];
    for (int i = 0; i < line - 1; i++) name[i] = name[i + 1];
    line--;
    for (int i = 0; i < line; i++) game.species[i].name = name[i];
    game.numSpecies = line;
    if (game.numSpecies > MAXSPECIES) {
        cout << "Error: Too many species!" << endl;
        cout << "Maximal number of species is " << MAXSPECIES << "." << endl;
        return 0;
    }
    for (int i = 0; i < line; i++) {
        ifstream new_file( get_name + "/" + name[i]);
        instruction_line.push_back(0);
        instruction_real_line.push_back(0);
        bool state = true;
        if (!new_file.is_open()){
            cout << "Error: Cannot open file " << get_name << "/" << name[i] << "!" << endl;
            return 0;
        }
        while (getline(new_file, instruction[i][instruction_line[i]])) {
            if (instruction[i][instruction_line[i]].empty()) state = false;
            if (state) {
                if (get_first(instruction[i][instruction_line[i]]) == "hop")
                    game.species[i].program[instruction_line[i]].op = HOP;
                else if (get_first(instruction[i][instruction_line[i]]) == "left")
                    game.species[i].program[instruction_line[i]].op = LEFT;
                else if (get_first(instruction[i][instruction_line[i]]) == "right")
                    game.species[i].program[instruction_line[i]].op = RIGHT;
                else if (get_first(instruction[i][instruction_line[i]]) == "infect")
                    game.species[i].program[instruction_line[i]].op = INFECT;
                else if (get_first(instruction[i][instruction_line[i]]) == "ifempty")
                    game.species[i].program[instruction_line[i]].op = IFEMPTY;
                else if (get_first(instruction[i][instruction_line[i]]) == "ifenemy")
                    game.species[i].program[instruction_line[i]].op = IFENEMY;
                else if (get_first(instruction[i][instruction_line[i]]) == "ifsame")
                    game.species[i].program[instruction_line[i]].op = IFSAME;
                else if (get_first(instruction[i][instruction_line[i]]) == "ifwall")
                    game.species[i].program[instruction_line[i]].op = IFWALL;
                else if (get_first(instruction[i][instruction_line[i]]) == "go")
                    game.species[i].program[instruction_line[i]].op = GO;
                else{
                    cout << "Error: Instruction " << get_first(instruction[i][instruction_line[i]])
                         << " is not recognized!" << endl;
                    return 0;
                }
                if (have_second(instruction[i][instruction_line[i]])) {
                    game.species[i].program[instruction_line[i]].address =
                            stoi(get_second(instruction[i][instruction_line[i]]));
                }
                instruction_real_line[i]++;
            }
            instruction_line[i]++;
        }
        game.species[i].programSize = instruction_real_line[i];
        if (game.species[i].programSize > MAXPROGRAM){
            cout << "Error: Too many instructions for species " << name[i] << "!" << endl;
            cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
            return 0;
        }
    }
    int count_world_line = 0;
    string world_command[100] = {"0"};
    while (getline(world, world_command[count_world_line])) count_world_line++;
    game.numCreatures = count_world_line - 2;
    if (game.numCreatures > MAXCREATURES){
        cout << "Error: Too many creatures!" << endl;
        cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
        return 0;
    }
    if (((unsigned)stoi(world_command[0]) >= 1) && ((unsigned)stoi(world_command[0]) <= MAXHEIGHT))
        game.grid.height = stoi(world_command[0]);
    else {
        cout << "Error: The grid height is illegal!" << endl;
        return 0;
    }
    if (((unsigned)stoi(world_command[1]) >= 1) && ((unsigned)stoi(world_command[1]) <= MAXHEIGHT))
        game.grid.width = stoi(world_command[1]);
    else {
        cout << "Error: The grid width is illegal!" << endl;
        return 0;
    }
    for (int i = 0; i < count_world_line - 2; i++) world_command[i] = world_command[i + 2];
    for (unsigned int pos = 0; pos < game.numCreatures; pos++){
        bool state = false;
        for (unsigned int i = 0; i < game.numSpecies; i++){
            if (get_first(world_command[pos]) == game.species[i].name){
                game.creatures[pos].species = &game.species[i];
                state = true;
                break;
            }
        }
        if (!state) {
            cout << "Error: Species " << get_first(world_command[pos]) << " not found!" << endl;
            return 0;
        }
        if (get_second(world_command[pos]) == "east") game.creatures[pos].direction = EAST;
        else if (get_second(world_command[pos]) == "west") game.creatures[pos].direction = WEST;
        else if (get_second(world_command[pos]) == "south") game.creatures[pos].direction = SOUTH;
        else if (get_second(world_command[pos]) == "north") game.creatures[pos].direction = NORTH;
        else{
            cout << "Error: Direction " << get_second(world_command[pos]) << " is not recognized!" << endl;
            return 0;
        }
        game.creatures[pos].programID = 0;
        game.creatures[pos].location.r = stoi(get_third(world_command[pos]));
        game.creatures[pos].location.c = stoi(get_fourth(world_command[pos]));
        if ((game.creatures[pos].location.r < 0) || ((unsigned)game.creatures[pos].location.r >= game.grid.height)
        || (game.creatures[pos].location.c < 0) || ((unsigned)game.creatures[pos].location.c >= game.grid.width)){
            cout << "Error: Creature (" << game.creatures[pos].species->name << " ";
            if (game.creatures[pos].direction == 0) cout << "east";
            if (game.creatures[pos].direction == 1) cout << "south";
            if (game.creatures[pos].direction == 2) cout << "west";
            if (game.creatures[pos].direction == 3) cout << "north";
            cout << " " << game.creatures[pos].location.r << " " << game.creatures[pos].location.c << ")"
            << " is out of bound!" << endl;
            cout << "The grid size is " << game.grid.height << "-by-" << game.grid.width << "." << endl;
            return 0;
        }
        for (unsigned int i = 0; i < pos; i++){
            if ((game.creatures[pos].location.r == game.creatures[i].location.r) &&
            (game.creatures[pos].location.c == game.creatures[i].location.c)){
                cout << "Error: Creature (" << game.creatures[pos].species->name << " "
                << get_second(world_command[pos])
                << " " << game.creatures[pos].location.r << " " << game.creatures[pos].location.c
                << ") overlaps with creature (" << game.creatures[i].species->name << " "
                << get_second(world_command[i]) << " " << game.creatures[i].location.r << " "
                << game.creatures[i].location.c << ")!" << endl;
                return 0;
            }
        }
        game.grid.squares[game.creatures[pos].location.r][game.creatures[pos].location.c] = &game.creatures[pos];
    }
    // This part above is the initialization of the values of variables in the
    // game as well as printing error messages. For each subpart in the part,
    // the legality of the contents read from the file will be checked. If they
    // are not illegal, they will be stored in the struct game as the
    // initialization of the game.

    for (int round_count = 1; round_count <= round; round_count++){
        if (round_count == 1)
        {
            cout << "Initial state" << endl;
            printGrid(game);
        }
        cout << "Round " << round_count << endl;
        for (unsigned int creature_count = 0; creature_count < game.numCreatures; creature_count++){
            cout << "Creature (" << game.creatures[creature_count].species->name << " ";
            if (game.creatures[creature_count].direction == EAST) cout << "east ";
            if (game.creatures[creature_count].direction == WEST) cout << "west ";
            if (game.creatures[creature_count].direction == SOUTH) cout << "south ";
            if (game.creatures[creature_count].direction == NORTH) cout << "north ";
            cout << game.creatures[creature_count].location.r << " " << game.creatures[creature_count].location.c
            << ") takes action:";
            if (more) cout << endl;
            while (true) {
                if (more) cout << "Instruction " << game.creatures[creature_count].programID + 1 << ": ";
                int operation
                = game.creatures[creature_count].species->program[game.creatures[creature_count].programID].op;
                int direct = game.creatures[creature_count].direction;
                unsigned int location_r = game.creatures[creature_count].location.r;
                unsigned int location_c = game.creatures[creature_count].location.c;
                string creature_name = game.creatures[creature_count].species->name;
                unsigned int creature_size = game.creatures[creature_count].species->programSize;
                if (operation == HOP){
                    if (direct == EAST){
                        if (!game.grid.squares[location_r][location_c + 1] && (location_c + 1 < game.grid.width)) {
                            game.grid.squares[game.creatures[creature_count].location.r]
                            [game.creatures[creature_count].location.c] = nullptr;
                            game.creatures[creature_count].location.c++;
                            game.grid.squares[game.creatures[creature_count].location.r]
                            [game.creatures[creature_count].location.c]
                                    = &game.creatures[creature_count];
                        }
                    }
                    if (direct == WEST){
                        if (location_c != 0) {
                            if (!game.grid.squares[location_r][location_c - 1]) {
                                game.grid.squares[game.creatures[creature_count].location.r]
                                [game.creatures[creature_count].location.c] = nullptr;
                                game.creatures[creature_count].location.c--;
                                game.grid.squares[game.creatures[creature_count].location.r]
                                [game.creatures[creature_count].location.c]
                                        = &game.creatures[creature_count];
                            }
                        }
                    }
                    if (direct == SOUTH){
                        if (!game.grid.squares[location_r + 1][location_c] && (location_r + 1 < game.grid.height)) {
                            game.grid.squares[game.creatures[creature_count].location.r]
                            [game.creatures[creature_count].location.c] = nullptr;
                            game.creatures[creature_count].location.r++;
                            game.grid.squares[game.creatures[creature_count].location.r]
                            [game.creatures[creature_count].location.c]
                                    = &game.creatures[creature_count];
                        }
                    }
                    if (direct == NORTH){
                        if (location_r != 0) {
                            if (!game.grid.squares[location_r - 1][location_c]) {
                                game.grid.squares[game.creatures[creature_count].location.r]
                                [game.creatures[creature_count].location.c] = nullptr;
                                game.creatures[creature_count].location.r--;
                                game.grid.squares[game.creatures[creature_count].location.r]
                                [game.creatures[creature_count].location.c]
                                        = &game.creatures[creature_count];
                            }
                        }
                    }
                    game.creatures[creature_count].programID++;
                    cout << " hop" << endl;
                    if (more) printGrid(game);
                    break;
                }
                if (operation == LEFT){
                    if (direct == EAST) game.creatures[creature_count].direction = NORTH;
                    if (direct == WEST) game.creatures[creature_count].direction = SOUTH;
                    if (direct == NORTH) game.creatures[creature_count].direction = WEST;
                    if (direct == SOUTH) game.creatures[creature_count].direction = EAST;
                    game.creatures[creature_count].programID++;
                    cout << " left" << endl;
                    if (more) printGrid(game);
                    break;
                }
                if (operation == RIGHT){
                    if (direct == EAST) game.creatures[creature_count].direction = SOUTH;
                    if (direct == WEST) game.creatures[creature_count].direction = NORTH;
                    if (direct == NORTH) game.creatures[creature_count].direction = EAST;
                    if (direct == SOUTH) game.creatures[creature_count].direction = WEST;
                    game.creatures[creature_count].programID++;
                    cout << " right" << endl;
                    if (more) printGrid(game);
                    break;
                }
                if (operation == INFECT){
                    if (direct == EAST) {
                        if (game.grid.squares[location_r][location_c + 1] && (location_c + 1 < game.grid.width)) {
                            if (creature_name != game.grid.squares[location_r][location_c + 1]->species->name) {
                                game.grid.squares[location_r][location_c + 1]->species->name = creature_name;
                                game.grid.squares[location_r][location_c + 1]->species->programSize = creature_size;
                                for (unsigned int program_count = 0;
                                     program_count < game.creatures[creature_count].species->programSize;
                                     program_count++) {
                                     game.grid.squares[location_r][location_c + 1]->species->program[program_count] =
                                            game.creatures[creature_count].species->program[program_count];
                                }
                                game.grid.squares[location_r][location_c + 1]->programID = 0;
                            }
                        }
                    }
                    if (direct == WEST){
                        if (location_c != 0) {
                            if (game.grid.squares[location_r][location_c - 1]) {
                                if (creature_name != game.grid.squares[location_r][location_c - 1]->species->name) {
                                    game.grid.squares[location_r][location_c - 1]->species->name = creature_name;
                                    game.grid.squares[location_r][location_c - 1]->species->programSize = creature_size;
                                    for (unsigned int program_count = 0;
                                         program_count < game.creatures[creature_count].species->programSize;
                                         program_count++) {
                                         game.grid.squares[location_r][location_c - 1]->species->program[program_count]
                                         = game.creatures[creature_count].species->program[program_count];
                                    }
                                    game.grid.squares[location_r][location_c - 1]->programID = 0;
                                }
                            }
                        }
                    }
                    if (direct == SOUTH){
                        if (game.grid.squares[location_r + 1][location_c] && (location_r + 1 < game.grid.height)){
                            if (creature_name != game.grid.squares[location_r + 1][location_c]->species->name){
                                game.grid.squares[location_r + 1][location_c]->species->name = creature_name;
                                game.grid.squares[location_r + 1][location_c]->species->programSize = creature_size;
                                for (unsigned int program_count = 0;
                                     program_count < game.creatures[creature_count].species->programSize;
                                     program_count++) {
                                    game.grid.squares[location_r + 1][location_c]->species->program[program_count] =
                                            game.creatures[creature_count].species->program[program_count];
                                }
                                game.grid.squares[location_r + 1][location_c]->programID = 0;
                            }
                        }
                    }
                    if (direct == NORTH){
                        if (location_r != 0) {
                            if (game.grid.squares[location_r - 1][location_c]) {
                                if (creature_name != game.grid.squares[location_r - 1][location_c]->species->name) {
                                    game.grid.squares[location_r - 1][location_c]->species->name = creature_name;
                                    game.grid.squares[location_r - 1][location_c]->species->programSize = creature_size;
                                    for (unsigned int program_count = 0;
                                         program_count < game.creatures[creature_count].species->programSize;
                                         program_count++) {
                                        game.grid.squares[location_r - 1][location_c]->species->program[program_count] =
                                                game.creatures[creature_count].species->program[program_count];
                                    }
                                    game.grid.squares[location_r - 1][location_c]->programID = 0;
                                }
                            }
                        }
                    }
                    game.creatures[creature_count].programID++;
                    cout << " infect" << endl;
                    if (more) printGrid(game);
                    break;
                }
                if (operation == IFEMPTY){
                    unsigned int num = game.creatures[creature_count].species->program
                    [game.creatures[creature_count].programID].address;
                    if (direct == EAST){
                        if (!game.grid.squares[location_r][location_c + 1] && (location_c + 1 < game.grid.width)){
                                game.creatures[creature_count].programID = num - 1;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == WEST){
                        if (location_c != 0) {
                            if (!game.grid.squares[location_r][location_c - 1]) {
                                game.creatures[creature_count].programID = num - 1;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == SOUTH){
                        if (!game.grid.squares[location_r + 1][location_c] && (location_r + 1 < game.grid.height)){
                            game.creatures[creature_count].programID = num - 1;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == NORTH){
                        if (location_r != 0) {
                            if (!game.grid.squares[location_r - 1][location_c]) {
                                game.creatures[creature_count].programID = num - 1;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (more) cout << " ifempty " << num << endl;
                }
                if (operation == IFENEMY){
                    unsigned int num = game.creatures[creature_count].species->program
                                    [game.creatures[creature_count].programID].address;
                    if (direct == EAST){
                        if (game.grid.squares[location_r][location_c + 1] && (location_c + 1 < game.grid.width)){
                            if (creature_name != game.grid.squares[location_r][location_c + 1]->species->name){
                                game.creatures[creature_count].programID = num - 1;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == WEST){
                        if (location_c != 0) {
                            if (game.grid.squares[location_r][location_c - 1]) {
                                if (creature_name != game.grid.squares[location_r][location_c - 1]->species->name) {
                                    game.creatures[creature_count].programID = num - 1;
                                } else game.creatures[creature_count].programID++;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == SOUTH){
                        if (game.grid.squares[location_r + 1][location_c] && (location_r + 1 < game.grid.height)){
                            if (creature_name != game.grid.squares[location_r + 1][location_c]->species->name){
                                game.creatures[creature_count].programID = num - 1;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == NORTH){
                        if (location_r != 0) {
                            if (game.grid.squares[location_r - 1][location_c]) {
                                if (creature_name != game.grid.squares[location_r - 1][location_c]->species->name) {
                                    game.creatures[creature_count].programID = num - 1;
                                } else game.creatures[creature_count].programID++;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (more) cout << " ifenemy " << num << endl;
                }
                if (operation == IFSAME){
                    unsigned int num = game.creatures[creature_count].species->program
                    [game.creatures[creature_count].programID].address;
                    if (direct == EAST){
                        if (game.grid.squares[location_r][location_c + 1] && (location_c + 1 < game.grid.width)){
                            if (creature_name == game.grid.squares[location_r][location_c + 1]->species->name){
                                game.creatures[creature_count].programID = num - 1;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == WEST){
                        if (location_c != 0) {
                            if (game.grid.squares[location_r][location_c - 1]) {
                                if (creature_name == game.grid.squares[location_r][location_c - 1]->species->name) {
                                    game.creatures[creature_count].programID = num - 1;
                                } else game.creatures[creature_count].programID++;
                            } else game.creatures[creature_count].programID++;
                        }else game.creatures[creature_count].programID++;
                    }
                    if (direct == SOUTH){
                        if (game.grid.squares[location_r + 1][location_c] && (location_r + 1 < game.grid.height)){
                            if (creature_name == game.grid.squares[location_r + 1][location_c]->species->name){
                                game.creatures[creature_count].programID = num - 1;
                            } else game.creatures[creature_count].programID++;
                        } else game.creatures[creature_count].programID++;
                    }
                    if (direct == NORTH){
                        if (location_r != 0) {
                            if (game.grid.squares[location_r - 1][location_c]) {
                                if (creature_name == game.grid.squares[location_r - 1][location_c]->species->name) {
                                    game.creatures[creature_count].programID = num - 1;
                                } else game.creatures[creature_count].programID++;
                            } else game.creatures[creature_count].programID++;
                        }
                    }
                    if (more) cout << " ifsame " << num << endl;
                }
                if (operation == IFWALL){
                    unsigned int num = game.creatures[creature_count].species->program
                    [game.creatures[creature_count].programID].address;
                    if (direct == EAST){
                        if (location_c + 1 >= game.grid.width) game.creatures[creature_count].programID = num - 1;
                        else game.creatures[creature_count].programID++;
                    }
                    if (direct == WEST){
                        if (location_c == 0) game.creatures[creature_count].programID = num - 1;
                        else game.creatures[creature_count].programID++;
                    }
                    if (direct == SOUTH){
                        if (location_r + 1 >= game.grid.height) game.creatures[creature_count].programID = num - 1;
                        else game.creatures[creature_count].programID++;
                    }
                    if (direct == NORTH){
                        if (location_r == 0) game.creatures[creature_count].programID = num - 1;
                        else game.creatures[creature_count].programID++;
                    }
                    if (more) cout << " ifwall " << num << endl;
                }
                if (operation == GO) {
                    unsigned int num = game.creatures[creature_count].species->program
                    [game.creatures[creature_count].programID].address;
                    game.creatures[creature_count].programID = num - 1;
                    if (more) cout << " go " << num << endl;
                }
            }
        }
        if (!more) printGrid(game);
    }
    // The part is the implementation of the game. The game will continue until
    // the needed number of rounds is reached. What's more, it will print the
    // result of each step based on the command "more", which is derived the "v"
    // or "verbose" from the program arguments.
    return 0;
}