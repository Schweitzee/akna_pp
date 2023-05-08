//
// Created by svajc on 16/04/2023.
//

#ifndef AKNA_PP_TILE_H
#define AKNA_PP_TILE_H

#include <iostream>

#include "econio.h"



class Tile {
    enum { COVERED, UNCOVERED, FLAGGED } state; /**< State of the Field */

public:

    /**
     * @brief Constructor of the Tile obj., sets it to COVERED by default
     */
    Tile(){
        this->state = COVERED;
    }

    /**
     * @brief sets the state of the Tile to Flagged
     */
    void Flag(){
        this->state = FLAGGED;
    }

    /**
     *
     * @return bool based on whether the tile is FLAGGED
     */
    bool flagged(){return state == FLAGGED;}


    /**
     * @brief sets the state of the Tile to UNCOVERED
     */
    void Uncover(){
        this->state = UNCOVERED;
    }

    /**
     *
     * @return bool based on whether the tile is UNCOVERED
     */
    bool uncovered(){return this->state == UNCOVERED;}


    /**
     * @brief sets the state of the Tile to COVERED
     */
    void Cover(){
        this->state = COVERED;
    }

    /**
     *
     * @return bool based on whether the tile is COVERED
     */
    bool covered(){return this->state == COVERED;}

    /**
     *
     * @return true is it's a mine, false if it isn't
     */
    virtual bool is_mine() = 0;

    /**
     * @brief used in field
     * @return the No. of mines surrounding the Tile
     */
    virtual unsigned get_num() = 0;

    /**
     * @brief draws the tile, used in Field and Mine
     * @param game_end bool based on the state of the game (ended - true, still going - false)
     */
    virtual void draw(bool game_end) = 0;

    /**
     * @brief increments the surrounding mine counter var. of the FIeld in descendant
     */
    virtual void up() = 0;

    virtual ~Tile() = default;

};



#endif //AKNA_PP_TILE_H
