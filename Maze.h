/********************************************************
 CS200 Lab 4
 
                    Maze Header File
 
 Writen by  : Denise Byrnes
 Modified by: Khoa Ngyuen, Eifu Tomita, Avi Vajpeyi
 
 
 Purpose    : Contains the varous data structure
 declarations and function prototyes that we need to 
 create the maze.
 
 ********************************************************/

#ifndef Maze_h
#define Maze_h

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif


#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include "DrawGraph.h"

using namespace std;

class Maze {
    public:
//        const int NUM_CELLS_PER_SIDE = 40;
        const int CELL_WIDTH = 10;
        const int OFFSET = 50;
        const int START_CELL = 0;
        const int STOP_CELL = NUM_CELLS_PER_SIDE * NUM_CELLS_PER_SIDE - 1;
        const int W_HEIGHT = NUM_CELLS_PER_SIDE *CELL_WIDTH + 2 * OFFSET;
        const int W_WIDTH = W_HEIGHT;
    
    //Constructs inital maze with all walls intact
    Maze();
    //Destroys the maze
    ~Maze();
    //Constructs initial equivalence classes, each vertex (cell) in its own class
    void buildEquivClasses();
    //Performs union-find algorithm as walls are removed from maze,
    //edges are added to adjacenct matrix. Condenses equivalence classes
    //until start vertex and stop vertex in same equivalence class
    void unionFind();
    //Randomly select an east or south wall
    int selectWall(int row,int col);
    //Draw the initial maze with all walls intact
    void drawInitWalls();
    //Draw the maze
    void drawMaze();
    //Draw the path through the maze
    void drawPath();
    
    private:
    
        DrawGraph *myGraph;							//graph holding adjacency info
        vector<vector<bool> > equivalenceClasses;	//stores equiv. classes
        stack<int> dfS;								//stack holds path thru maze
		int classRep[NUM_CELLS_PER_SIDE * NUM_CELLS_PER_SIDE]; // stores class representatives
};

#endif /* Maze_h */
