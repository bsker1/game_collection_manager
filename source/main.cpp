#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Game
{
    int id;
    string name, platform, format, completion, priority;
};
void fillGame(Game &, string);

struct GameNode
{
    Game game;
    GameNode* nextGame;
};
void dallocList(GameNode*);

void viewCollection();
void addGames();

void displayTableMargin();
void displayGamesList(GameNode*);
void stringUpper(string&);
int generateID(string);
void displayGame(Game&);
void insertGame(Game&, string&);
void clearBuffer();

int main()
{
    while (true)
    {
        int choice = 0;
        cout << "\nMain Menu\n" << endl;

        cout << "\t1) View Collection\n"
             << "\t2) Add Games\n"
             << "\t3) Quit Program\n"
             << "\n*__ ";
        cin >> choice;

        if (choice < 1 || choice > 3)
        {
            cerr << "ERROR: invalid choice" << endl;
            clearBuffer();
            continue;
        }
        
        switch(choice)
        {
            case 1:
                viewCollection();
                break;
            case 2:
                addGames();
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
        }
    }
}

void viewCollection()
{
    ifstream gamesListRead;
    string currentLine;
    string gameDataBuffer;
    int gameCount = 0;
    //  Fills gameDataBuffer with last gameslist.txt save
    gamesListRead.open("data/gameslist.txt");
    while (getline(gamesListRead, currentLine, '\n'))
    {
        gameDataBuffer += currentLine + "\n";
        ++gameCount;
    }
    gamesListRead.close();
    currentLine.clear();

    int index = 0;
    int indexBuffer = index;
    int currentDataLength = 0;
    GameNode* gameHead = nullptr;
    //  Fills LL with game objects with saved data
    for (int i = 0; i < gameCount; ++i)
    {
        //  Fills currentLine with game data
        while (gameDataBuffer[index] != '\n')
        {
            ++index;
            ++currentDataLength;
        }
        currentLine = gameDataBuffer.substr(indexBuffer, currentDataLength);
        ++index;
        indexBuffer = index;
        currentDataLength = 0;

        //  Appends LL with data
        GameNode* newNode = new GameNode;
        newNode->nextGame = nullptr;
        fillGame(newNode->game, currentLine);
        if (gameHead == nullptr)
            gameHead = newNode;
        else
        {
            GameNode* temp = gameHead;
            while (temp->nextGame != nullptr)
                temp = temp->nextGame;
            temp->nextGame = newNode;
        }
    }

    displayTableMargin();
    displayGamesList(gameHead);

    dallocList(gameHead);
    gameHead = nullptr;
}

void displayTableMargin()
{
    string fillerBuffer;
    for (int i = 0; i < 46; ++i)
        fillerBuffer += " ";
    cout << "\nName" << fillerBuffer << "| Platform | Format | Completion | Priority"
         << endl;
    fillerBuffer.clear();
    for (int i = 0; i < 50; ++i)
        fillerBuffer += "-";
    cout << fillerBuffer << "|";
    fillerBuffer.clear();
    for (int i = 0; i < 10; ++i)
        fillerBuffer += "-";
    cout << fillerBuffer << "|";
    fillerBuffer.clear();
    for (int i = 0; i < 8; ++i)
        fillerBuffer += "-";
    cout << fillerBuffer << "|";
    fillerBuffer.clear();
    for (int i = 0; i < 12; ++i)
        fillerBuffer += "-";
    cout << fillerBuffer << "|";
    fillerBuffer.clear();
    for (int i = 0; i < 9; ++i)
        fillerBuffer += "-";
    cout << fillerBuffer << endl;
    fillerBuffer.clear();
}

void displayGamesList(GameNode* head)
{
    if (head == nullptr)
    {
        cout << endl;
        return;
    }

    GameNode* iter = head;
    int gameNum = 1;
    while (iter != nullptr)
    {
        //  Prints game names
        bool secondLine = false;
        int index = 49;
        string fillerBuffer;
        string currentName = to_string(gameNum) + ". " + iter->game.name;
        if (currentName.size() <= 49)
        {
            cout << currentName;
            for (int i = 0; i < 50 - currentName.size(); ++i)
                fillerBuffer += " ";
            cout << fillerBuffer << "| ";
            fillerBuffer.clear();
        }
        else
        {
            secondLine = true;
            while (currentName[index] != ' ')
                --index;
            cout << currentName.substr(0, index);
            for (int i = 0; i < 50 - index; ++i)
                fillerBuffer += " ";
            cout << fillerBuffer << "| ";
            fillerBuffer.clear();
            ++index;
        }

        string currentPlatform = iter->game.platform;
        cout << currentPlatform;
        for (int i = 0; i < 9 - currentPlatform.size(); ++i)
            fillerBuffer += " ";
        cout << fillerBuffer << "| ";
        fillerBuffer.clear();

        string currentFormat = iter->game.format;
        cout << currentFormat;
        for (int i = 0; i < 7 - currentFormat.size(); ++i)
            fillerBuffer += " ";
        cout << fillerBuffer << "| ";
        fillerBuffer.clear();

        string currentCompletion = iter->game.completion;
        cout << currentCompletion;
        for (int i = 0; i < 11 - currentCompletion.size(); ++i)
            fillerBuffer += " ";
        cout << fillerBuffer << "| ";
        fillerBuffer.clear();

        string currentPriority = iter->game.priority;
        cout << currentPriority << endl;

        if (secondLine)
        {
            string remainingName = currentName.substr(index,
                                                      currentName.size() - index);
            cout << remainingName;
            for (int i = 0; i < 50 - remainingName.size(); ++i)
                fillerBuffer += " ";
            cout << fillerBuffer << "|";
            fillerBuffer.clear();
            for (int i = 0; i < 10; ++i)
                fillerBuffer += " ";
            cout << fillerBuffer << "|";
            fillerBuffer.clear();
            for (int i = 0; i < 8; ++i)
                fillerBuffer += " ";
            cout << fillerBuffer << "|";
            fillerBuffer.clear();
            for (int i = 0; i < 12; ++i)
                fillerBuffer += " ";
            cout << fillerBuffer << "|\n";
        }

        iter = iter->nextGame;
        ++gameNum;
    }
}

