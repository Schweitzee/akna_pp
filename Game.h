//
// Created by svajc on 02/04/2023.
//

#ifndef AKNA_PP_GAME_H
#define AKNA_PP_GAME_H

#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <iostream>

#include "Tile.h"
#include "VektorTable.h"
#include "econio.h"
#include "control.h"

#include "memtrace.h"

class Game {
    int height; /**< The height of the game board. */
    int width; /**< The width of the game board. */
    unsigned mine_n; /**< The number of mines on the game board. */
    int revealed_n; /**< The number of revealed tiles on the game board. */

    static bool fail_state; /**< The failure state of the game. */

    VektorTable table; /**< The game board represented as a vector of vectors of Tile objects. */

public:

    /**
     * @brief Constructor for the Game class.
     *
     * @param heig The height of the game board.
     * @param wid The width of the game board.
     * @param mine The number of mines on the game board.
     */
    Game(int heig, int wid, unsigned mine) : height(heig), width(wid), mine_n(mine), revealed_n(0), table(height, width){};

    /**
     * @brief Returns the height of the game board.
     * @return The height of the game board.
     */
    int get_h() const { return height; }

    /**
     * @brief Returns the width of the game board.
     * @return The width of the game board.
     */
    int get_w() const { return width; }

    /**
     * @brief Checks whether the game has entered the failure state.
     * @return Whether the game has entered the failure state.
     */
    static bool fail_check() {
        return fail_state;
    }

    /**
     * @brief Toggles the failure state of the game.
     */
    static void toggle_fail_state() {
        if(fail_state)
            fail_state = false;
        else
            fail_state = true;
    }

    /**
     * @brief Returns a pointer to the game board.
     * @return A pointer to the game board.
     */
    VektorTable* get_table() { return &this->table; }

    /**
     * @brief Increments the number of revealed tiles by a specified amount.
     * @param a The amount by which to increment the number of revealed tiles.
     */
    void plus_revealed(int a) {
        revealed_n += a;
    }

    /**
     * @brief Randomly places mines on the game board, than fills the nearby mine counters of the tiles.
     */
    void rand_mine() {
        srand((unsigned)time(nullptr)*91);
        unsigned ready_mine = 0;
        while(ready_mine < mine_n){
            int x = rand() % height, y = rand() % width;
            if((!table.get(x,y)->is_mine()) && !table.get(x,y)->uncovered()){
                table.place_mine(x,y);
                ready_mine++;
            }
        }
        table.filler();
    }

    /**
     * @brief Checks whether the game has been won.
     * @return Whether the game has been won.
     */
    bool win_check() const {
        return height*width-mine_n == revealed_n;
    }


   /**
    *
    * @brief Handles the first step of the game, which is different from the other steps.
    * Draws the game board, waits for user input, and performs the appropriate action.
    * @param res reference to the integer storing the key code of the pressed key.
    * @param x reference to the integer storing the x coordinate of the cursor.
    * @param y reference to the integer storing the y coordinate of the cursor.
    */
    void first_step(int& res, int& x, int& y);


   /**
    *
    * @brief Handles the game loop, where the player repeatedly performs actions until they win or fail.
    * Draws the game board, waits for user input, and performs the appropriate action.
    * @param res reference to the integer storing the key code of the pressed key.
    * @param x reference to the integer storing the x coordinate of the cursor.
    * @param y reference to the integer storing the y coordinate of the cursor.
    */
    void game_loop(int& res, int& x, int& y);

   /**
    *
    * @brief Finishes the game by checking if the player has won or failed, and displays the appropriate message.
    * @param res reference to the integer storing the key code of the pressed key.
    */
    void finish_him(int& res) const;


    /**
     * @brief Draws the game board to the console.
     */
    void draw() const;

};

#endif //AKNA_PP_GAME_H
