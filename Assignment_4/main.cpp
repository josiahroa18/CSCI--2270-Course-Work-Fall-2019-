/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    bool run = true;
    int userInput;
    // For Insert Country (Case 3)
    string newCountryName;
    string previousCountry;

    // For Delete Country (Case 4)
    string deleteCountryName;

    // For Rotate Network (Case 6)
    string x;
    int n;

    while(run){
        displayMenu();
        cin >> userInput;
        switch(userInput){
            // Load Default Startup
            case 1:
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
                break;
            // Print Path
            case 2:
                CountryNet.printPath();
                break;
            // Add Country
            case 3:
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
            // Delete Country
            case 4:
                cin.ignore();
                cout << "Enter a country name:" << endl;
                getline(cin, deleteCountryName);
                CountryNet.deleteCountry(deleteCountryName);
                CountryNet.printPath();
                break;
            // Reverse Network
            case 5:
                CountryNet.reverseEntireNetwork();
                CountryNet.printPath();
                break;
            // Rotate Network
            case 6:
                cin.ignore();
                cout << "Enter the count of values to be rotated:" << endl;
                getline(cin, x);
                n = stoi(x);
                CountryNet.rotateNetwork(n);
                CountryNet.printPath();
                break;
            // Clear Network
            case 7:
                cout << "Network before deletion" << endl;
                CountryNet.printPath();
                CountryNet.deleteEntireNetwork();
                cout << "Network after deletion" << endl;
                CountryNet.printPath();
                break;
            // Exit program
            case 8:
                cout << "Quitting... cleaning up path: " << endl;
                CountryNet.printPath();
                CountryNet.deleteEntireNetwork();
                if(CountryNet.isEmpty()){
                    cout << "Path cleaned" << endl;
                }else{
                    cout << "Error: Path NOT cleaned" << endl;
                }
                cout << "Goodbye!" << endl;
                run = false;
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
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
