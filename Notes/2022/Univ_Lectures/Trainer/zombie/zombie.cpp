#include "zombie.h"

////////////////////  Game  ////////////////////

void Game::attack(int r) {
    this->people_hp -= r;
    this->zombie_hp -= 30;

    this->t_att += 30;
    cout << "Got hit : " << r << endl;
}

void Game::run(int r) {
    this->t_run += r;
    cout << "Dodged : " << r << endl;
}

void Game::infoHP() {
    cout << "Your helth : " << this->people_hp << ", Zombie's helth : " << this->zombie_hp << endl;
}

void Game::game_match(int sel) {
    switch (sel) {
        case 1:
            attack((rand() % 3 + 2) * 10);
            infoHP();
            break;
        case 2:
            run((rand() % 3 + 2) * 10);
            infoHP();
            break;
        default:
            cout << "Unknown selection. Try again" << endl;
            break;
    }
}

int Game::game_over() {
    if (this->people_hp >= 0 && this->zombie_hp >= 0)
        return 2;  // 2 : still playing
    return (zombie_hp < 0);  // 1 : win, 0 : loss
}

void Game::info_total() {
    cout << "Attack : " << this->t_att << ", Dodge : " << this->t_run << "\n" << endl;
}

////////////////////  GameManager  ////////////////////

GameManager::GameManager(int game_run) {
    int sel;

    this->p = new Game[game_run];
    this->win = 0;
    this->game_num = game_run;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < game_run; i++) {
        // play game
        do {
            cout << "Attack / Dodge (1 or 2) >> ";
            cin >> sel;
            this->p[i].game_match(sel);
        } while (this->p[i].game_over() == 2);

        // result
        cout << "== Game ";
        if (this->p[i].game_over()) {
            cout << "Won ==" << endl;
            this->win++;
        }
        else
            cout << "Lost ==" << endl;

        // print info
        this->p[i].info_total();
    }
}

GameManager::~GameManager() {
    delete [] this->p;
    cout << "\nFrom Deconstructor : Exiting..." << endl;
}

void GameManager::info_total_win() {
    cout << "Won " << this->win << " games out of " << this->game_num << endl;
}