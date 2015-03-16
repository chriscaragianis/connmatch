#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <glpk.h>
#include <string>

using namespace std;
#include "../graph_lib/DenseGRAPH.cc"
#include "../graph_lib/IO.cc"
//#include "../graph_lib/graph_lp.cc"
#include "../graph_lib/specialGraphs.cc"
#include "../graph_lib/edgetools.cc"
#include "../graph_lib/randomG.cc"


#define NUM_VERTICES 12
#define NUM_GRAPHS 20
int main()
{
    
    for (int i = 0; i < NUM_GRAPHS; i++)
		{
			DenseGRAPH G(NUM_VERTICES, false);
			randomMTF(G);
			complement(G);
			cout << (float) minDegree(G) / NUM_VERTICES << endl;
			~G();
		}
    return 0;
}
