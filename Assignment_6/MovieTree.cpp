#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST

MovieTree::MovieTree() {
  root = NULL;
}

MovieTree::~MovieTree() {
  
}

// Helper function for printMovieInventory
void printNodes(MovieNode* curr){
  if(curr->left != NULL){
    printNodes(curr->left);
  }
  cout << "Movie: " << curr->title << " " << curr->rating << endl;
  if(curr->right != NULL){
    printNodes(curr->right);
  }
}

void MovieTree::printMovieInventory() {
   if(root == NULL){
     cout << "Tree is Empty. Cannot print" << endl;
   }else{
     printNodes(root);
   }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating){
  MovieNode* temp = new MovieNode(ranking, title, year, rating);
  MovieNode* curr = root;
  MovieNode* prev = NULL;
  while(curr != NULL){
    prev = curr;
    if(title < curr->title){
      curr = curr->left;
    }else{
      curr = curr->right;
    }
  }
  if(root == NULL){
    root = temp;
  }else if(title < prev->title){
    prev->left = temp;
  }else{
    prev->right = temp;
  }
}

// Helper function for findMovie
void findMovieNode(MovieNode* curr, string title){
  if(curr->title == title){
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << curr->ranking << endl;
    cout << "Title  :" << curr->title << endl;
    cout << "Year   :" << curr->year << endl;
    cout << "rating :" << curr->rating << endl;
    return;
  }
  if(title < curr->title){
    if(curr->left == NULL){
      cout << "Movie not found." << endl;
    }else{
      findMovieNode(curr->left, title);
    }
  }else{
    if(curr->right == NULL){
      cout << "Movie not found." << endl;
    }else{
      findMovieNode(curr->right, title);
    }
  }
}

void MovieTree::findMovie(string title) {
  findMovieNode(root, title);
}

// Helper function for queryMovies
void preOrder(MovieNode* curr, float rating, int year){
  if(curr == NULL){
    return;
  }
  if(curr->year > year && curr->rating > rating){
    cout << curr->title << "(" << curr->year << ") " << curr->rating << endl;
  }
  preOrder(curr->left, rating, year);
  preOrder(curr->right, rating, year);
}

void MovieTree::queryMovies(float rating, int year) {
  //write your code
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  preOrder(root, rating, year);
}

// Helper function for averageRating
// Get the sum of the nodes in the tree
float sumOfTree(MovieNode* curr){
  if(curr == NULL){
    return 0;
  }
  return(curr->rating + sumOfTree(curr->left) + sumOfTree(curr->right));
}

// Get the amount of nodes in the tree
int nodeCount(MovieNode* curr){
  int count = 0;
  if(curr){
    count ++;
    count = count + nodeCount(curr->left);
    count = count + nodeCount(curr->right);
  }
  return count;
}

void MovieTree::averageRating() {
  if(root == NULL){
    cout << "Average rating:0.0" << endl;
  }else{
    float sumOfRatings = 0.0;
    int movieCount = 0;
    sumOfRatings = sumOfTree(root);
    movieCount = nodeCount(root);
    float averageRating = sumOfRatings / movieCount;
    cout << "Average rating:" << averageRating << endl;
  }
}
