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
    // for(int j = 0; j < udGraph.size(); j++){
    //     vector<int> temp = udGraph[j];
	for (int j = 0; j < adjMat.size(); j++) {
		vector<int> temp = adjMat[j];
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
	vertices = n * n;

	// Adjacency matrix
	vector<int> tmp;
	for (int j = 0; j < n * n; j++) {
		tmp.push_back(0);
	}

	for (int i = 0; i < n * n; i++) {
		adjMat.push_back(tmp);
	}

	// Adjacency list
	vector<int> tmp2;
	for (int i = 0; i < n * n; i++) {
		adjList.push_back(tmp2);
	}
}

//Return a copy of the adjacency matrix
vector<vector<int> > DrawGraph:: get()
{
	return adjList;
}

//Add a graph edge (remove wall on a cell)
void DrawGraph::addEdge(int v1, int v2) {
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
	// ------------------------------ AVI ------------------------------
	stack<int> S;
    
    // Mark all the vertices as not visited
    bool *visited = new bool[vertices];// a bool of all the verticies

    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
	}
    
    stack<int> stack;
    stack.push(start);
    
    // cout << "DFS: ";
    while(!stack.empty())
    {
        int top = stack.top();
        stack.pop();
        
        S.push(top); // saving the value visitied
        visited[top] = true;
        
        
        for(vector<int>::iterator i = adjList[top].begin(); i != adjList[top].end(); i++)
        {
            if (!visited[*i]) // if not visited, push the value onto the stack of the entire list
                stack.push(*i);
        }
    }
    
    
    return S;
}


//Constructs an Undirected Bidirectional Graph based on adjacency list
void DrawGraph::SearchGraph()
{
    
    //printGraph2();
    
}
