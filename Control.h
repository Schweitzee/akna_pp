//
// Created by svajc on 26/04/2023.
//

#ifndef AKNA_PP_CONTROL_H
#define AKNA_PP_CONTROL_H

#include <iostream>
# include "econio.h"



template<typename T>
T min(T a, T b) { return a < b ? a : b; }

template<typename T>
T max(T a, T b) { return a > b ? a : b; }



    /**
     * @brief handles the in-game stepping of the cursor
     * @param x horizontal location of the cursor
     * @param y vertical location of the cursor
     * @param a height of the game table
     * @param b width of the game table
     * @return the pressed key (enter - reveal, backspace - flag toggle)
     */
EconioKey stepper(int &x, int &y, int a, int b);





#endif //AKNA_PP_CONTROL_H
