/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
using namespace std;
// you may include more libraries as needed

// declarations for main helper-functions
void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    // Get user input
    bool run = true;
    while(run){
        displayMenu();
        int userInput = 0;

        // For case 3
        string targetCountry;
        string message;

        // For case 4
        string newCountryName;
        string previousCountry;

        cin >> userInput;
        switch(userInput){
            // Build a network
            case 1:
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
                //CountryNet.printPath();
                break;
            // Print Network Path
            case 2:
                CountryNet.printPath();
                break;
            // Transmit Message
            case 3:
                cin.ignore();
                cout << "Enter name of the country to receive the message:" << endl;
                getline(cin, targetCountry);
                cout << "Enter the message to send:" << endl;
                getline(cin, message);
                cout << endl;
                CountryNet.transmitMsg(targetCountry, message);
                break;
            // Add Country
            case 4:
                cin.ignore();
                cout << "Enter a new country name:" << endl;
                getline(cin, newCountryName);
                cout << "Enter the previous country name (or First):" << endl;
                getline(cin, previousCountry);
                if(CountryNet.searchNetwork(previousCountry) == NULL){
                    if(previousCountry == "First"){
                        CountryNet.insertCountry(NULL, newCountryName);
                    }else{
                        cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                        getline(cin, previousCountry);
                        CountryNet.insertCountry(CountryNet.searchNetwork(previousCountry), newCountryName);
                    }
                }else{
                    CountryNet.insertCountry(CountryNet.searchNetwork(previousCountry), newCountryName);
                }
                CountryNet.printPath();
                break;
            // Quit
            case 5:
                run = false;
                cout << "Quitting..." << endl;
                cout << "Goodbye!" << endl;
                break;
        }
    }

    return 0;
}


/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
