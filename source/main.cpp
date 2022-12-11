#include <iostream>
#include <fstream>

#include "utils.h"
#include "Game.h"
#include "save.h"

using namespace std;

void viewCollection();
void addGames();

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
    displayTableMargin();
    showGamesList(head);

    dallocList(head);
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