/********************************************************
CS200 Lab 4
 
                Maze Implementation File
 
 Writen by  : Denise Byrnes
 Modified by: Khoa Ngyuen, Eifu Tomita, Avi Vajpeyi
 
 
 Purpose    : Contains the implementation of the various
 data structures and functions, like creating the equivalency 
 lists, and unions, that we need to create the maze.
 
********************************************************/

#include "Maze.h"
#include <iostream>

using namespace std;

//Constructs inital maze with all walls intact
Maze::Maze() {
    myGraph = new DrawGraph(NUM_CELLS_PER_SIDE);
    
    srand (time(NULL));
    buildEquivClasses();							//initial set of classes
    unionFind();									//condense classes - used to remove maze walls
}

//Maze destructor
Maze::~Maze(){
	delete myGraph;
}

//randomly select an east or south wall
int Maze::selectWall(int row,int col) {
	 // This gives us current cell vertex number
    int cellID = row * NUM_CELLS_PER_SIDE + col;
    
    if ( (row == NUM_CELLS_PER_SIDE-1) && (col == NUM_CELLS_PER_SIDE-1)) {
        return -1;	//Error code bc this is the finish cell
    }

    else if (row == NUM_CELLS_PER_SIDE-1) {
		 // either gives -1 (invalid) or 0 (east wall)
        int choice = rand() % 2 ;
        return choice == 1 ? cellID+1 : -1 ;
    }
	
    else if ( col == NUM_CELLS_PER_SIDE-1) {
        int choice =  rand() % 2;
        return choice == 1 ? cellID + NUM_CELLS_PER_SIDE : -1;
    }

	else {
        int choice = rand()%2;  //// no invalid choice,,  just east or south
        return choice == 1 ? cellID + 1 : cellID + NUM_CELLS_PER_SIDE;
        /* choice can be either 1 or 0.
         when choice is 1, east
         when choice is 0, south.
         */
    }

//    return -1;	//have to return something for last row, last column (no connection)
} 

//performs the union find algorithm - cells with adjacent walls are placed in the
//same equivalence class. This continues until a single class remains containing start
//and finish cells => maze has a path from start to finish.
void Maze::unionFind() {
	int n = NUM_CELLS_PER_SIDE;
	srand(time(NULL));
	
	while (classRep[0] != classRep[n * n - 1]) {
		int row = rand() % n;
		int col = rand() % n;
		int neighborID = selectWall(row, col);
		int cellID = row * NUM_CELLS_PER_SIDE + col;
		if ( neighborID != -1 && classRep[cellID] != classRep[neighborID]) {
			myGraph -> addEdge(cellID, neighborID);

			int max = classRep[cellID], min = classRep[neighborID];
			if (classRep[cellID] < classRep[neighborID]) {
				max = classRep[neighborID];
				min = classRep[cellID];
			}
				
			for (int i = 0; i < n * n; i++) {
				if (equivalenceClasses[max][i] == true) {
					equivalenceClasses[min][i] = true;
					classRep[i] = min;
				}
			}
												
			equivalenceClasses[max].erase(equivalenceClasses[max].begin(),
										  equivalenceClasses[max].end());
		}
	}
}

//Constructs initial equivalence classes, each vertex in its own class
void Maze::buildEquivClasses() {
	// Bool matrix of EquivClasses
	int n = NUM_CELLS_PER_SIDE;
	vector<bool> row;

	for (int i = 0; i < n * n; i++) {
		row.push_back(false);
		classRep[i] = i; 	// Array of Class Representatives for the vertices
	}

	for (int i = 0; i < n * n; i++) {
		equivalenceClasses.push_back(row);
		equivalenceClasses[i][i] = true;
	}
}

//Draws initial maze with no walls removed
void Maze::drawInitWalls()
{
    // horizontal lines
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i=0; i <= NUM_CELLS_PER_SIDE; i++){
        glVertex2d(OFFSET, i*CELL_WIDTH + OFFSET);
        glVertex2d(CELL_WIDTH*NUM_CELLS_PER_SIDE + OFFSET,i*CELL_WIDTH + OFFSET);
    }
    // vertical lines
    for (int i=0; i <= NUM_CELLS_PER_SIDE; i++){
        glVertex2d(i*CELL_WIDTH + OFFSET, OFFSET);
        glVertex2d(i*CELL_WIDTH + OFFSET,CELL_WIDTH*NUM_CELLS_PER_SIDE + OFFSET);
    
    }
    glEnd();
    
    //character start and finish
    glColor3f (0.0, 0.0, 0.0);
    glRasterPos2d(OFFSET - 10, NUM_CELLS_PER_SIDE*CELL_WIDTH-10 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'S');
    glRasterPos2d(NUM_CELLS_PER_SIDE*CELL_WIDTH + OFFSET + 5,
                  5 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'F');
    
    glutSwapBuffers();
    
}


