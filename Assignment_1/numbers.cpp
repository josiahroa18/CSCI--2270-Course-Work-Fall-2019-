#include <iostream>
#include <fstream>
using namespace std;

int insertIntoSortedArray(int myArray[], int numEntries, int newValue){
    int i = 0;
    // Locate where we should store i
    while(newValue > myArray[i]){
        if(i == numEntries){
            break;
        }
        i ++;
    }
    // Shift all elements to the right so we can store newValue into i
    for(int j=numEntries;j>i;j--){
        myArray[j] = myArray[j-1];
    }
    myArray[i] = newValue;
    numEntries ++;
    //Print out insertions
    for(int k=0;k<numEntries;k++){
        if(k<numEntries && k!=0){
            cout << ',';
        }
        cout << myArray[k];
    }
    cout << endl;
    return numEntries;
}

int main(int argc, char* argv[]){
    int numbers[100];
    // Open file
    ifstream openFile(argv[1]); 
    if(!openFile){
        cout << "Failed to open the file." << endl;
    }
    // Read in lines from the file
    string line;
    int arraySize = 0;
    while(getline(openFile, line)){
        int x = stoi(line);
        arraySize = insertIntoSortedArray(numbers, arraySize, x);
    }
}
