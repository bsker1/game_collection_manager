#include <iostream>

using namespace std;

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
        
        switch (choice)
        {
            case 1:
                cout << "View Collection chosen." << endl;
                break;
            case 2:
                cout << "Add Games chosen." << endl;
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
        }
    }
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}