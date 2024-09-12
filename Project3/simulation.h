/**
* @file simulation.h
* @brief This file only focuses on printing the game.
*/
#include "world_type.h"
#include <iostream>
#include <string>
using namespace std;
#ifndef INC_280PROJ3_SIMULATION_H
#define INC_280PROJ3_SIMULATION_H

/**
 * @brief This function helps to get the first two characters of a string.
 *
 * @param name
 *
 * Based on the rules of printing the grid, the first two characters of the
 * name of the species of the creatures need to be printed. Therefore, they need
 * to be derived in advance.
 */
string get_first_two(string name);

/**
 * @brief This function can print every grid of the game according the
 * requirements.
 *
 * @param game
 */
void printGrid(const world_t& game);

#endif