#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Game
{
    int id;
    string name, platform, format, completion, priority;
};

void viewCollection();
void addGames();

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
        cout << "Main Menu\n" << endl;

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
    cout << "viewCollection() called" << endl;
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
        //  Sets new game's ID to next unused ID
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

            if (toupper(choice) == 'N')
                break;
            else
            {
                insertGame(newGame, gameDataBuffer);
                break;
            }
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
            else
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
                   << "$name:" << inGame.name
                   << "$platform:" << inGame.platform
                   << "$format:" << inGame.format
                   << "$completion:" << inGame.completion
                   << "$priority:" << inGame.priority << "\n"
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

