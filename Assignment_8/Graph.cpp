#include <iostream>
#include <vector>
#include <queue>
#include "Graph.hpp"
using namespace std;

void Graph::addEdge(string v1, string v2){
    vertex* V1 = NULL;
    vertex* V2 = NULL;
    for(int i=0; i<vertices.size(); i++){
        if(vertices[i]->name == v1){
            V1 = vertices[i];
        }
        if(vertices[i]->name == v2){
            V2 = vertices[i];
        }
    }
    adjVertex newEdge;
    newEdge.v = V2;
    V1->adj.push_back(newEdge);
    newEdge.v = V1;
    V2->adj.push_back(newEdge);
}

void Graph::addVertex(string name){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == name){
            found = true;
        }
    }
    if (found == false){
        vertex* newV = new vertex;
        newV->name = name;
        vertices.push_back(newV);
    }
}

void Graph::displayEdges(){
    for(unsigned int i=0; i<vertices.size(); i++){
        cout << vertices[i]->name << " --> ";
        for(unsigned int j=0; j<vertices[i]->adj.size();j++){
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vertex* vStart = NULL;
    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i]->name == sourceVertex){
            vStart = vertices[i];
            vStart->visited = true;
            vStart->distance = 0;
            break;
        }
    }
    cout << "Starting vertex (root): " << vStart->name << "-> ";
    queue<vertex*> q;
    vertex* currV = NULL;
    q.push(vStart);
    while(q.size() > 0){
        currV = q.front();
        q.pop();
        for(unsigned int i=0; i < currV->adj.size(); i++){
            if(!currV->adj[i].v->visited){
                currV->adj[i].v->visited = true;
                currV->adj[i].v->distance = currV->distance + 1;
                cout << currV->adj[i].v->name << "(" << currV->adj[i].v->distance << ")" << " ";
                q.push(currV->adj[i].v);
            }
        }
    }
}

// getConnectedComponents helper function
void BFTraverseGraph(vertex* startV){
    queue<vertex*> q;
    vertex* currV = NULL;
    q.push(startV);
    while(q.size() > 0){
        currV = q.front();
        q.pop();
        for(unsigned int i=0; i < currV->adj.size(); i++){
            if(!currV->adj[i].v->visited){
                currV->adj[i].v->visited = true;
                q.push(currV->adj[i].v);
            }
        }
    }
}

int Graph::getConnectedComponents(){
    int numSubGraphs = 0;
    for(unsigned int i=0; i<vertices.size(); i++){
        if(!vertices[i]->visited){
            BFTraverseGraph(vertices[i]);
            numSubGraphs ++;
        }
    }
    return numSubGraphs; 
}

// checkBipartite helper function
bool colorGraph(vertex* startV){
    startV->color = "red";
    startV->visited = true;
    queue<vertex*> q;
    vertex* currV = NULL;
    q.push(startV);
    while(q.size() > 0){
        currV = q.front();
        q.pop();
        for(unsigned int i=0; i<currV->adj.size(); i++){
            if((currV->color == "red" && currV->adj[i].v->color== "red") || (currV->color == "blue" && currV->adj[i].v->color== "blue")){
                return false;
            }
            if(!currV->adj[i].v->visited){
                currV->adj[i].v->visited = true;
                if(currV->color == "red"){
                    currV->adj[i].v->color = "blue"; 
                }else{
                    currV->adj[i].v->color = "red"; 
                }
                q.push(currV->adj[i].v);
            }
        }
    }
    return true;
}

bool checkGraph(vertex* startV){
    queue<vertex*> q;
    vertex* currV = NULL;
    q.push(startV);
    while(q.size()>0){
        currV = q.front();
        q.pop();
        for(unsigned int i=0; i < currV->adj.size(); i++){
            if((currV->color == "red" && currV->adj[i].v->color== "red") || (currV->color == "blue" && currV->adj[i].v->color== "blue")){
                return false;
            }
        }
    }
    return true;
}

bool Graph::checkBipartite(){
    bool bipartite = true;
    // Color the graph
    for(unsigned int i=0; i<vertices.size(); i++){
        if(!vertices[i]->visited){
            bipartite = colorGraph(vertices[i]);
            if(bipartite == false){
                return false;
            }
        }
    }
    // Check the graph
    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i]->visited){
            bipartite = checkGraph(vertices[i]);
        }
    }
    // Return
    if(bipartite == true){
        return true;
    }else{
        return false;
    }
}

// vertex* startV = vertices[0];
//     startV->color = "red";
//     startV->visited = true;
//     queue<vertex*> q;
//     vertex* currV = NULL;
//     q.push(startV);
//     while(q.size() > 0){
//         currV = q.front();
//         q.pop();
//         for(unsigned int i=0; i < currV->adj.size(); i++){
//             if((currV->color == "red" && currV->adj[i].v->color== "red") || (currV->color == "blue" && currV->adj[i].v->color== "blue")){
//                 return false;
//             }
//             if(!currV->adj[i].v->visited){
//                 currV->adj[i].v->visited = true;
//                 if(currV->color == "red"){
//                     currV->adj[i].v->color = "blue";
//                 }else{
//                     currV->adj[i].v->color = "red";
//                 }
//                 q.push(currV->adj[i].v);
//             }
//         }
//     }
//     return true;