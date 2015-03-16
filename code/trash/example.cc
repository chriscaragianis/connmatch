using namespace std;
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "DenseGRAPH.cc"
#include "IO.cc"
#include "Polytope.cc"

int main () {
	Edge e_1; e_1.v = 0; e_1.w = 1;
	Edge e_2; e_2.v = 0; e_2.w = 4;
	Edge e_3; e_3.v = 0; e_3.w = 5;
	Edge e_4; e_4.v = 1; e_4.w = 2;
	Edge e_5; e_5.v = 1; e_5.w = 6;
	Edge e_6; e_6.v = 2; e_6.w = 3;
	Edge e_7; e_7.v = 2; e_7.w = 7;
	Edge e_8; e_8.v = 3; e_8.w = 4;
	Edge e_9; e_9.v = 3; e_9.w = 8;
	Edge e_10; e_10.v = 4; e_10.w = 9;
	Edge e_11; e_11.v = 5; e_11.w = 7;
	Edge e_12; e_12.v = 5; e_12.w = 8;
	Edge e_13; e_13.v = 6; e_13.w = 8;
	Edge e_14; e_14.v = 6; e_14.w = 9;
	Edge e_15; e_15.v = 7; e_15.w = 9;
	
	DenseGRAPH G(10, false);
	G.insert(e_1);	
	G.insert(e_2);
	G.insert(e_3);
	G.insert(e_4);	
	G.insert(e_5);
	G.insert(e_6);
	G.insert(e_7);	
	G.insert(e_8);
	G.insert(e_9);
	G.insert(e_10);	
	G.insert(e_11);
	G.insert(e_12);
	G.insert(e_13);	
	G.insert(e_14);
	G.insert(e_15);
		
	IO<DenseGRAPH>::show(G);
	IO<DenseGRAPH>::showAdjMat(G);
	Polytope<DenseGRAPH>::printVertexCondition(G);
	Polytope<DenseGRAPH>::printEdgePairCondition(G);
	Polytope<DenseGRAPH>::printGLPConditions(G);
	Polytope<DenseGRAPH>::printEdgeList(G);
}

