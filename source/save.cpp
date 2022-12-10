#include "save.h"

//  Returns last entered ID from save file, -1 if no save
int getLastID()
{
    ifstream gamesListRead;
    string idString;
    gamesListRead.open("data/gameslist.txt");
    if (getline(gamesListRead, idString, '$'))
    {
        gamesListRead.close();
        return strToInt(idString);
    }
    else
    {
        gamesListRead.close();
        return -1;
    }
}

//  Returns a string with save file contents
string loadFile(string fileName)
{
    ifstream gamesListRead;
    string buffer;
    string fileString;
    gamesListRead.open(fileName);
    while (getline(gamesListRead, buffer, '\n'))
        fileString += buffer + "\n";
    
    gamesListRead.close();
    return fileString;
}

void addGameToSave(Game inGame)
{
    string saveBuffer = loadFile("data/gameslist.txt");
    ofstream gamesListWrite;
    gamesListWrite.open("data/gameslist.txt");
    gamesListWrite << inGame.id << "$"
                   << inGame.name << "$"
                   << inGame.platform << "$"
                   << inGame.format << "$"
                   << inGame.completion << "$"
                   << inGame.priority << "\n"
                   << saveBuffer;
    
    gamesListWrite.close();
}