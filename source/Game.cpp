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

    gamesListRead.close();
    return head;
}

//  Fills a Game object based on contents from a line in the save file
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
//  marked for display, returns number of items displayed
int showGamesList(GameNode* inHead)
{
    int gameCount = 0;
    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        if (!iter->display)
        {
            iter = iter->nextGame;
            continue;
        }
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

    return gameCount;
}

//  Copies one Game object's members to another Game object
void copyGame(Game& copy, Game source)
{
    copy.id = source.id;
    copy.name = source.name;
    copy.platform = source.platform;
    copy.format = source.format;
    copy.completion = source.completion;
    copy.priority = source.priority;
}

//  Deletes a selected node from a linked list
void deleteNode(GameNode*& inHead, GameNode*& selectedGame)
{
    if (inHead == nullptr)
    {
        cout << "\nNo games to delete!" << endl;
        return;
    }

    if (selectedGame == inHead)
    {
        if (inHead->nextGame == nullptr)
            inHead = nullptr;
        else
            inHead = inHead->nextGame;
        delete selectedGame;
        selectedGame = nullptr;
        return;
    }

    GameNode* iter = inHead;
    GameNode* prev = iter;
    while (iter != selectedGame)
    {
        prev = iter;
        iter = iter->nextGame;
    }
    prev->nextGame = iter->nextGame;
    delete selectedGame;
    selectedGame = nullptr;
}

//  Sorts a linked list based on chosen parameters
void sortList(GameNode*& inHead, bool byName, bool descending)
{
    if (inHead->nextGame == nullptr)
        return;
    
    GameNode* newHead = nullptr;
    GameNode* sourceIter = inHead;
    GameNode* newIter = newHead;
    if (byName)
    {
        while (inHead != nullptr)
        {
            GameNode* nextNode = inHead;
            sourceIter = inHead;
            while (sourceIter != nullptr)
            {
                string sourceNameLower = sourceIter->game.name;
                stringLower(sourceNameLower);
                string nextNameLower = nextNode->game.name;
                stringLower(nextNameLower);
                if (sourceNameLower < nextNameLower)
                    nextNode = sourceIter;
                sourceIter = sourceIter->nextGame;
            }

            GameNode* newNode = new GameNode;
            copyGame(newNode->game, nextNode->game);
            newNode->display = nextNode->display;
            newNode->nextGame = nullptr;
            if (newHead == nullptr)
            {
                newHead = newNode;
                newIter = newNode;
            }
            else
            {
                newIter->nextGame = newNode;
                newIter = newIter->nextGame;
            }

            deleteNode(inHead, nextNode);
        }
    }
    else
    {
        while (inHead != nullptr)
        {
            GameNode* nextNode = inHead;
            sourceIter = inHead;
            while (sourceIter != nullptr)
            {
                if (sourceIter->game.id < nextNode->game.id)
                    nextNode = sourceIter;
                sourceIter = sourceIter->nextGame;
            }

            GameNode* newNode = new GameNode;
            copyGame(newNode->game, nextNode->game);
            newNode->display = nextNode->display;
            newNode->nextGame = nullptr;
            if (newHead == nullptr)
            {
                newHead = newNode;
                newIter = newNode;
            }
            else
            {
                newIter->nextGame = newNode;
                newIter = newIter->nextGame;
            }

            deleteNode(inHead, nextNode);
        }
    }

    if (descending)
        reverseList(newHead);
    
    inHead = newHead;
}

//  Reverses the elements of a linked list
void reverseList(GameNode*& inHead)
{
    if (inHead->nextGame == nullptr)
        return;
    
    GameNode* newHead = inHead;
    GameNode* newPrev = newHead;
    while (newHead->nextGame != nullptr)
    {
        newPrev = newHead;
        newHead = newHead->nextGame;
    }

    GameNode* newTail = newHead;
    while (inHead != newTail)
    {
        newPrev = inHead;
        while (newPrev->nextGame != newTail)
            newPrev = newPrev->nextGame;
        newTail->nextGame = newPrev;
        newPrev->nextGame = nullptr;
        newTail = newPrev;
    }

    inHead = newHead;
}

//  Sets all nodes' display member to true
void showAllGames(GameNode* inHead)
{
    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        iter->display = true;
        iter = iter->nextGame;
    }
}

void filterPlatform(GameNode* inHead)
{
    string input;
    bool loopFlag = true;
    cin.get();
    while (loopFlag)
    {
        cout << "\n\nEnter a platform, or type \"back\" to cancel:\n"
             << "\n*__ ";
        getline(cin, input);
        if (input == "back")
            return;
        stringUpper(input);

        ifstream platformsList;
        string listIter;
        platformsList.open("data/platformslist.txt");
        while (getline(platformsList, listIter))
        {
            if (input == listIter)
            {
                loopFlag = false;
                break;
            }
        }
        platformsList.close();

        if (loopFlag)
        {
            cerr << "\n\nERROR: invalid platform" << endl;
            clearBuffer();
        }
    }

    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        if (iter->game.platform != input)
            iter->display = false;
        iter = iter->nextGame;
    }
}

void filterOwned(GameNode* inHead)
{
    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        if (iter->game.format != "PHYS" && iter->game.format != "DIG")
            iter->display = false;
        iter = iter->nextGame;
    }
}

void filterNew(GameNode* inHead)
{
    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        if (iter->game.completion != "NEW")
            iter->display = false;
        iter = iter->nextGame;
    }
}

void filterPlay(GameNode* inHead)
{
    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        if (iter->game.priority == "NONE")
            iter->display = false;
        iter = iter->nextGame;
    }
}

void filterBacklog(GameNode* inHead)
{
    GameNode* iter = inHead;
    while (iter != nullptr)
    {
        if (iter->game.priority != "BACKLOG")
            iter->display = false;
        iter = iter->nextGame;
    }
}

void randomizeGame(GameNode* inHead, int gameCount)
{
    if (gameCount < 2)
    {
        cout << "\nNothing to randomize!" << endl;
        return;
    }
    srand(time(NULL));
    while (true)
    {
        int game = rand() % gameCount;
        GameNode* iter = inHead;
        while (!iter->display)
            iter = iter->nextGame;
        int index = 0;
        while (index != game)
        {
            iter = iter->nextGame;
            while (!iter->display)
                iter = iter->nextGame;
            ++index;
        }
        
        cout << "\nYour game is " << iter->game.name << "!" << endl;
        while (true)
        {
            char choice;
            cout << endl;
            cout << "\nRun again? (Y/N)\n"
                 << "*__ ";
            cin >> choice;

            if (toupper(choice) != 'Y' && toupper(choice) != 'N')
            {
                cerr << "ERROR: invalid choice" << endl;
                clearBuffer();
                continue;
            }

            if (toupper(choice) == 'Y')
                break;
            
            return;
        }
    }
}