#include "utils.h"

//  Returns an int with the number in a passed string
int strToInt(string inString)
{
    for (int i = 0; i < inString.size(); ++i)
    {
        if (inString[i] < '0' || inString[i] > '9')
        {
            cerr << "ERROR: generateID() fail" << endl;
            return -1;
        }
    }

    int id = 0;
    int placeBuffer = 1;
    for (int i = inString.size() - 1; i >= 0; --i)
    {
        int digit = inString[i] - '0';
        id += digit * placeBuffer;
        placeBuffer *= 10;
    }
    
    return id;
}

//  Converts each character in a string to upper case
void stringUpper(string& inString)
{
    for (int i = 0; i < inString.size(); ++i)
        inString[i] = toupper(inString[i]);
}

//  Clears cin input buffer, for use whenever user inputs
//  fail a determined test
void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//  Prints the margin for the games table
void displayTableMargin()
{
    cout << "\n| Name" << characterBuffer(' ', 47) << "| Platform | Format | Completion | Priority |"
         << "\n|" << characterBuffer('-', 52) << "|" << characterBuffer('-', 10) << "|"
         << characterBuffer('-', 8) << "|" << characterBuffer('-', 12) << "|"
         << characterBuffer('-', 10) << "|\n";
}

//  Returns a string filled with a chosen amount of a chosen
//  character
string characterBuffer(char character, int count)
{
    string result;
    for (int i = 0; i < count; ++i)
        result += character;
    
    return result;
}