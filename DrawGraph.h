/********************************************************
 CS200 Lab 4
 
 Draw-Graph Header File
 
 Writen by  : Denise Byrnes
 Modified by: Khoa Ngyuen, Eifu Tomita, Avi Vajpeyi
 
 
 Purpose    : Here we declare the various functions that
 are required to create the graphs, and the functions that
 traverse the biderectional list to create the path of the
 maze.
 
 ********************************************************/

#ifndef DrawGraph_h
#define DrawGraph_h

#include <iostream>
#include <vector>
#include <stack>
#include <list>

#define NUM_CELLS_PER_SIDE 40

using namespace std;

class DrawGraph{
    public:
//        const int NUM_CELLS_PER_SIDE = 40;
		
        //Creates an empty initial adjacency list, sets vertices to n*n
        DrawGraph(int n);
		
        //when a maze wall is removed, adds edge to adjacency list
        void addEdge(int v1, int v2);
		
        //Debug: dump graph for inspection
        void printGraph();
        void printGraph2();
		
        //returns a copy of the adjacency list
        vector<vector<int> > get();
        void SearchGraph(); // build udGraph
		
        //Perform the depth-first search of the graph
        stack<int> depthFirstSearch(int start, int end);
    
    private:
		vector<vector<int> > adjMat; // adjacency matrix
        vector<vector<int> > adjList; //stores only outgoing edges
        vector<vector<int> > udGraph; //undirected "bidirectional" graph
        int vertices;
};

#endif /* DrawGraph_h */
