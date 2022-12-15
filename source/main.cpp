#include <iostream>
#include <fstream>
#include <ctime>

#include "utils.h"
#include "Game.h"
#include "save.h"

using namespace std;

void viewCollection();
void addGames();

void selectGame(GameNode*&);
void editGame(Game&);
void deleteGame(GameNode*&, GameNode*&);
void sortGames(GameNode*&);
void filterGames(GameNode*);

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
        
        switch (choice)
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
    GameNode* head = initializeList();
    int gameCount = 0;
    while (true)
    {
        displayTableMargin();
        gameCount = showGamesList(head);

        int choice = 0;
        cout << "\nSelect an option:\n" << endl;

        cout << "\t1) Select Game\n"
             << "\t2) Sort Games\n"
             << "\t3) Filter Games\n"
             << "\t4) Random Game\n"
             << "\t5) Back\n"
             << "\n*__ ";
        cin >> choice;

        if (choice < 1 || choice > 5)
        {
            cerr << "ERROR: invalid choice" << endl;
            clearBuffer();
            continue;
        }
        
        switch (choice)
        {
            case 1:
                selectGame(head);
                break;
            case 2:
                sortGames(head);
                break;
            case 3:
                filterGames(head);
                break;
            case 4:
                randomizeGame(head, gameCount);
                break;
            case 5:
                return;
        }
    }

    dallocList(head);
}

void selectGame(GameNode*& inHead)
{
    if (inHead == nullptr)
    {
        cout << "No games to select!" << endl;
        return;
    }

    GameNode* selectedGame = inHead;
    while (true)
    {
        int choice = 0;
        cout << "\nSelect a game by its number in the list above:\n" << endl;

        cout << "*__ ";
        cin >> choice;
        if (choice < 1)
        {
            cerr << "ERROR: invalid choice" << endl;
            clearBuffer();
            continue;
        }

        int index = 0;
        selectedGame = inHead;
        while (index < choice && selectedGame != nullptr)
        {
            if (selectedGame->display)
                ++index;
            if (index != choice)
                selectedGame = selectedGame->nextGame;
        }
        if (selectedGame == nullptr)
        {
            cerr << "ERROR: invalid choice" << endl;
            clearBuffer();
            continue;
        }

        while (true)
        {
            int choice = 0;
            cout << "\nWhat would you like to do with "
                 << selectedGame->game.name << "?:\n" << endl;

            cout << "\t1) Edit Game\n"
                 << "\t2) Delete Game\n"
                 << "\t3) Back\n"
                 << "\n*__ ";
            cin >> choice;
            if (choice < 1 || choice > 3)
            {
                cerr << "ERROR: invalid choice" << endl;
                clearBuffer();
                continue;
            }

            switch (choice)
            {
                case 1:
                    editGame(selectedGame->game);
                    return;
                case 2:
                    deleteGame(inHead, selectedGame);
                    return;
                case 3:
                    return;
            }
        }

        break;
    }
}

void editGame(Game& inGame)
{
    Game editedGame = enterGameAttributes(inGame.id);
    if (editedGame.id == -1)
    {
        cout << "\nEdit Game aborted." << endl;
        return;
    }

    copyGame(inGame, editedGame);
    editGameInSave(inGame);

    cout << "\nGame edited successfully." << endl;
}

void deleteGame(GameNode*& inHead, GameNode*& selectedGame)
{
    while (true)
    {
        char choice;
        cout << "\nAre you sure you would like to delete\n"
             << selectedGame->game.name << "? (Y/N)\n"
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
        
        cout << "\nDelete Game aborted." << endl;
        return;
    }

    deleteGameInSave(selectedGame->game.id);
    deleteNode(inHead, selectedGame);

    cout << "\nDelete Game successful." << endl;
    return;
}

void sortGames(GameNode*& inHead)
{
    if (inHead == nullptr)
    {
        cout << "\nNo games to sort!" << endl;
        return;
    }

    while (true)
    {
        bool byName = false;
        bool descending = false;
        while (true)
        {
            int choice = 0;
            cout << "\nHow would you like to sort?\n" << endl;

            cout << "\t1) Recently Added\n"
                 << "\t2) Name\n"
                 << "\t3) Back\n"
                 << "\n*__ ";
            cin >> choice;

            if (choice < 1 || choice > 3)
            {
                cerr << "ERROR: invalid choice" << endl;
                clearBuffer();
                continue;
            }

            switch (choice)
            {
                case 1:
                    break;
                case 2:
                    byName = true;
                    break; 
                case 3:
                    cout << "\nSort Games aborted." << endl;
                    return;
            }

            break;
        }

        while (true)
        {
            int choice = 0;
            cout << "\nAscending or descending order?\n" << endl;

            cout << "\t1) Ascending\n"
                 << "\t2) Descending\n"
                 << "\t3) Back\n"
                 << "\n*__ ";
            cin >> choice;

            if (choice < 1 || choice > 3)
            {
                cerr << "ERROR: invalid choice" << endl;
                clearBuffer();
                continue;
            }

            if (choice == 3)
                break;

            switch (choice)
            {
                case 1:
                    break;
                case 2:
                    descending = true;
                    break;
            }

            sortList(inHead, byName, descending);
            return;
        }
    }
}

void filterGames(GameNode* inHead)
{
    while (true)
    {
        int choice = 0;
        cout << "\nWhich filter would you like to apply?\n" << endl;

        cout << "\t1) Clear Filters\n"
             << "\t2) Specific Platform\n"
             << "\t3) Owned Games\n"
             << "\t4) Unplayed Games\n"
             << "\t5) Games To Play\n"
             << "\t6) Backlog Titles\n"
             << "\t7) Back\n"
             << "\n*__ ";
        cin >> choice;

        if (choice < 1 || choice > 7)
        {
            cerr << "ERROR: invalid choice" << endl;
            clearBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                showAllGames(inHead);
                break;
            case 2:
                filterPlatform(inHead);
                break; 
            case 3:
                filterOwned(inHead);
                break;
            case 4:
                filterNew(inHead);
                break;
            case 5:
                filterPlay(inHead);
                break;
            case 6:
                filterBacklog(inHead);
                break;
            case 7:
                return;
        }

        break;
    }
}

void addGames()
{
    while (true)
    {
        Game newGame = enterGameAttributes(getLastID() + 1);
        if (newGame.id == -1)
        {
            cout << "\nAdd Game aborted." << endl;
            return;
        }

        addGameToSave(newGame);
        
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