#ifndef EDGES_CONNECTED
#define EDGES_CONNECTED (G.edge(edgeList[i].w, edgeList[j].w) || G.edge(edgeList[i].w, edgeList[j].v) || G.edge(edgeList[i].v, edgeList[j].w) || G.edge(edgeList[i].v, edgeList[j].v))
#endif

#ifndef EDGES_INTERSECT
#define EDGES_INTERSECT (edgeList[i].v == edgeList[j].v || edgeList[i].v == edgeList[j].w || edgeList[i].w == edgeList[j].v || edgeList[i].w == edgeList[j].w)
#endif


#include <vector>
#include <iostream>

#include "graph.h"
#include "graph_IO.h"
#include <vector>


vector< vector<bool> >  conn_match_mat(Graph &G)
{
	vector <Edge> edgeList = edges(G);
	vector <vector <bool> > matrix;
	
	//vertex constraints
	for (int vertex = 0; vertex < G.V(); vertex++)
	{
		vector <bool> vertex_row;
		for (int i = 0; i < edgeList.size(); i++)
		{
			if (edgeList[i].v == vertex || edgeList[i].w == vertex)
                vertex_row.push_back(true);
			else
				vertex_row.push_back(false);
		}

		matrix.push_back(vertex_row);
	}

	//edge constraints	
	for (int i = 0; i < edgeList.size(); i++)
	{
		vector <bool> edge_pair_row;
		for (int j = i + 1; j < edgeList.size(); j++)
        {
			if (!EDGES_CONNECTED && !EDGES_INTERSECT) //...then sum is less <= 1
			{
				for (int k = 0; k < edgeList.size(); k++)
				{
					if (k == i || k == j)
						edge_pair_row.push_back(true);
					else
						edge_pair_row.push_back(false);
				}
            }
		}
		matrix.push_back(edge_pair_row);	
	}

	return matrix;
}	
	
void print_mat(vector <vector <bool> > matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{	
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j]) 
				cout << "1 ";
			else
				cout << "0 "; 
		}
		cout << "\n";
	}
}

int main()
{
	Graph G(6, false);
	G.insert(Edge(0,1));
	G.insert(Edge(1,2));
	G.insert(Edge(2,3));
	G.insert(Edge(3,4));
	G.insert(Edge(4,5));
	G.insert(Edge(5,0  ));
	showAM(G);
	cout << "\n\n";
	print_mat(conn_match_mat(G));
}
