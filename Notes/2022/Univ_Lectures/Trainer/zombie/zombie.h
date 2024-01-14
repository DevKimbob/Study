#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Game {
    int people_hp = 100;
    int zombie_hp = 100;
    int t_att = 0;
    int t_run = 0;

public:
    void attack(int r);
    void run(int r);
    void infoHP();
    void game_match(int sel);
    int game_over();
    void info_total();
};

class GameManager {
    Game *p;
    int win;
    int game_num;

public:
    GameManager(int game_run);
    ~GameManager();
    void info_total_win();
};

#endif