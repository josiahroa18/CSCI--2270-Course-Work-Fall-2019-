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
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty(){
    if(head == NULL){
        return true;
    }
    else{
        return false;
    }
}

/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
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
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    if(isEmpty()){
        cout << "The list is empty" << endl;
    }else{
        Country *ptr = head;
        Country *prev = nullptr;
        while(ptr != NULL){
            if(ptr->name == countryName){
                break;
            }else{
                prev = ptr;
                ptr = ptr->next;
            }
        }
        // Country not found in list
        if(ptr == NULL){
            cout << "Country does not exist." << endl;
        }
        // Country found and node is stored in ptr
        else{
            // Delete head node
            if(head == ptr){
                head = head->next;
            }
            // Delete internal/last node
            else{
                prev->next = ptr->next;
            }
            delete ptr;
        }
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
    deleteEntireNetwork();
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
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName) {
    Country* ptr = head;
    while(ptr != NULL && ptr->name != countryName){
        ptr = ptr->next;
    }
    return ptr;
}

/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork(){
    Country* temp = nullptr;
    if(head==NULL){
        return;
    }
    while(!isEmpty()){
        cout << "deleting: " << head->name << endl;
        temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Deleted network" << endl;
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
void CountryNetwork::rotateNetwork(int n){
    Country *curr = head;
    Country *nthNode = nullptr;
    int count = 1;
    if(isEmpty()){
        cout << "Linked List is Empty" << endl;
    }else{
        //Count the amount of nodes in the linked list
        while(count < n && curr != NULL){
            curr = curr->next;
            count++;
        }
        // If n is bigger than number of nodes in the linked list or smaller than 1
        if(n > count || n < 1){
            cout << "Rotate not possible" << endl;
        }
        // Rotate the linked list
        else{
            nthNode = curr;
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = head;
            head = nthNode->next;
            nthNode->next = NULL;
            cout << "Rotate Complete" << endl;
        }
    }
}

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork(){
    Country *curr = head;
    Country *prev = nullptr;
    Country *next = nullptr;
    while(curr != NULL){
         next = curr->next;
         curr->next = prev;
         prev = curr;
         curr = next;
    }
    head = prev;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
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
