//
// Created by svajc on 02/04/2023.
//

#ifndef AKNA_PP_GAME_H
#define AKNA_PP_GAME_H


#include "Tile.h"
#include "VektorTable.h"
#include "econio.h"

#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <iostream>


class Game{
    int height;
    int width;
    unsigned mine_n;
    int revealed_n;

    static bool fail_state;

    VektorTable table;
public:

    Game(int heig, int wid, unsigned mine) : height(heig), width(wid), mine_n(mine), revealed_n(0), table(height, width){};

    bool fail_check(){
        return fail_state;
    }
    void toggle_fail_state(){
        if(fail_state)
            fail_state = false;
        else
            fail_state = true;
    }

    VektorTable* get_table(){return &this->table;}

    void plus_revealed(int a){
        revealed_n += a;
    }

    void rand_mine(){
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

    bool win_check() const{
        return height*width-mine_n == revealed_n;
    }

    void table_draw() const;

};

#endif //AKNA_PP_GAME_H
