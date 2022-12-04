#include <iostream>

using namespace std;

void menu();
void viewCollection();
void addGames();

void clearBuffer();

int main()
{
    menu();

    return 0;
}

void menu()
{
    int choice = 0;
    while (true)
    {
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
                return;
        }
    }
}

void viewCollection()
{
    cout << "viewCollection() called" << endl;
}

void addGames()
{
    cout << "addGames() called" << endl;
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}