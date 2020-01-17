/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    head = NULL;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    if(head == NULL){
        head = new Country;
        head->name = countryName;
        head->next = NULL;
        cout << "adding: " << countryName << " (HEAD)" << endl;
    }
    else if(previous == NULL){
        Country* newCountry = new Country;
        newCountry->name = countryName;
        newCountry->next = head;
        head = newCountry;
        cout << "adding: " << countryName << " (HEAD)" << endl; 
    }else{
        Country* newCountry = new Country;
        newCountry->name = countryName;
        newCountry->next = previous->next;
        previous->next = newCountry;
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    }  
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    string countries[6] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    insertCountry(NULL, countries[0]);
    insertCountry(searchNetwork(countries[0]), countries[1]);
    insertCountry(searchNetwork(countries[1]), countries[2]);
    insertCountry(searchNetwork(countries[2]), countries[3]);
    insertCountry(searchNetwork(countries[3]), countries[4]);
    insertCountry(searchNetwork(countries[4]), countries[5]);
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    Country* ptr = head;
    while(ptr != NULL && ptr->name != countryName){
        ptr = ptr->next;
    }
    return ptr;
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    Country* targetCountry = new Country;
    Country* ptr = new Country;
    ptr = head;
    targetCountry = searchNetwork(receiver);
    if(head == NULL){
        cout << "Empty list" << endl;
    }
    else if(targetCountry == NULL){
        cout << "Country not found" << endl;
    }else{
        // Count the messages passing through
        while(ptr->name != targetCountry->name){
            ptr->numberMessages ++;
            cout << ptr->name << " [# messages received: " << ptr->numberMessages << "] received: " << message << endl;
            ptr=ptr->next;
        }
        ptr->numberMessages ++;
        cout << ptr->name << " [# messages received: " << ptr->numberMessages << "] received: " << message << endl;
        targetCountry->message = message;
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    cout << "== CURRENT PATH ==" << endl;
    if(head == NULL){
        cout << "nothing in path" << endl;
    }else{
        Country *currentCountry = head;
        while(currentCountry != NULL){
            cout << currentCountry->name;
            cout << " -> ";
            currentCountry = currentCountry->next;
        }
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
}
