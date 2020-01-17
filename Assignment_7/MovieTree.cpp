#include <iostream>
#include "MovieTree.hpp"
using namespace std;

MovieTree::MovieTree(){
    root = NULL;
}

void deleteLL(LLMovieNode* currLL){
    if(currLL->next == NULL){
        delete currLL;
        currLL = NULL;
        return;
    }
    LLMovieNode* temp = currLL;
    currLL = currLL->next;
    delete temp;
    deleteLL(currLL);
}

void deleteTree(TreeNode* curr){
    if(curr == NULL){
        return;
    }
    // Delete LL associated with nodes 
    LLMovieNode* currLL = curr->head;
    if(currLL->next == NULL){
        delete curr->head;
    }else{
        deleteLL(curr->head);
    }
    deleteTree(curr->leftChild);
    deleteTree(curr->rightChild);
    delete curr;
}

MovieTree::~MovieTree(){
    deleteTree(root);
    root = NULL;
}

void printInventory(TreeNode* curr, LLMovieNode* currLL){
    if(curr->leftChild != NULL){
        printInventory(curr->leftChild, curr->leftChild->head);
    }
    cout << "Movies starting with letter: " << curr->titleChar << endl;
    // Print out values in linked list
    while (currLL->next != NULL){
        cout << " >> " << currLL->title << " " << currLL->rating << endl;
     currLL = currLL->next;
    }
    cout << " >> " << currLL->title << " " << currLL->rating << endl;
    if(curr->rightChild != NULL){
        printInventory(curr->rightChild, curr->rightChild->head);
    }
}

void MovieTree::printMovieInventory(){
    if (root == NULL){
        cout << "Tree is empty" << endl;
        return;
    }
    printInventory(root, root->head);
}


// Helper functions for addMovie
LLMovieNode* createLLNode(int ranking, string title, int year, float rating){
    LLMovieNode* newNode = new LLMovieNode(ranking, title, year, rating);
    return newNode;
}

TreeNode* createTreeNode(int ranking, string title, int year, float rating){
    TreeNode* newNode = new TreeNode;
    newNode->titleChar = title[0];
    newNode->head = createLLNode(ranking, title, year, rating);
    return newNode;
}

void addMovieRecursive(int ranking, string title, int year, float rating, TreeNode* curr){
    if(title[0] == curr->titleChar){
        LLMovieNode* currLL = curr->head;
        LLMovieNode* prevLL = NULL;
        LLMovieNode* temp = createLLNode(ranking, title, year, rating);
        while(currLL && title > currLL->title){
            prevLL = currLL;
            currLL = currLL->next;
        }
        if(prevLL == NULL){
            temp->next = curr->head;
            curr->head = temp;
        }else if(prevLL != NULL && currLL != NULL){
            prevLL->next = temp;
            temp->next = currLL;
        }else if(currLL == NULL){
            prevLL->next = temp;
        }
    }else if(title[0] < curr->titleChar){
        if(curr->leftChild != NULL){
            addMovieRecursive(ranking, title, year, rating, curr->leftChild);
        }else{
            curr->leftChild = createTreeNode(ranking, title, year, rating);
        }
    }else if(title[0] > curr->titleChar){
        if(curr->rightChild != NULL){
            addMovieRecursive(ranking, title, year, rating, curr->rightChild);
        }else{
            curr->rightChild = createTreeNode(ranking, title, year, rating);
        }
    }
}

void MovieTree::addMovie(int ranking, string title, int year, float rating){
    if (root == NULL){
        root = createTreeNode(ranking, title, year, rating);
    }else{
        addMovieRecursive(ranking, title, year, rating, root);
    }
}

// deleteMovies helper functions
TreeNode* findTreeNode(string title, TreeNode* curr){
    if(curr == NULL || curr->titleChar == title[0]){
        return curr;
    }
    if(curr->titleChar > title[0]){
        return findTreeNode(title, curr->leftChild);
    }
    return findTreeNode(title, curr->rightChild);
}

