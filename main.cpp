#include <iostream>

#include "Game.h"
#include "memtrace.h"

int main() {
    std::cout << "anyad"<< std::endl;
    int res = KEY_ENTER;
    while(res != KEY_ESCAPE) {
        //
        //      JÁTÉK LEÍRÁS? INPUT ÉS BUILD
        //
        int a = -1, b = -1, c = 10;

        std::cout << "geci a b c-t: ";
        std::cin >> a >> b >> c;

        while (a < 10 || a > 25 || b < 10 || b > 25 || c < a * b * 0.1 || c > a * b * 0.35) {
            fflush(stdin);
            std::cout << "elbasztad zsiguli, geci a b c-t: ";
            std::cin >> a >> b >> c;
        }
        Game gameszko(a, b, c);

        int x = 6;
        int y = 2;

        gameszko.first_step(res, x, y);

        gameszko.game_loop(res, x, y);

        gameszko.finish_him(res);
    }
    return 0;
}


