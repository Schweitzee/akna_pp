#include <iostream>

#include "Game.h"
#include "Control.h"
#include "memtrace.h"

int main() {
    std::cout << "anyad"<< std::endl;
    int res = KEY_ENTER;
    while(res != KEY_ESCAPE) {
        //
        //      JÁTÉK LEÍRÁS? INPUT ÉS BUILD
        //
        int a = -1, b = -1, c = -1;

        std::cout << "geci a b c-t: ";
        std::cin >> a >> b >> c;

        while (a < 10 || a > 25 || b < 10 || b > 25 || c < a * b * 0.1 || c > a * b * 0.35) {
            fflush(stdin);
            std::cout << "elbasztad zsiguli, geci a b c-t: ";
            std::cin >> a >> b >> c;
        }
        Game gameszko(a, b, c);

        gameszko.table_draw();

        int x = 6;
        int y = 2;
        gameszko.table_draw();
        res = stepper(x, y, a, b);
        econio_normalmode();

        if (res == KEY_ENTER) {
            gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->Uncover();
        }
        if (res == KEY_BACKSPACE)
            gameszko.get_table()->flag_toggle((y - 2) / 2, (x - 6) / 5);

        gameszko.rand_mine();

        if (res == KEY_ENTER) {
            gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->Cover();
            gameszko.plus_revealed(gameszko.get_table()->revealer((y - 2) / 2, (x - 6) / 5));
        }

        while (!gameszko.fail_check() && !gameszko.win_check()) {
            gameszko.table_draw();
            res = stepper(x, y, a, b);
            econio_normalmode();
            if (res == KEY_ENTER && !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->is_mine() &&
                !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->flagged())
                gameszko.plus_revealed(gameszko.get_table()->revealer((y - 2) / 2, (x - 6) / 5));
            if (res == KEY_BACKSPACE && !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->uncovered())
                gameszko.get_table()->flag_toggle((y - 2) / 2, (x - 6) / 5);
            if (res == KEY_ENTER && gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->is_mine() &&
                !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->flagged())
                gameszko.toggle_fail_state();
        }
        if (gameszko.fail_check()) {
            gameszko.table_draw();
            econio_rawmode();
            econio_gotoxy(0, a * 2 + 3);
            econio_normalmode();
            econio_textcolor(COL_RED);
            std::cout << "YOU FAILED" << std::endl << "press anything except ESC to start new game," << std::endl << "press ESC to close game.";
            econio_textcolor(COL_RESET);
            econio_rawmode();
            res = econio_getch();
            econio_normalmode();
        }
        if (gameszko.win_check()) {
            gameszko.table_draw();
            econio_rawmode();
            econio_gotoxy(0, a * 2 + 3);
            econio_normalmode();
            econio_textcolor(COL_GREEN);
            std::cout << "YOU WON!" << std::endl << "press anything except ESC to start new game," << std::endl << "press ESC to close game.";
            econio_textcolor(COL_RESET);
            econio_rawmode();
            res = econio_getch();
            econio_normalmode();
        }
    }
    return 0;
}


