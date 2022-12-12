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

void editGameInSave(Game inGame)
{
    string prevLines;
    string currentLine;
    string nextLines;
    string inGameIDString = to_string(inGame.id);
    ifstream gamesListRead;
    ofstream gamesListWrite;

    gamesListRead.open("data/gameslist.txt");
    getline(gamesListRead, currentLine, '\n');
    while (currentLine.substr(0, inGameIDString.size()) != inGameIDString)
    {
        prevLines += currentLine + '\n';
        getline(gamesListRead, currentLine, '\n');
    }
    while (getline(gamesListRead, currentLine, '\n'))
        nextLines += currentLine + '\n';
    gamesListRead.close();

    gamesListWrite.open("data/gameslist.txt");
    gamesListWrite << prevLines << inGameIDString << "$"
                   << inGame.name << "$" << inGame.platform
                   << "$" << inGame.format << "$"
                   << inGame.completion << "$"
                   << inGame.priority << "\n"
                   << nextLines;
    gamesListWrite.close();
}