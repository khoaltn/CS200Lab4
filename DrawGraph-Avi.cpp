//
//  DrawGraph.cpp
//  Maze
//
//  Created by Denise Byrnes on 3/13/16.
//  Copyright © 2016 Denise Byrnes. All rights reserved.
//

#include "DrawGraph.h"
#include <iostream>

//Debug: dump graph for inspection
void DrawGraph::printGraph(){
    for(int j = 0; j < adjList.size(); j++)
    
    {
        vector<int> temp = adjList[j];
        cout<< j << ": ";
        for(int i = 0; i < temp.size(); i++)
        
        {
            int val = temp[i];
            cout<< val << " ";
        }
        cout<<endl;
    }
}



/************************************
*           AVI's IDEAS             *
*   for implementation of DrawGrph  *
************************************/

//Construct an empty inital adjacency matrix
DrawGraph::DrawGraph(int n)
{
    this->vertices = n;

    
    for (int i = 0; i < n; i++)
    {
        vector <int> row; // creating an empty row
        for(int j = 0; j < n; j++)
        {
            row.push_back(0);
        }
        
        adjList.push_back(row); // add the row to the main vector
    }

    // creates a vector of  rows of vectors, with each row currently storing only 0


}

//Return a copy of the adjacency matrix
vector<vector<int> > DrawGraph:: get()
{
    return adjList;
}


/************************************
 *           AVI's IDEAS            *
 *   for implementation of addEdge  *
 ************************************/

//Add a graph edge (remove wall on a cell)
void DrawGraph::addEdge(int v1, int v2)
{
    if ( ((v1 > vertices) or (v1 < 0)) || ((v2 > vertices) or (v2 < 0)) )
        cout << "Fool, this is an invalid edge\n";
    else
        adjList[v1 - 1][v2 - 1] = 1; // so that we can keep numbering from 1, 2....n
}



/************************************
 *           AVI's IDEAS            *
 *   for implementation of depSearch*
 ************************************/

//Perform depth-first search of graph
stack<int> DrawGraph ::depthFirstSearch(int start, int end)
{
    stack<int> S;
 
    // Mark all the vertices as not visited
    bool *visited = new bool[vertices];// a bool of all the verticies
    for (int i = 0; i < vertices; i++)
        visited[i] = false;
    

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

o
    return S;
}