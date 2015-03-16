#include <iostream>
#include <time.h>
using namespace std;
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <glpk.h>
#include <string>
#include "../graph_lib/DenseGRAPH.cc"
#include "../graph_lib/IO.cc"
#include "../graph_lib/graph_lp.cc"
#include "../graph_lib/specialGraphs.cc"
#include "../graph_lib/edgetools.cc"
#include "../graph_lib/randomG.cc"


#define NUM_VERTICES 30
#define NUM_GRAPHS 2

int main()
{
    int num = NUM_VERTICES;
    int small_count = 0;
    int non_int_count = 0;
    vector <double> solution;
    double sol_obj_val;
    DenseGRAPH G(NUM_VERTICES, false);
    for (int i = 0; i < NUM_GRAPHS; i++)
        {
            randomMTF(G);
            complement(G);
            //G_IS_PETERSEN;
            solution = solve_with_GLPK(G,false,true,true);cout << "graph " << i << " complete: \t";
           // for (int i = 0; i < solution.size(); i ++) {cout << "x" << i << " = " << solution[i] << ", ";} cout << endl;
            //if (solution[0] < 25) cout << solution[0] << endl;
            //cout << solution[0] << endl;
            if (solution[0] < NUM_VERTICES/2) {cout << "small\n";printDotFile(G, solution);} else {cout << endl;}

        }
    //cout << "\n\n small count = " << small_count << endl;
    //cout << "\n non integral = " << non_int_count << endl;
    return 0;
}
