//
// Created by svajc on 02/04/2023.
//

#ifndef AKNA_PP_GAME_H
#define AKNA_PP_GAME_H

#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <fstream>

#include "Tile.h"
#include "VektorTable.h"
#include "econio.h"

//#include "memtrace.h"

class Game {
    int height; /**< The height of the game board. */
    int width; /**< The width of the game board. */
    int mine_n; /**< The number of mines on the game board. */
    int revealed_n; /**< The number of revealed tiles on the game board. */

    static bool fail_state; /**< The failure state of the game. */

    VektorTable* table; /**< The game board represented as a vector of vectors of Tile objects. */

public:

    /**
     * @brief Constructor for the Game class.
     *
     * @param heig The height of the game board.
     * @param wid The width of the game board.
     * @param mine The number of mines on the game board.
     */
    Game(int heig, int wid, int mine, VektorTable* t = nullptr, int r = 0) : height(heig), width(wid), mine_n(mine), revealed_n(r){
        if(t == nullptr){
            table = new VektorTable(heig,wid);
        }
        else
            table = t;
    };

    /**
     * @brief saves a game to a txt file
     * @param file = "mentes.txt" string path to the file in which it stores the state of the game
     * @return bool based on the success of the saving
     */
    bool save(const std::string& file = "mentes.txt") const;

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
    static bool fail_check(){return fail_state;}

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
    VektorTable* get_table() const { return this->table; }

    /**
     * @brief Increments the number of revealed tiles by a specified amount.
     * @param a The amount by which to increment the number of revealed tiles.
     */
    void plus_revealed(int a) {revealed_n += a;}

    /**
     * @brief Randomly places mines on the game board, than fills the nearby mine counters of the tiles.
     */
    void rand_mine();

    /**
     * @brief Checks whether the game has been won.
     * @return Whether the game has been won.
     */
    bool win_check() const {return height*width-mine_n == revealed_n;}


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

    ~Game(){
        delete table;
    }
};

/**
 * @brief Loads a game from a txt file into and allocates a game obj. to it
 * @param from = "mentes.txt" string path to the file storing the saved game
 * @return An address to a dynamically allocated(!) and made Game object ready to be used with game loop.
 */
Game* g_load(const std::string& from = "mentes.txt");

#endif //AKNA_PP_GAME_H