void deleteLLNode(string title, LLMovieNode* currLL, LLMovieNode* prevLL, TreeNode* curr){
    LLMovieNode* temp = NULL;
    if(currLL->title == title){
        if(prevLL == NULL){
            temp = currLL;
            curr->head = currLL->next;
            delete temp;
        }else if(prevLL != NULL && currLL != NULL){
            temp = currLL;
            prevLL->next = currLL->next;
            delete temp;
        }else if(currLL == NULL){
            delete prevLL;
        }
        return;
    }
    deleteLLNode(title, currLL->next, currLL, curr);
}

TreeNode* findMin(TreeNode* curr){
    if(curr->leftChild == NULL){
        return curr;
    }
    return findMin(curr->leftChild);
}

TreeNode* deleteTreeNode(TreeNode* curr, LLMovieNode* key){
    if(curr->leftChild == NULL && curr->rightChild == NULL){
        delete curr;
        curr = NULL;
    }else if(curr->leftChild == NULL){
        TreeNode* temp = curr;
        curr->rightChild->parent = curr->parent;
        curr = curr->rightChild;
        delete temp;
    }else if(curr->rightChild == NULL){
        TreeNode* temp = curr;
        curr->leftChild->parent = curr->parent;
        curr = curr->leftChild;
        delete temp;
    }else if(curr->leftChild != NULL && curr->rightChild != NULL){
        TreeNode* temp = curr;
        temp = findMin(curr->rightChild);
        curr->head = temp->head;
        curr->rightChild = deleteTreeNode(curr->rightChild, temp->head);
    }
    return curr;
}

void MovieTree::deleteMovie(string title){
    TreeNode* curr = findTreeNode(title, root);
    if(curr == NULL){
        cout << "Movie: " << title << " not found, cannot delete." << endl;
    }else{
        if(curr->head->next == NULL){
            delete curr->head;
            curr->head = NULL;
            curr = deleteTreeNode(curr, curr->head);
        }else{
            deleteLLNode(title, curr->head, NULL, curr);
        }
    }
}

// Delete movies old code

// void deleteTreeNode(TreeNode* curr){
//     TreeNode* temp = curr;
//     // Case 1 (no children):
//     if(curr->leftChild == NULL && curr->rightChild == NULL){
//         delete curr;
//         curr = NULL;
//     }
//     // Case 2 (no left child)
//     else if(curr->leftChild == NULL){
//         curr = curr->rightChild;
//         delete temp;
//     }
//     // Case 3 (no right child)
//     else if(curr->rightChild == NULL){
//         curr = curr->leftChild;
//         delete temp;
//     }
//     // Case 4 (two children, recursive)
//     // Replace with minimum from right subtree
// }

// TreeNode* curr = root;
//     TreeNode* prev = NULL;
//     // Search BST for corresponding LL head node
//     while(curr != NULL){
//         // Traverse LL for title
//         if(curr->titleChar == title[0]){
//             LLMovieNode* currLL = curr->head;
//             LLMovieNode* prevLL = NULL;
//             // Case 1: head is the LLnode to be deleted
//             if(currLL->title == title){
//                 if(currLL->next == NULL){
//                     delete curr->head;
//                     curr->head = NULL;
//                     // Delete the associated BST node
//                     deleteTreeNode(curr);
//                     return;
//                 }else{
//                     // Possible error
//                     LLMovieNode* temp = curr->head;
//                     curr->head = curr->head->next;
//                     delete temp;
//                     return;
//                 }
//             }
//             // Case 2: Traverse the LL for the title
//             else{
//                 while(currLL != NULL){
//                     prevLL = currLL;
//                     if(currLL->title == title){
//                         // Case 1: Node is at the end of the LL
//                         if(currLL->next == NULL){
//                             delete currLL;
//                             prevLL->next = NULL;
//                             return;
//                         }
//                         // Case 2: Node is in the LL
//                         else{
//                             LLMovieNode* temp = currLL;
//                             prevLL->next = currLL->next;
//                             delete temp;
//                             return;
//                         }
//                     }
//                     currLL = currLL->next;
//                 }
//             }
//             // Tile was not found
//             cout << "Movie: " << title << " not found, cannot delete." << endl;
//             return;
//         }
//         else if(curr->titleChar > title[0]){
//             curr = curr->leftChild;
//         }else{
//             curr = curr->rightChild;
//         }
//     }
//     // Letter doesn't exist in BST which implies title doesn't exist in BST
//     cout << "Movie: " << title << " not found, cannot delete." << endl;



