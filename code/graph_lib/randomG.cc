// randomG.cc
//
// Random graph models.  Add edges to an existing empty graph.
//
// TO DO:
//  * validate empty graph

#include "graph.h"
#include <iostream>
#include <stdlib.h>
using namespace std;  

//Random k-regular bipartite graph
void random_k_bip(Graph &G, int k)
	{
		blank(G);
		int vert2 = G.V() / 2;
		int degrees[G.V()];
		for (int i = 0; i < G.V(); i++)
			{degrees[i] = 0;}
		bool done = false;
		int nbr, src;
		bool goodnbr = false;
		bool fullup = false;
		while(!done)
			{	
				done = true;
				
				for (int j = 0; j < vert2; j++)
					{
						fullup = true;
						if (degrees[j] >= k) continue;
						for (int n = vert2; n < G.V(); n++) {if (degrees[n] < k) fullup = false;}
						if (fullup) continue;					
						while (!goodnbr) {nbr = (rand() % vert2) + vert2; if (degrees[nbr] < k && !G.edge(j,nbr)) goodnbr = true;}	
						G.insert(Edge(j, nbr));goodnbr = false;
						degrees[j]++; degrees[nbr]++;
					}
				for (int l = 0; l < G.V(); l++) {if (degrees[l] < k) done = false;}

			}
		for (int m = 0; m < G.V(); m++) {cout << "\n" << degrees[m] << ", ";}
		cout << "\n";
	}
//Erdos-Renyi random graph.  Probability of an edge = p

void random_p(Graph &G, float p)
    {
        for (int i = 0; i < G.V(); i++)
            for (int j = i + 1; j < G.V(); j++)
                if ((float) rand() / RAND_MAX  > p) G.insert(Edge(i,j));
    }

//Get a list of edges of G that will not complete a triangle

vector <Edge> safeEdges(Graph &G)
    {
        vector <Edge> safeEdges;
        bool good = true;
        for (int i = 0; i < G.V(); i++)
            {
                for (int j = i + 1; j < G.V(); j++)
                    {
                        if (G.edge(i,j)) good = false;
                        for (int k = 0; k < G.V(); k++)
                            {if (G.edge(k,i) && G.edge(k,j)) good = false;}
                        if (good) {safeEdges.push_back(Edge(i,j));}
                        good = true;
                    }
            }
        return safeEdges;
    }

//Generates a random mtf graph by sequentially choosing uniformly from the remaining
//non-edges whose addition does not complete a triangle (NOT a uniform distribution of mtfs)

void randomMTF(Graph &G)
    {
		//ONLY SEND IN EMPTY GRAPH
		blank(G);
        //srand ( time(NULL) );
        bool done = false;
        vector <Edge> sEdges = safeEdges(G);
        int index;
        while (!done)
        {
            sEdges = safeEdges(G);
            if (sEdges.size() == 0) {done = true; break;}
            if (sEdges.size() == 1) {done = true; G.insert(sEdges[0]); break;}
            index = rand() % (sEdges.size() - 1);
            G.insert(sEdges[index]);
            sEdges.erase(sEdges.begin()+index);

        }
    }
