#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <bits/stdc++.h> 
using namespace std;

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

void Graph::addEdge(string v1, string v2, int num){
    vertex* V1 = NULL;
    vertex* V2 = NULL;
    // Find the corresponding vertices
    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i]->name == v1){
            V1 = vertices[i];
        }
        if(vertices[i]->name == v2){
            V2 = vertices[i];
        }
    }
    adjVertex newEdge;
    newEdge.weight = num;
    newEdge.v = V2;
    V1->adj.push_back(newEdge);
    newEdge.v = V1;
    V2->adj.push_back(newEdge);
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

void Graph::setAllVerticesUnvisited(){
    for(unsigned int i=0; i<verices.size(); i++){
        vertices[i]->visited = false;
    }
}

void DFT(vertex* currV){
    currV->visited = true;
    cout << currV->name << " --> ";
    for(unsigned int i=0; i<currV->adj.size(); i++){
        if(!currV->adj[i].v->visited){
            DFT(currV->adj[i].v);
        }
    }
}

void Graph::depthFirstTraversal(string sourceVertex){
    setAllVerticesUnvisited();
    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i]->name == sourceVertex){
            DFT(vertices[i]);
        }
    }
    cout << "Done" << endl;
}

vertex* Graph::DijkstraAlgorithm(string start, string end){
    setAllVerticesUnvisited();
    vertex* vStart = NULL;
    vertex* vEnd = NULL;
    vector<vertex*> vList;
    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i]->name == start){
            vStart = vertices[i];
        }
        if(vertices[i]->name == end){
            vEnd = vertices[i];
        }
    }
    vStart->visited = true;
    vList.push_back(vStart);
    int minDistance;
    int distance;
    vertex* vSolved;
    while(!vEnd->visited){
        minDistance = INT_MAX;
        vSolved = NULL;
        for(unsigned int i=0; i<vList.size(); i++){
            for(unsigned int j=0; j<vList[i]->adj.size(); j++){
                if(!vList[i]->adj[j].v->visited){
                    distance = vList[i]->distance + vList[i]->adj[j].weight;
                    if(distance<minDistance){
                        vSolved = vList[i]->adj[j].v;
                        minDistance = distance;
                    }
                }
            }
        }
        vSolved->distance = minDistance;
        vSolved->visited = true;
        vList.push_back(vSolved);
    }
    return vEnd;
}

void Graph::shortestpath(string start, string end){
    vertex* vEnd = NULL;
    vector<vertex*> vList;
    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i]->name == end){
            vEnd = vertices[i];
        }
    }
    vertex* currV = vEnd;
    stack<vertex*> s;
    while(currV != NULL){
        s.push(currV);
        currV = currV->pred;
    }
    while(s.size() > 0){
        cout << s.top()->name << " ";
        s.pop();
    }
    cout << endl;
}