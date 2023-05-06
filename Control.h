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

EconioKey stepper(int &x, int &y, int a, int b);





#endif //AKNA_PP_CONTROL_H
