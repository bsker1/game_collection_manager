#include "Game.h"

//  Deletes each node in a GameNode list, sets head to nullptr
void dallocList(GameNode*& head)
{
    GameNode* iter = head;
    while (iter != nullptr)
    {
        GameNode* prev = iter;
        iter = iter->nextGame;
        delete prev;
    }
    head = nullptr;
}

//  Returns Game object with entered data, id = -1 if the user
//  doesn't confirm the data, id = passed argument otherwise
Game enterGameAttributes(int id)
{
    while (true)
    {
        Game newGame;
        newGame.id = -1;
        string input;

        cout << "\nEnter the game's info, or type \"back\" in any prompt to abort."
             << endl;
        cin.get();
        cout << "\nName:\n*__ ";
        getline(cin, input);
        if (input == "back")
            return newGame;
        newGame.name += input;

        bool loopFlag = true;
        while (loopFlag)
        {
            cout << "\n\nPlatform:\n*__ ";
            getline(cin, input);
            if (input == "back")
                return newGame;
            stringUpper(input);

            ifstream platformsList;
            string listIter;
            platformsList.open("data/platformslist.txt");
            while (getline(platformsList, listIter))
            {
                if (input == listIter)
                {
                    newGame.platform = listIter;
                    loopFlag = false;
                    break;
                }
            }
            platformsList.close();

            if (loopFlag)
            {
                cerr << "ERROR: invalid platform";
                clearBuffer();
            }
        }

        while (true)
        {
            cout << "\n\nFormat (PHYS, DIG, EMU, GP):\n*__ ";
            cin >> input;
            if (input == "back")
                return newGame;
            stringUpper(input);

            if (input != "PHYS" && input != "DIG" && input != "EMU" && input != "GP")
            {
                cerr << "ERROR: invalid format";
                clearBuffer();
                continue;
            }

            newGame.format = input;
            break;
        }

        while (true)
        {
            cout << "\n\nCompletion (NEW, STARTED, BEAT):\n*__ ";
            cin >> input;
            if (input == "back")
                return newGame;
            stringUpper(input);

            if (input != "NEW" && input != "STARTED" && input != "BEAT")
            {
                cerr << "ERROR: invalid format";
                clearBuffer();
                continue;
            }

            newGame.completion = input;
            break;
        }

        while (true)
        {
            cout << "\n\nPriority (NONE, PLAY, BACKLOG):\n*__ ";
            cin >> input;
            if (input == "back")
                return newGame;
            stringUpper(input);

            if (input != "NONE" && input != "PLAY" && input != "BACKLOG")
            {
                cerr << "ERROR: invalid format";
                clearBuffer();
                continue;
            }

            newGame.priority = input;
            break;
        }

        while (true)
        {
            char choice;
            cout << endl;
            showEnteredGame(newGame);
            cout << "\nIs this correct? (Y/N)\n"
                 << "*__ ";
            cin >> choice;

            if (toupper(choice) != 'Y' && toupper(choice) != 'N')
            {
                cerr << "ERROR: invalid choice" << endl;
                clearBuffer();
                continue;
            }

            if (toupper(choice) == 'Y')
                newGame.id = id;
            break;
        }

        return newGame;
    }
}

//  Outputs passed Game object's contents
void showEnteredGame(Game inGame)
{
    cout << "Name: " << inGame.name << endl;
    cout << "Platform: " << inGame.platform << endl;
    cout << "Format: " << inGame.format << endl;
    cout << "Completion: " << inGame.completion << endl;
    cout << "Priority: " << inGame.priority << endl;
}

//  Returns head of a linked list holding Game objects
//  with save file data
GameNode* initializeList()
{
    GameNode* head = nullptr;
    ifstream gamesListRead;
    string currentLine;
    gamesListRead.open("data/gameslist.txt");
    GameNode* iter = nullptr;
    while (getline(gamesListRead, currentLine, '\n'))
    {
        GameNode* newNode = new GameNode;
        fillGame(newNode->game, currentLine);
        newNode->nextGame = nullptr;
        if (head == nullptr)
        {
            head = newNode;
            iter = newNode;
        }
        else
        {
            iter->nextGame = newNode;
            iter = iter->nextGame;
        }
    }

    cout << "working" << endl;
    gamesListRead.close();
    return head;
}

//  Fills a Game object based on contents for a line in the save file
void fillGame(Game& inGame, string gameData)
{
    string currentData;
    int index = 0;
    int indexBuffer = index;
    int currentDataLength = 0;
    while (gameData[index] != '$')
    {
        ++index;
        ++currentDataLength;
    }
    inGame.id = strToInt(gameData.substr(indexBuffer, currentDataLength));

    ++index;
    indexBuffer = index;
    currentDataLength = 0;
    while (gameData[index] != '$')
    {
        ++index;
        ++currentDataLength;
    }
    inGame.name = gameData.substr(indexBuffer, currentDataLength);

    ++index;
    indexBuffer = index;
    currentDataLength = 0;
    while (gameData[index] != '$')
    {
        ++index;
        ++currentDataLength;
    }
    inGame.platform = gameData.substr(indexBuffer, currentDataLength);

    ++index;
    indexBuffer = index;
    currentDataLength = 0;
    while (gameData[index] != '$')
    {
        ++index;
        ++currentDataLength;
    }
    inGame.format = gameData.substr(indexBuffer, currentDataLength);

    ++index;
    indexBuffer = index;
    currentDataLength = 0;
    while (gameData[index] != '$')
    {
        ++index;
        ++currentDataLength;
    }
    inGame.completion = gameData.substr(indexBuffer, currentDataLength);

    inGame.priority = gameData.substr(index + 1);
}

//  Prints the contents of a Game linked list in table form
void showGamesList(GameNode* inHead)
{
    int gameCount = 0;
    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        bool extraLine = false;
        string printedName = to_string(++gameCount) + ". " + iter->game.name;
        cout << "| ";
        int index = 50;
        if (printedName.size() > index)
        {
            extraLine = true;
            while (printedName[index] != ' ')
                --index;
            string nameFirst = printedName.substr(0, index);
            cout << nameFirst << characterBuffer(' ', 50 - index);
            ++index;
        }
        else
            cout << printedName << characterBuffer(' ', 50 - printedName.size());
        
        cout << " | " << iter->game.platform
             << characterBuffer(' ', 8 - iter->game.platform.size())
             << " | " << iter->game.format
             << characterBuffer(' ', 6 - iter->game.format.size())
             << " | " << iter->game.completion
             << characterBuffer(' ', 10 - iter->game.completion.size())
             << " | " << iter->game.priority
             << characterBuffer(' ', 8 - iter->game.priority.size())
             << " |\n";
        
        if (extraLine)
        {
            int countBuffer = to_string(gameCount).size() + 1;
            string nameExcess = printedName.substr(index);
            cout << "| " << characterBuffer(' ', countBuffer) << nameExcess
                 << characterBuffer(' ', 51 - nameExcess.size() - countBuffer)
                 << "|" << characterBuffer(' ', 10) << "|"
                 << characterBuffer(' ', 8) << "|"
                 << characterBuffer(' ', 12) << "|"
                 << characterBuffer(' ', 10) << "|\n";
        }

        iter = iter->nextGame;
    }
}