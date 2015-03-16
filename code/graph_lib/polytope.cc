#ifndef EDGES_CONNECTED
#define EDGES_CONNECTED (G.edge(edgeList[i].w, edgeList[j].w) || G.edge(edgeList[i].w, edgeList[j].v) || G.edge(edgeList[i].v, edgeList[j].w) || G.edge(edgeList[i].v, edgeList[j].v))
#endif

#ifndef EDGES_INTERSECT
#define EDGES_INTERSECT (edgeList[i].v == edgeList[j].v || edgeList[i].v == edgeList[j].w || edgeList[i].w == edgeList[j].v || edgeList[i].w == edgeList[j].w)
#endif

#include <fstream>
//#include "polytope.h"
#include "graph.h"
#include <vector>
void polyFile(Graph &G)
{
    ofstream polyfile;
	polyfile.open("conn_match.poly");
	int ia[100000], ja[100000];
		double ar[100000];
	//vector <vector <bool> > matrix;
	int lineCount = 1;          // Counts non-zero entries in constraint matrix
	int rowCount = 1;
	int nonZeroCount = 1;           //Counts conditions
    bool isolated = true;
	vector <Edge> edgeList = edges(G);
            
	//Calculate edge pair conditions
    for (int i = 0; i < edgeList.size(); i++)
    {
        	for (int j = i + 1; j < edgeList.size(); j++)
            {
     	       if (!EDGES_CONNECTED && !EDGES_INTERSECT) //...then sum is less <= 1
               {
     	          ia[lineCount] = rowCount, ja[lineCount] = i+1, ar[lineCount] = 1;
                  ia[lineCount + 1] = rowCount, ja[lineCount + 1] = j+1, ar[lineCount +1] = 1;
                  
				  lineCount +=2 ;
                  rowCount++;
               }

            }
    }

    //Calculate vertex conditions
    for (int vertex = 0; vertex < G.V(); vertex++)
    {
	    for (int i = 0; i < edgeList.size(); i++)
        {
	        if (edgeList[i].v == vertex || edgeList[i].w == vertex)
            {
	            isolated = false;
                //Add a non-zero entry for each edge incident to vertex
                ia[lineCount] = rowCount, ja[lineCount] = i+1, ar[lineCount] = 1;
                lineCount++;
            }
        }

        if (!isolated) rowCount++; //Exclude isolated vertices
        isolated = true;
    }

	
    polyfile << "INEQUALITIES\n";
	for (int i = 1; i < rowCount; i++) 
	{
		polyfile << "1 ";
		for (int j = 1; j < G.E()+1; j++)
		{	
			if (i == ia[nonZeroCount] && j == ja[nonZeroCount])
				{polyfile << "-1 "; nonZeroCount++;}
			else
				polyfile << "0 ";
		}
		polyfile << "\n";

	}
	
	for (int i = 0; i < G.E(); i++)
	{
		polyfile << "0 ";
		for (int j = 0; j < G.E(); j++)
		{
			if (i == j)
				polyfile << "1 ";
			else
				polyfile << "0 ";
		}
		polyfile << "\n";
	}
}	

