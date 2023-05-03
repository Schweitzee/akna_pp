//
// Created by svajc on 25/04/2023.
//

#ifndef AKNA_PP_VEKTORTABLE_H
#define AKNA_PP_VEKTORTABLE_H

#include "Tile.h"
#include "Field.h"
#include "Mine.h"

#include <vector>

class VektorTable {
    std::vector<std::vector<Tile*>> matrix;
public:
    VektorTable(int row, int col) {
        matrix.resize(row);
        for (int i = 0; i < row; i++) {
            matrix[i].resize(col);
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                matrix[i][j] = new Field();
            }
        }
    }

    void place_mine(unsigned row, unsigned col){
        delete matrix[row][col];
        matrix[row][col] = new Mine();
    }

    Tile* get(int row, int col) const{
        return matrix[row][col];
    }

    Tile* get(int row, int col){
        return matrix[row][col];
    }

    void flag_toggle(int row, int col){
        if(matrix[row][col]->flagged())
            matrix[row][col]->Cover();
        else if(matrix[row][col]->covered())
            matrix[row][col]->Flag();
    }

    int revealer(int row, int col);

    void filler();

    ~VektorTable(){
        std::cout << "VÉGEM VAN GECI" << std::endl;
        for(auto & i : matrix){
            for (auto & j : i) {
                delete j;
            }
        }
    }
};

#endif //AKNA_PP_VEKTORTABLE_H
