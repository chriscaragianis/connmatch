#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <glpk.h>
#include <string>

using namespace std;
#include "graph_lib/graph.h"
#include "graph_lib/graph_lp.h"
#include "graph_lib/graph_IO.h"
#include "graph_lib/polytope.h"


#define CONN_MATCH 0
#define MAX_CLIQUE 1
#define NUM_VERTICES 50
#define NUM_GRAPHS 1
#define P 0.41
#define A1_1 0
#define A1_2 1
#define A2_1 2
#define A2_2 3
#define A3_1 4
#define A3_2 5
#define A4_1 6
#define A4_2 7
#define A5_1 8
#define A5_2 9


int main()
{	
			
			
			Graph G(NUM_VERTICES, false);
			
			G.insert(Edge(A1_1,A2_1));
			G.insert(Edge(A1_1,A2_2));
			G.insert(Edge(A1_2,A2_1));
			G.insert(Edge(A1_2,A2_2));
			G.insert(Edge(A1_1,A5_1));
			G.insert(Edge(A1_1,A5_2));
			G.insert(Edge(A1_2,A5_1));
			G.insert(Edge(A1_2,A5_2));
			G.insert(Edge(A3_1,A2_1));
			G.insert(Edge(A3_1,A2_2));
			G.insert(Edge(A3_2,A2_1));
			G.insert(Edge(A3_2,A2_2));
			G.insert(Edge(A3_1,A4_1));
			G.insert(Edge(A3_1,A4_2));
			G.insert(Edge(A3_2,A4_1));
			G.insert(Edge(A3_2,A4_2));
			G.insert(Edge(A5_1,A4_1));
			G.insert(Edge(A5_1,A4_2));
			G.insert(Edge(A5_2,A4_1));
			G.insert(Edge(A5_2,A4_2));
			
			printDotFile(G);

}
