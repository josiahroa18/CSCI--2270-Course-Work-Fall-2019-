#include "MovieTree.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

void displayMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Query movies" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Average Rating of movies" << endl;
    cout << "5. Quit" << endl;
}

void addMovies(MovieTree &BST, string fileName){
    string line;
    string element;
    string array[4];
    int ranking;
    string title;
    int year;
    float rating;
    int i;
    ifstream myFile;
    myFile.open(fileName);
    while(getline(myFile, line)){
        stringstream ss(line);
        i = 0;
        while(getline(ss, element, ',')){
            array[i] = element;
            i++;
        }
        ranking = stoi(array[0]);
        title = array[1];
        year = stoi(array[2]);
        rating = stof(array[3]);
        BST.addMovieNode(ranking, title, year, rating);
    }
    myFile.close();
}

int main(int argc, char* argv[]){
    // Read in file
    string fileName = argv[1];
    MovieTree BST;
    addMovies(BST, fileName);
    int userInput;
    // Case 1
    string title;
    // Case 2
    float minRating;
    int minYear;
    while(true){
        displayMenu();
        cin >> userInput;
        switch(userInput){
            // Find a movie
            case 1:
                cout << "Enter title:" << endl;
                getline(cin >> ws, title);
                BST.findMovie(title);
                break;
            // Query movies
            case 2:
                cout << "Enter minimum rating:" << endl;
                cin >> minRating;
                cout << "Enter minimum year:" << endl;
                cin >> minYear;
                BST.queryMovies(minRating, minYear);
                break;
            // Print inventory
            case 3:
                BST.printMovieInventory();
                break;
            // Average rating of movies
            case 4:
                BST.averageRating();
                break;
            // Quit
            case 5:
                cout << "Goodbye!" << endl;
                return 0;
        }
    }
}