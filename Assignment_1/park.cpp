#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Park{
    string parkname;
    string state;
    int area;
};

void addPark(Park parks[], string parkname, string state, int area, int length){
    Park newPark;
    newPark.parkname = parkname;
    newPark.state = state;
    newPark.area = area;
    parks[length] = newPark;
}

void printList(const Park parks[], int length){
    for(int i=0;i<length;i++){
        cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area << endl;
    }
}

int main(int argc, char* argv[]){
    string outputFileName = argv[2];
    int minimumArea = stoi(argv[3]);
    // Read in CSV Data
    ifstream openFile(argv[1]);
    if(!openFile){
        cout << "File open failed" << endl;
    }
    string line;
    Park parks[100];

    // Parse CSV Data
    string parkname;
    string state;
    string area;
    int parkCount = 0;
    while(getline(openFile, line)){
        stringstream ss(line);
        getline(ss, parkname, ',');
        getline(ss, state, ',');
        getline(ss, area, ',');
        int iArea = stoi(area);
        addPark(parks, parkname, state, iArea, parkCount);
        parkCount++;
    }

    // Print out parsed data
    printList(parks, parkCount);

    // Open a csv file
    ofstream outFile;
    outFile.open(outputFileName);
    string output;
    // Output parks where the area is more than the min area
    for(int i=0;i<parkCount;i++){
        if(parks[i].area > minimumArea){
            
            output = parks[i].parkname + ',' + parks[i].state + ',' + to_string(parks[i].area) + '\n';
            outFile << output;
        }
    }

    openFile.close();
}