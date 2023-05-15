//
// Created by svajc on 25/04/2023.
//

#include "VektorTable.h"


VektorTable::VektorTable(int row, int col) {
    matrix.resize(row);
    for (int i = 0; i < row; i++) {
        matrix[i].resize(col);
        for (int j = 0; j < col; j++) {
            matrix[i][j] = new Field();
        }
    }
}

void VektorTable::place_mine(int row, int col) {
    delete matrix[row][col];
    matrix[row][col] = new Mine();
}


void VektorTable::flag_toggle(int row, int col) {
    if (matrix[row][col]->flagged())
        matrix[row][col]->Cover();
    else if (matrix[row][col]->covered())
        matrix[row][col]->Flag();
}

int VektorTable::revealer(int row, int col){
    int plus_revealed = 0;
    int width = matrix.size();
    int height = matrix[0].size();
    if(matrix[row][col]->covered() && !matrix[row][col]->is_mine()){
        if(matrix[row][col]->get_num()){
            matrix[row][col]->Uncover();
            return 1;
        }
        matrix[row][col]->Uncover();
        plus_revealed++;
        for (int i = (row-1); i <= (row+1); ++i) {
            for (int j = (col-1); j <= (col+1); ++j) {
                if(i >= 0 && i < height && j >= 0 && j < width){
                    if(matrix[i][j]->get_num() == 0){
                        plus_revealed += revealer(i,j);
                    }
                    else if(matrix[i][j]->covered()  && !matrix[i][j]->is_mine()){
                        matrix[i][j]->Uncover();
                        plus_revealed++;
                    }
                }
            }
        }
        return plus_revealed;
    }
    else
        return 0;
}

void VektorTable::filler() {
    unsigned height = matrix.size(), width = matrix[0].size();
    //bal felso
    if(matrix[0][0]->is_mine()){
        matrix[0][1]->up();
        matrix[1][0]->up();
        matrix[1][1]->up();
    }

    //jobb felso
    if(matrix[0][width-1]->is_mine()){
        matrix[0][width-2]->up();
        matrix[1][width-1]->up();
        matrix[1][width-2]->up();
    }

    //bal also
    if(matrix[height-1][0]->is_mine()){
        matrix[height-2][0]->up();
        matrix[height-1][1]->up();
        matrix[height-2][1]->up();
    }

    //jobb also
    if(matrix[height-1][width-1]->is_mine()){
        matrix[height-2][width-1]->up();
        matrix[height-1][width-2]->up();
        matrix[height-2][width-2]->up();
    }

    //felso sor
    for (unsigned i = 1; i < width-1; ++i) {
        if(matrix[0][i]->is_mine()){
            matrix[0][i-1]->up();
            matrix[0][i+1]->up();
            matrix[1][i-1]->up();
            matrix[1][i]->up();
            matrix[1][i+1]->up();
        }
    }

    //also sor
    for (unsigned i = 1; i < width-1; ++i) {
        if(matrix[height-1][i]->is_mine()){
            matrix[height-1][i-1]->up();
            matrix[height-1][i+1]->up();
            matrix[height-2][i-1]->up();
            matrix[height-2][i]->up();
            matrix[height-2][i+1]->up();
        }
    }

    //bal oszlop
    for (unsigned i = 1; i < height-1; ++i) {
        if(matrix[i][0]->is_mine()){
            matrix[i-1][0]->up();
            matrix[i+1][0]->up();
            matrix[i-1][1]->up();
            matrix[i][1]->up();
            matrix[i+1][1]->up();
        }
    }

    //jobb oszlop
    for (unsigned i = 1; i < height-1; ++i) {
        if(matrix[i][width-1]->is_mine()){
            matrix[i-1][width-1]->up();
            matrix[i+1][width-1]->up();
            matrix[i-1][width-2]->up();
            matrix[i][width-2]->up();
            matrix[i+1][width-2]->up();
        }
    }

    //belsoket toli
    for (unsigned i = 1; i < height-1; ++i) {
        for (unsigned j = 1; j < width-1; ++j) {
            if(matrix[i][j]->is_mine()){
                matrix[i-1][j-1]->up();
                matrix[i-1][j]->up();
                matrix[i-1][j+1]->up();
                matrix[i][j-1]->up();
                matrix[i][j+1]->up();
                matrix[i+1][j-1]->up();
                matrix[i+1][j]->up();
                matrix[i+1][j+1]->up();
            }

        }
    }
}

