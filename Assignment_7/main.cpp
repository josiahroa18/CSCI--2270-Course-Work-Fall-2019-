#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MovieTree.hpp"
using namespace std;

void displayMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Print the inventory" << endl;
    cout << "2. Delete a movie"<< endl;
    cout << "3. Quit" << endl;
}

int main(int argc, char* argv []){
    MovieTree Movies;
    string fileName = argv[1];
    ifstream myFile;

    // Variables for storing data in BST
    string line, ranking, title, year, rating;
    int rankInt, y;
    float r;

    myFile.open(fileName);
    while(getline(myFile, line)){
        stringstream ss(line);
        getline(ss, ranking, ',');
        if(ranking == ""){
            continue;
        }
        getline(ss, title, ',');
        getline(ss, year, ',');
        getline(ss, rating);
        rankInt = stoi(ranking);
        y = stoi(year);
        r = stof(rating);
        Movies.addMovie(rankInt, title, y ,r);
    }
    myFile.close();

    int userInput;
    string deleteMovie;
    while(true){
        displayMenu();
        cin >> userInput;
        switch(userInput){
            // Print inventory
            case 1:
                Movies.printMovieInventory();
                break;
            // Delete movie
            case 2:
                cout << "Enter a movie title:" << endl;
                getline(cin >> ws, deleteMovie);
                Movies.deleteMovie(deleteMovie);
                break;
            // Quit
            case 3:
                Movies.~MovieTree();
                Movies.printMovieInventory();
                cout << "Goodbye!" << endl;
                return 0;
        }
    }
}