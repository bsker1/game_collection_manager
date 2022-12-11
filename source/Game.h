#pragma once

#include <iostream>
#include <fstream>

#include "utils.h"

using namespace std;

struct Game
{
    int id = -1;
    string name, platform, format, completion, priority;
};

struct GameNode
{
    Game game;
    GameNode* nextGame;
    bool display = true;
};

void dallocList(GameNode*&);
Game enterGameAttributes(int);
void showEnteredGame(Game);
GameNode* initializeList();
void fillGame(Game&, string);
void showGamesList(GameNode*);