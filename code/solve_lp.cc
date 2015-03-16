using namespace std;
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <glpk.h>
#include "DenseGRAPH.cc"
#include "IO.cc"
#include "Polytope.cc"
#include "specialGraphs.cc"
#include "edgevector.cpp"
#include "randomG.cc"

#define RANDOM '1'
#define PETERSEN '2'
#define BY_MATRIX '3'

/********************************************
  CODE ASSUMES EDGE LIST IS LEX ORDERED.
  MAYBE SHOULD WRITE A FUNCTION THAT DOES THAT
*********************************************/

int main (int argc, char *argv[]) {

	//parse command line
	//char t = *argv[1];
	//if (t == RANDOM) {return 0;} //to do
	//if (t == BY_MATRIX) {return 0;} //to do

	//For now, assuming that we are working on Petersen graph

	//G_IS_PETERSEN;

	//Now lets try it random
	DenseGRAPH G(10, false);
	randG(G, 40);
	vector <Edge> edgeList = edges(G);
	vector <double> solution = solve_GLPK(G);
	for (int i = 1; i <= solution.size(); i++ )
		{
			cout << "x" << i << " = " << solution[i-1] << endl;
		}
    printDotFile(G, solution);

}
