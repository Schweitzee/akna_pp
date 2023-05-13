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
    std::vector<std::vector<Tile *>> matrix; /** < 2D vector matrix filled with Tile* to allocate Fields and Mines onto them >*/
public:

    /**
     * @brief Constructor to the Vektortable, fills it up with basic Field objects allocated dynamically
     * @param row No. of rows
     * @param col No. of columns
     */
    VektorTable(int row, int col);

    /**
     * @brief changes a Field object on a given coordinate to a Mine object
     * @param row
     * @param col
     */
    void place_mine(unsigned row, unsigned col);

    /**
     * @brief returns the address of a Field or a Mine given its coordinates
     * @param row
     * @param col
     * @return
     */
    Tile* get(int row, int col) {return matrix[row][col];}

    /**
     * @brief Toggles the flag state of a given Field or Mine based on coordinates
     * @param row
     * @param col
     */
    void flag_toggle(int row, int col);

    /**
     * @brief The revealer algorithm used when the user reveals a block and some of the block automatically gets revealed around it (this reveals the first one too)
     * @param row y coordinate of the initially revealed Tile
     * @param col x coordinate of the initially revealed Tile
     * @return the number of blocks revealed in the game with the algorithm
     */
    int revealer(int row, int col);

    /**
     * @brief goes over the whole VektorTable and if it finds a bomb, it gives +1 into the mine_c to all the Tiles around it
     */
    void filler();

    ~VektorTable() {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                delete matrix[i][j];
            }
        }
    }
};

#endif //AKNA_PP_VEKTORTABLE_H
