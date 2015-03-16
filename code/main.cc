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
#define NUM_VERTICES 80
#define NUM_GRAPHS 1
#define P 0.41
int binom4(int x)
{	
	return x*(x-1)*(x-2)*(x-3)/24;
	
}

int main()
{	
			srand ( time(NULL) );

			/*int count = 0;
			//Graph G(NUM_VERTICES, false);
			//bool flag = true;
			while (flag)
			{
				count++;
				randomMTF(G);
				flag = isBipartite(G);
			}
			complement(G);
			showAM(G);cout << "\n Count : " << count << "\n"; 
			//complement(*G);
			//int a = conn_match_num(G);
		    //cout << sol[0] << endl;
			//if (sol[0] < NUM_VERTICES / 2) break;

			vector <double> sols = solve_lp(G, CONN_MATCH, true,false);
            //cout << sols[0] << "\t" << sols[1] << endl;
            //sols.erase(sols.begin(), sols.begin()+2);
            printDotFile_cm(G, sols);
            //for (int i = 0; i < sols.size(); i++)
              //  cout << sols[i] << "\t";
            //delete G;
        
 	//system ("circo -Tgif new.dot -o new.gif");
	//cout << count << "\t" << max << endl;
    return 0;*/
			
			/*Graph G(NUM_VERTICES, false);
			cout << "vertices: " << NUM_VERTICES << "\n";
			for (int i = 0; i < NUM_GRAPHS; i++)
			{			
				//randomMTF(G);
				random_k_bip(G, 9);				
				//if (isBipartite(G)) {i--; continue;} 
				//if (maxDegree(G) > NUM_VERTICES/4) {i--; continue;} 
				//if (i == 0) showAM(G);
				//complement(G);
				//writeRecord(G);
				int c = conn_match_num(G);
				//polyFile(G);
				printDotFile(G);
				cout << "connmatch: " << c << "\n";
				cout << isBipartite(G)<< "\n";
			}*/
			time_t start, end;
			double dif;
			vector <Graph> graphs;			
			ifstream infile;
			infile.open("readmuh", ifstream::in);
			int c;
			int min = 1000;
			int max = 0;
			graphs = readList(infile);
			//showAM(graphs[123]);
			int check = 0;
			int count = 0;
			time (&start);			
			for (int i = 0; i < graphs.size(); i++)
			{
				complement(graphs[i]);
				if (isBipartite(graphs[i])) continue;
				complement(graphs[i]);count++;
				c = conn_match_num(graphs[i]);
				if (c==3) 
					{
						check++;
						if (check == 2) printDotFile(graphs[i]); 
					}
				//if (c < 5) {cout << "\n***CEXP Graph #" << i << "***\n"; return 0;} 
				if (c > max) max = c;
				if (c < min) min = c;	
			}
			time (&end);
			dif = difftime(end, start);
			cout << "\n\n Min = "<< min << ", Max = " << max << ", Time = " << dif << "\n" << check << endl << count << endl;

			
			 

}
