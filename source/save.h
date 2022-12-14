#pragma once

#include <fstream>
#include <iostream>

#include "utils.h"
#include "Game.h"

using namespace std;

int getLastID();
string loadFile(string);
void addGameToSave(Game);
void editGameInSave(Game);
void deleteGameInSave(int);