void dallocList(GameNode* head)
{
    if (head == nullptr)
        return;
    
    GameNode* prev = head;
    GameNode* next = prev;
    while (next != nullptr)
    {
        prev = next;
        next = prev->nextGame;
        delete prev;
    }
}

void fillGame(Game &inGame, string gameData)
{
    int index = 0;
    int indexBuffer = index;
    int currentDataLength = 0;

    while (gameData[index] != '$')
    {
        ++index;
        ++currentDataLength;
    }
    inGame.id = generateID(gameData.substr(indexBuffer, currentDataLength));
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
    ++index;
    indexBuffer = index;
    currentDataLength = 0;

    while (gameData[index] != '$')
    {
        ++index;
        ++currentDataLength;
    }
    inGame.priority = gameData.substr(indexBuffer, currentDataLength);
}

void addGames()
{
    ifstream gamesListRead;
    string currentGame;
    string gameDataBuffer;
    int lastID = 0;

    gamesListRead.open("data/gameslist.txt");
    //  Gets last inserted ID to prevent ID duplicates
    if (getline(gamesListRead, currentGame, '$'))
    {
        gameDataBuffer += currentGame + "$";
        lastID = generateID(currentGame);
    }

    //  Fills gameDataBuffer with last gameslist.txt save
    while (getline(gamesListRead, currentGame, '\n'))
        gameDataBuffer += currentGame + "\n";
    gamesListRead.close();

    while (true)
    {
        Game newGame;
        string input;
        newGame.id = ++lastID;

        cout << "\nEnter the game's info, or type \"back\" in any prompt to abort."
             << endl;
        cin.get();

        cout << "\nName:\n*__ ";
        getline(cin, input);
        if (input == "back")
            return;
        newGame.name = input;

        ifstream platformsList;
        bool loopFlag = true;
        while (loopFlag)
        {
            platformsList.open("data/platformslist.txt");
            cout << "\n\nPlatform:\n*__ ";
            getline(cin, input);
            if (input == "back")
                return;
            stringUpper(input);

            //  Checks if inputted platform is supported
            string platformIterator;
            while (getline(platformsList, platformIterator, '\n'))
            {
                if (input == platformIterator)
                {
                    newGame.platform = platformIterator;
                    loopFlag = false;
                    break;
                }
            }

            if (loopFlag)
            {
                cerr << "ERROR: invalid platform";
                clearBuffer();
            }
            platformsList.close();
        }
        
        while (true)
        {
            cout << "\n\nFormat (PHYS, DIG, EMU, GP):\n*__ ";
            cin >> input;
            if (input == "back")
                return;
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
                return;
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
                return;
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
            displayGame(newGame);
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
                insertGame(newGame, gameDataBuffer);
            break;
        }

        while (true)
        {
            char choice;
            cout << "\nGame added successfully. Add another game? (Y/N)\n"
                 << "*__ ";
            cin >> choice;

            if (toupper(choice) != 'Y' && toupper(choice) != 'N')
            {
                cerr << "ERROR: invalid choice" << endl;
                clearBuffer();
                continue;
            }

            if (toupper(choice) == 'N')
                return;
            
            break;
        }
    }
}

void stringUpper(string &inString)
{
    for (int i = 0; i < inString.size(); ++i)
        inString[i] = toupper(inString[i]);
}

int generateID(string inString)
{
    for (int i = 0; i < inString.size(); ++i)
    {
        if (inString[i] < 48 || inString[i] > 57)
        {
            cerr << "ERROR: generateID() fail" << endl;
            return -1;
        }
    }

    int id = 0;
    int placeBuffer = 1;
    for (int i = inString.size() - 1; i >= 0; --i)
    {
        int digit = inString[i] - 48;
        id += digit * placeBuffer;
        placeBuffer *= 10;
    }
    
    return id;
}

void displayGame(Game &inGame)
{
    cout << "Title: " << inGame.name << endl;
    cout << "Platform: " << inGame.platform << endl;
    cout << "Format: " << inGame.format << endl;
    cout << "Completion: " << inGame.completion << endl;
    cout << "Priority: " << inGame.priority << endl;
}

void insertGame(Game &inGame, string &dataBuffer)
{
    ofstream gamesListWrite;
    gamesListWrite.open("data/gameslist.txt");

    gamesListWrite << inGame.id
                   << "$" << inGame.name
                   << "$" << inGame.platform
                   << "$" << inGame.format
                   << "$" << inGame.completion
                   << "$" << inGame.priority << "\n"
                   << dataBuffer;
    gamesListWrite.close();

    ifstream gamesListRead;
    gamesListRead.open("data/gameslist.txt");
    string currentGame;
    dataBuffer.clear();
    while (getline(gamesListRead, currentGame, '\n'))
    {
        dataBuffer += currentGame + "\n";
    }
    gamesListRead.close();
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

