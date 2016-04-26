//
//  DrawGraph.cpp
//  Maze
//
//  Created by Denise Byrnes on 3/13/16.
//  Copyright © 2016 Denise Byrnes. All rights reserved.
//

#include "DrawGraph.h"
#include <iostream>
#include <algorithm>

using namespace std;

//Debug: dump graph for inspection
void DrawGraph::printGraph(){
    for(int j = 0; j < adjList.size(); j++){
        vector<int> temp = adjList[j];
        cout<< j << ": ";
        for(int i = 0; i < temp.size(); i++) {
            int val = temp[i];
            cout<< val << " ";
        }
        cout<<endl;
    }
}

void DrawGraph::printGraph2(){
     for(int j = 0; j < udGraph.size(); j++){
         vector<int> temp = udGraph[j];
	        cout<< j << ": ";
        for(int i = 0; i < temp.size(); i++) {
            int val = temp[i];
            cout<< val << " ";
        }
        cout<<endl;
    }
}

//Construct an empty inital adjacency matrix
DrawGraph::DrawGraph(int n) {
	// Num vertices 

    
	vertices = n*n;

	// Adjacency matrix
	vector<int> tmp;
	for (int j = 0; j < vertices; j++)
    {
		tmp.push_back(0);
	}

	for (int i = 0; i < vertices; i++)
    {
		adjMat.push_back(tmp);
	}

	// Adjacency list

	vector<int> tmp2;
	for (int i = 0; i < vertices; i++) {
		adjList.push_back(tmp2);

	}
}

//Return a copy of the adjacency matrix
vector<vector<int> > DrawGraph:: get()
{
	return adjList;
}

//Add a graph edge (remove wall on a cell)
void DrawGraph::addEdge(int v1, int v2)

{
	if (0 <= v1 && v1 < (vertices * vertices)
		&& 0 <= v2 && v2 < (vertices * vertices) // v1, v2 are valid
		&& adjMat[v1][v2] == 0) { // v1, v2 are not already neighbors
		// Find row and column indices of v1 and v2
		
		
		// Fix adjacency matrix
		adjMat[v1][v2] = 1;
		adjMat[v2][v1] = 1;
	
		// Fix adjacency list
		if (v1 < v2) {
			adjList[v1].push_back(v2);
		}
		else {
			adjList[v2].push_back(v1);
		}
	}
}

//Perform depth- first search of graph
stack<int> DrawGraph ::depthFirstSearch(int start, int end) {
    
    // stack<int> S;
    // SearchGraph();
    
    // return S;
	
	stack<int> saveStack;

    
    // Mark all the vertices as not visited
    bool *visited = new bool[vertices];// a bool of all the verticies

    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
	}
    
    stack<int> tempStack;
    tempStack.push(start);
    
    while(!tempStack.empty())
    {
        int top = tempStack.top();
        tempStack.pop();
        
        // what is the int start = 0?
        saveStack.push(top); // saving the value visitied
        
        
        if (visited[top] != true)
        {
            // if not visited, push the value onto the stack of the entire list
            visited[top] = true;
            
            
            // use uD graph here instead of adjList
            for(vector<int>::iterator i = adjList[top].begin(); i != adjList[top].end(); i++)
            {
                    tempStack.push(*i);
                
            }
        }
        
    }
    // problem with this is that we are saving even the places that we done eed to visit
    // need to edit so that we check if with the graph, we are reaching the end from the tempStackPush
    
    return saveStack;
}



//Constructs an Undirected Bidirectional Graph based on adjacency list
void DrawGraph::SearchGraph()
{
    /*
     We will polulate the udGraph
     
     int adjList
     0 -> 1 add the 1-> =0
     
     */
    
    
    for (int i = 0; i < vertices; i++)
    {
        udGraph[i] = adjList[i];
    }
    
    
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j< adjList[i].size(); j++)
        {
            if (adjList[i][j] > i)
            {
                udGraph[j].push_back(i);
            }
            
        }
    }
    
    
    printGraph2();
    
    
    
    
}