//Draws  maze with  walls removed
void Maze::drawMaze()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    
    //draw outer walls
    glBegin(GL_LINES);
    glVertex2d(OFFSET, OFFSET);
    glVertex2d(OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE, OFFSET);
    glVertex2d(OFFSET, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    glVertex2d(OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    glVertex2d(OFFSET , OFFSET);
    glVertex2d(OFFSET, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    glVertex2d(OFFSET+ CELL_WIDTH * NUM_CELLS_PER_SIDE , OFFSET);
    glVertex2d(OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE, OFFSET + CELL_WIDTH * NUM_CELLS_PER_SIDE);
    
    //draw inner walls based on adjacency list
    vector<vector<int> > adjMatrix = myGraph->get();
    
    for (int i=0; i < adjMatrix.size() - 1; i++) {
        
        vector<int> list = adjMatrix[i];
		
        //all walls intact, i.e list.size() == 0
        if(list.size() == 0)
        {
            //draw south wall
            int vertex = i;
            int row = vertex / NUM_CELLS_PER_SIDE;
            int col = vertex % NUM_CELLS_PER_SIDE;
            if((row+1) % NUM_CELLS_PER_SIDE == 0) continue;
            
            int x = OFFSET + (col) * CELL_WIDTH;
            int y = W_HEIGHT - (OFFSET + (row+1) * CELL_WIDTH);
            int x2 = OFFSET + (col+1) * CELL_WIDTH;
            glVertex2d(x, y);
            glVertex2d(x2, y);
                
            
            //draw east wall
            vertex = i + NUM_CELLS_PER_SIDE;
            row = vertex / NUM_CELLS_PER_SIDE;
            col = vertex % NUM_CELLS_PER_SIDE;
            if((col+1) % NUM_CELLS_PER_SIDE == 0) continue;
                
            x = OFFSET + (col+1) * CELL_WIDTH;
            y = W_HEIGHT - (OFFSET + (row-1) * CELL_WIDTH);
            int y2 = W_HEIGHT - (OFFSET + (row) * CELL_WIDTH);
            glVertex2d(x, y);
            glVertex2d(x, y2);
            
        }
            
        else if(list.size() < 2) {
            
        for(int j = 0; j < list.size(); j++) {
            int vertex = list[j];
            int row = vertex / NUM_CELLS_PER_SIDE;
            int col = vertex % NUM_CELLS_PER_SIDE;
            
            if(vertex == (i + 1)) {//east wall removed, draw south wall
                if((row+1) % NUM_CELLS_PER_SIDE == 0) continue;
                
                int x = OFFSET + (col-1) * CELL_WIDTH;
                int y = W_HEIGHT - (OFFSET + (row+1) * CELL_WIDTH);
                int x2 = OFFSET + (col) * CELL_WIDTH;
                glVertex2d(x, y);
                glVertex2d(x2, y);
                
            }
            else {//south wall removed, draw east wall
                if((col+1) % NUM_CELLS_PER_SIDE == 0) continue;
                
                int x = OFFSET + (col+1) * CELL_WIDTH;
                int y = W_HEIGHT - (OFFSET + (row-1) * CELL_WIDTH);
                int y2 = W_HEIGHT - (OFFSET + (row) * CELL_WIDTH);
                glVertex2d(x, y);
                glVertex2d(x, y2);
            }
          }
        }
    }
    
    glEnd();
    
    //character start and finish
    glColor3f (0.0, 0.0, 0.0);
    glRasterPos2d(OFFSET - 10, NUM_CELLS_PER_SIDE*CELL_WIDTH-10 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'S');
    glRasterPos2d(NUM_CELLS_PER_SIDE*CELL_WIDTH + OFFSET + 5,
                  5 + OFFSET);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'F');
    
    glutSwapBuffers();

}

//Draws path thru maze from stack entries
void Maze::drawPath()
{
    //Clear drawing buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    //redraw maze
    drawMaze();
    
    //find path and place in depth first stack
    stack<int> dfS = myGraph->depthFirstSearch(START_CELL, STOP_CELL);

    //blue boxes for path
    glColor3f (0.0, 0.0, 1.0);
    int row, col, cell;
    
    //since path in reverse order, easier to place stack
    // into a vector
    vector<int> temp;
    while(!dfS.empty()){
        cell = dfS.top();
        dfS.pop();
        temp.push_back(cell);
    }
    
    //for each cell in path
    for(int i = temp.size() - 1; i >= 0; i--){
        cell = temp[i];
        
        //find row/col for cell
        row = cell / NUM_CELLS_PER_SIDE;
        col = cell % NUM_CELLS_PER_SIDE;
        
        //draw a blue rectangle for cell in path
        glRectd(OFFSET + col * CELL_WIDTH + 2,
                W_HEIGHT - (OFFSET + row * CELL_WIDTH + 2),
                OFFSET + col * CELL_WIDTH + CELL_WIDTH - 2,
                W_HEIGHT - (OFFSET + row * CELL_WIDTH + CELL_WIDTH - 2));
        
    }
    
    //draw the new buffer contents
    glutSwapBuffers();
}
