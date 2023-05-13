//
// Created by svajc on 16/04/2023.
//

#ifndef AKNA_PP_MINE_H
#define AKNA_PP_MINE_H

#include "Tile.h"

class Mine : public Tile {
public:

    /**
     * @brief constructs a mine with the basic constructor of the tile
     */
    Mine() : Tile(){}


    /**
     * shows that the tile is a mine
     * @return true
     */
    bool is_mine() override{return true;}


    /**
     * @brief draws the mine cells based on the state of the game
     * @param end shows the function if the game is ended
     */
    void draw(bool end) override;


    /**
     * @brief another way to decide if the tile is a mine
     * @return 10 all the time
     */
    unsigned get_num()override{return 10;}


    /**
     * @brief this function is needed for the Field, but is called on Mines too, so it does nothing on them
     */
    void up()override{};

};

#endif //AKNA_PP_MINE_H
