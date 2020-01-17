#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct wordItem{
    string word;
    int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]){
    ifstream ignoreWordsFile(ignoreWordFileName);
    if(!ignoreWordsFile){
        cout << "Failed to open " << ignoreWordFileName << endl;
    }
    string word;
    int i = 0;
    while(getline(ignoreWordsFile, word)){
        ignoreWords[i] = word;
        i++;
    }
    ignoreWordsFile.close();
}

bool isStopWord(string word, string ignoreWords[]){
    for(int i=0;i<50;i++){
        if(word == ignoreWords[i]){
            return true;
        }
    }
    return false;
}

void doubleArraySize(wordItem *&arrayPtr, int &size){
    int newSize = size*2;
    wordItem *tempArray = new wordItem[newSize];
    for(int i=0;i<size;i++){
        tempArray[i] = arrayPtr[i];
    }
    delete[] arrayPtr;
    arrayPtr = tempArray;
    size = newSize;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length){
    int count = 0;
    for(int i=0;i<length;i++){
        count += uniqueWords[i].count;
    }
    return count;
}

void arraySort(wordItem uniqueWords[], int length){
    for(int i=0;i<length;i++){
        int maxIndex = i;
        for(int j=i+1;j<length;j++){
            if(uniqueWords[j].count > uniqueWords[maxIndex].count){
                maxIndex = j;
            }
        }
        wordItem tempItem = uniqueWords[maxIndex];
        uniqueWords[maxIndex] = uniqueWords[i];
        uniqueWords[i] = tempItem;
    }
}

void printNext10(wordItem uniqueWords[], int N, int totalNumWords){
    cout << "Probability of next 10 words from rank " << N << endl;
    cout << "---------------------------------------" << endl;
    float probability;
    int precisionValue = 4;
    for(int i=N;i<N+10;i++){
        probability = (float)uniqueWords[i].count/totalNumWords;
        cout << setprecision(4) << fixed << probability << " - " << uniqueWords[i].word << endl;
    }
}

int main(int argc, char* argv[]){
    if(argc != 4){
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt" << endl;
        return 0;
    }
    int N = stoi(argv[1]);
    string openFileName = argv[2];
    const char *ignoreWordFileName = argv[3];
    string ignoreWords[50];
    getStopWords(ignoreWordFileName, ignoreWords);

    // Read words from TomSawyer.txt and store unique words into an array of wordItems
    int size = 100;
    wordItem *uniqueWords = new wordItem[size];

    ifstream tomSawyerText(openFileName);
    if(!tomSawyerText){
        cout << "Failed to open" << endl;
        return 0;
    }
    string line;
    string word;
    int uniqueWordCount = 0;
    int timesDoubled = 0;
    while(getline(tomSawyerText, line)){
        stringstream ss(line);
        while(getline(ss, word, ' ')){
            if(!isStopWord(word, ignoreWords)){
                bool newWord = true;
                for(int i=0;i<=uniqueWordCount;i++){
                    if(word == uniqueWords[i].word){
                        uniqueWords[i].count ++;
                        newWord = false;
                    }
                }
                if(newWord){
                    uniqueWords[uniqueWordCount].word = word;
                    uniqueWords[uniqueWordCount].count = 1;
                    uniqueWordCount++;
                }
                // Check to see if the array needs to be doubled
                if(uniqueWordCount == size){
                    doubleArraySize(uniqueWords, size);
                    timesDoubled++;
                }
            }
        }
    }
    arraySort(uniqueWords, uniqueWordCount);
    cout << "Array doubled: " << timesDoubled << endl;
    cout << "#" << endl;
    cout << "Unique non-common words: " << uniqueWordCount << endl;
    cout << "#" << endl;
    cout << "Total non-common words: " << getTotalNumberNonStopWords(uniqueWords, uniqueWordCount) << endl;
    cout << "#" << endl;
    printNext10(uniqueWords, N, getTotalNumberNonStopWords(uniqueWords, uniqueWordCount));
}