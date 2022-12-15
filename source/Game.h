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
    bool display = true;
    //static int nodeCount;
    GameNode* nextGame;
};

void dallocList(GameNode*&);
Game enterGameAttributes(int);
void showEnteredGame(Game);
GameNode* initializeList();
void fillGame(Game&, string);
void showGamesList(GameNode*);
void copyGame(Game&, Game);
void deleteNode(GameNode*&, GameNode*&);
void sortList(GameNode*&, bool, bool);
void reverseList(GameNode*&);
void showAllGames(GameNode*);
void filterPlatform(GameNode*);
void filterOwned(GameNode*);
void filterNew(GameNode*);
void filterPlay(GameNode*);
void filterBacklog(GameNode*);