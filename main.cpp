#include <iostream>
#include <string>

#include "Game.h"
#include "econio.h"

//#define CPORTA

#ifdef CPORTA //includeok a tesztekhez CPORTARA
#include "Field.h"
#include "Mine.h"
#include "VektorTable.h"
#include "gtest_lite.h"
#include "memtrace.h"
#endif

void start_print(){
    econio_clrscr();
    std::string sign = "This is my MINESWEEPER!";
    for (unsigned i = 0; i < sign.size(); ++i) {
        econio_sleep(i*0.004);
        std::cout << sign[i];
    }
    std::cout << std::endl;
}

int main(){

#ifdef CPORTA

    /*
     * Mező tesztek (field és mine)
     */

    Field* fp = new Field;

    TEST(Field, DefCtor){
            EXPECT_TRUE(fp->covered());
            EXPECT_EQ(0, fp->get_num());
    }ENDM

    TEST(Field, mineReturn){
            EXPECT_FALSE(fp->is_mine());
    }ENDM

    TEST(Field, NumUp){
        fp->up();
        EXPECT_EQ(1, fp->get_num());
    }ENDM

    TEST(Field, StateSwitch){
        fp->Uncover();
        EXPECT_TRUE(fp->uncovered());
        fp->Flag();
        EXPECT_TRUE(fp->flagged());
        fp->Cover();
        EXPECT_FALSE(fp->flagged());
    }ENDM

    delete fp;

    Mine* mp = new Mine;

    TEST(Mine, DefCtor){ //annyira irtam volna ide DefCon-t de ugy nem koherens az elnevezes xdd
        EXPECT_EQ(10, mp->get_num());
        EXPECT_TRUE(mp->is_mine());
        EXPECT_TRUE(mp->covered());
    }ENDM

    TEST(Mine, NumUp){
        mp->up();
        EXPECT_EQ(10, mp->get_num());
    }ENDM

    delete mp;

    /*
    -VEKTORTABLE TESZTEK-
    */

    int t = 2;
    int k = 5;

    VektorTable* vtp = new VektorTable(6,8);


    TEST(VektorTable, Ctor_n_Getter){
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 8; ++j) {
                EXPECT_TRUE(vtp->get(i,j)->covered() && vtp->get(i,j)->get_num() == 0);
            }
        }
    }ENDM

    TEST(VektorTable, Place_mine){
        vtp->place_mine(t,t);
        EXPECT_TRUE(vtp->get(t,t)->is_mine());
    }ENDM

    TEST(VektorTable, Flag_toggle){
        vtp->flag_toggle(k,k);
        EXPECT_TRUE(vtp->get(k,k)->flagged());
    }ENDM

    TEST(VektorTable, Filler){
        vtp->filler();
            for (int i = t-1; i <= t+1; ++i) {
                for (int j = t-1; j <= t+1; ++j) {
                    if(i == t && j ==t)
                        EXPECT_EQ(vtp->get(i,j)->get_num(), 10);
                    else
                        EXPECT_EQ(vtp->get(i,j)->get_num(), 1);
                }
            }
    }ENDM

    TEST(VektorTable, Revealer){
        int revealed = vtp->revealer(0,0);
        EXPECT_EQ(6*8-2, revealed);
    }ENDM

    delete vtp;

    /*
     * - GAME Tesztek -
     */

    Game* gp = new Game(6, 8, 47);

    TEST(Game, Alapok){
            EXPECT_EQ(6,gp->get_h());
            EXPECT_EQ(8,gp->get_w());
            EXPECT_FALSE(Game::fail_check());
            EXPECT_TRUE(gp->get_table() != nullptr);
    }ENDM

    TEST(Game, Fail_toggle){
        Game::toggle_fail_state();
        EXPECT_TRUE(Game::fail_check());
        Game::toggle_fail_state();
    }ENDM

    TEST(Game, rand_mine){
        gp->get_table()->get(5,5)->Uncover();
        gp->rand_mine();
        int mine_num = 0;
            for (int i = 0; i < gp->get_h(); ++i) {
                for (int j = 0; j < gp->get_w(); ++j) {
                    if(gp->get_table()->get(i,j)->is_mine())
                        mine_num++;
                }
            }
        EXPECT_EQ(47,mine_num);
        EXPECT_FALSE(gp->get_table()->get(5,5)->is_mine());
    }ENDM

    TEST(Game, win_check){
            gp->plus_revealed(1);
            EXPECT_TRUE(gp->win_check());
            Game temp(20,30,40);
            temp.plus_revealed(560);
            EXPECT_TRUE(temp.win_check());
    }ENDM

    delete gp;

    TEST(Game, Load){
        gp = g_load(std::string("hibas_mentes.txt"));
        EXPECT_TRUE(nullptr == gp);

        EXPECT_THROW(gp = g_load(std::string("kamu_mentes.txt")),std::ifstream::failure&);
        EXPECT_NO_THROW(gp = g_load());
        EXPECT_TRUE(gp!= nullptr);
        delete gp;
    }ENDM


TEST(Teljes, jatek)
    {

#endif

        //std::ifstream inputFile("input.txt");
        ////::streambuf *originalCin = std::cin.rdbuf();  // Save original cin stream buffer
        //std::cin.rdbuf(inputFile.rdbuf());


        int res = KEY_ENTER;
        while (res != KEY_ESCAPE) {
            Game *gameszko = nullptr;
            int branch = -1;
            start_print();
            std::cout << "   - Press '1' to start a new game" << std::endl << "   - Press '2' to load a saved one"
                      << std::endl << "   - Press '3' to exit game" << std::endl;
            std::cin >> branch;
            while (branch != 1 && branch != 2 && branch != 3) {
                std::cout << "Invalid input, 1, 2 or 3 please!" << std::endl;
                econio_flush();
                std::cin >> branch;
            }

            int x = 6;
            int y = 2;
            if (branch == 1) {
                int a = -1, b = -1, c = 10;
                std::cout << "Height and width between 10 and 40, mine number between 10% and 35%" << std::endl
                          << "Type in the parameters of the game separated with a space [height width number_of_mines]: ";
                std::cin >> a >> b >> c;

                while (a < 10 || a > 40 || b < 10 || b > 40 || c < a * b * 0.1 || c > a * b * 0.35) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Wrong numbers, try again: ";
                    std::cin >> a >> b >> c;
                }
                gameszko = new Game(a, b, c);
                gameszko->first_step(res, x, y);
            }


            if (branch == 2) {
                try {
                    gameszko = g_load();
                }
                catch (std::ifstream::failure &err) {
                    std::cout << err.what() << std::endl;
                    econio_sleep(3);
                    branch = -1;
                    continue;
                }

                if (gameszko == nullptr) {
                    std::cout << "Failed to load game, invalid format in saved game!" << std::endl
                              << "Press ENTER to return to the menu";
                    econio_flush();
                    std::getchar();
                    econio_clrscr();
                    branch = -1;
                    continue;
                }
                gameszko->get_table()->filler();
            }
            if (branch == 3)
                break;
            branch = -1;

            gameszko->game_loop(res, x, y);
            if (res == KEY_END) {
                delete gameszko;
                res = KEY_ENTER;
                continue;
            }
            gameszko->finish_him(res);
            delete gameszko;
        }
#ifdef CPORTA
    }ENDM
#endif
    return 0;
}
