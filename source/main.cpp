#include <iostream>
#include <fstream>

#include "utils.h"
#include "Game.h"
#include "save.h"

using namespace std;

void viewCollection();
void addGames();

void selectGame(GameNode*&);

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
    while (true)
    {
        displayTableMargin();
        showGamesList(head);

        int choice = 0;
        cout << "\nSelect an option:\n" << endl;

        cout << "\t1) Select Game\n"
             << "\t2) Filter Games\n"
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
                selectGame(head);
                break;
            case 2:
                break;
            case 3:
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

    GameNode* iter = inHead;
    while (true)
    {
        int choice = 1;
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
        iter = inHead;
        while (index < choice && iter != nullptr)
        {
            if (iter->display)
                ++index;
            if (index != choice)
                iter = iter->nextGame;
        }
        if (iter == nullptr)
        {
            cerr << "ERROR: invalid choice" << endl;
            clearBuffer();
            continue;
        }

        cout << iter->game.name << " was chosen." << endl;
        cin.get();

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