//
// Created by svajc on 25/04/2023.
//

#ifndef AKNA_PP_VEKTORTABLE_H
#define AKNA_PP_VEKTORTABLE_H

#include "Field.h"
#include "Mine.h"
#include <vector>

#include "memtrace.h"

class VektorTable {
    std::vector<std::vector<Tile *>> matrix;
public:


    VektorTable(int row, int col) {
        matrix.resize(row);
        for (int i = 0; i < row; i++) {
            matrix[i].resize(col);
            for (int j = 0; j < col; j++) {
                matrix[i][j] = new Field();
            }
        }
    }

    void place_mine(unsigned row, unsigned col) {
        delete matrix[row][col];
        matrix[row][col] = new Mine();
    }

    Tile* get(int row, int col) {
        return matrix[row][col];
    }

    void flag_toggle(int row, int col) {
        if (matrix[row][col]->flagged())
            matrix[row][col]->Cover();
        else if (matrix[row][col]->covered())
            matrix[row][col]->Flag();
    }

    int revealer(int row, int col);

    void filler();

    ~VektorTable() {

        std::cout << "VEGEM VAN GECI - 1" << std::endl;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                delete matrix[i][j];
            }
        }
        std::cout << "VEGEM VAN GECI - 2" << std::endl;
    }
};

#endif //AKNA_PP_VEKTORTABLE_H
