#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <glpk.h>
#include <string>

//using namespace std;
#include "../graph_lib/graph.h"
#include "../graph_lib/graph_lp.h"
#include "../graph_lib/graph_IO.h"
#include "../graph_lib/polytope.h"


#define CONN_MATCH 0
#define MAX_CLIQUE 1
#define NUM_VERTICES 51
#define NUM_GRAPHS 1
#define P 0.41

int main()
{	

	srand ( time(NULL) );
	cout << "yobibby\n" ;
	Graph G(NUM_VERTICES, false);
	for (int i = 0; i < NUM_GRAPHS; i++)
			{			
				randomMTF(G);
				//if (!isBipartite(G)) {i--; cout << "BIP\n";continue;}				
				//cout << i << "\t" << maxDegree(G) << "\n";
				 
				
				//if (maxDegree(G) > NUM_VERTICES/4) {i--; cout << "DEG\n"; continue;} 
				//complement(G);
				printDotFile(G);				
				int c = conn_match_num(G);
				//polyFile(G);
				
				
			}
}
