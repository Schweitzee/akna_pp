//
// Created by svajc on 16/04/2023.
//

#ifndef AKNA_PP_FIELD_H
#define AKNA_PP_FIELD_H

#include "Tile.h"

void colornum(unsigned i, bool end);


class Field : public Tile{
    unsigned mine_c; /**< The number of the mines surrounding the Field */

public:

    /**
     * @brief constructs a Field object with surrounding mine_c set to 0
     */
    Field() : Tile(), mine_c(0){}

    /**
     * shows that the tile is not a mine
     * @return false
     */
    bool is_mine() override{return false;}


    /**
     *
     * @param end
     */
    void draw(bool end) override;


    /**
     *
     * @return the No. of mines surrounding the field
     */
    unsigned get_num() override{return mine_c;}


    /**
     * @brief increments the mine_c of the field, used when filling the mine_c var's after creating the mines if the filler function of the VektorTable
     */
    void up() override{mine_c++;}
};

#endif //AKNA_PP_FIELD_H
