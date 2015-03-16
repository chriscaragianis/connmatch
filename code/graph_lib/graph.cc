#include "graph.h"
#include "graph_lp.h"
#include <vector>
#include <iostream>

#define BLACK 3
#define WHITE 4
#define QUIT 19999

using namespace std;


class Graph::adjIterator
{ Graph &G; int i, v;
public:
	adjIterator( Graph &G, int v) :
		G(G), v(v), i(-1) {}
	int beg()
		{i = -1; return nxt(); }
	int nxt()
		{
			for (i++; i < G.V(); i++)
				if (G.adj[v][i] == true) return i;
		}
	bool end()
		{ return i >= G.V(); }
};


//template <class Graph>
vector <Edge> edges(Graph &G)
	{ 	int E = 0;
		vector <Edge> a(G.E());
		for (int v = 0; v < G.V(); v++)
			{
				Graph::adjIterator A(G,v);
				for (int w = A.beg(); !A.end(); w = A.nxt())
					if (G.directed() || v < w)
						a[E++] = Edge(v,w);
			}
		return a;
	}

//Replaces a graph with its complement
//template <class Graph>
void complement(Graph &G)
    {
        for (int i = 0; i < G.V(); i++)
            for (int j = i + 1; j < G.V(); j++)
                if (G.edge(i,j)) {G.remove(Edge(i,j));}
                    else {G.insert(Edge(i,j));}
    }

//	template <class Graph>
int minDegree(Graph &G)
    {
        int min = G.V();
        int count = 0;
        for (int i = 0; i < G.V(); i++)
            {
                for (int j = 0; j < G.V(); j++)
                    if (G.edge(i,j)) count++;
                if (count < min) min = count;
                count = 0;
            }
        return min;
    }

int maxDegree(Graph &G)
    {
        int max = 0;
        int count = 0;
        for (int i = 0; i < G.V(); i++)
            {
                for (int j = 0; j < G.V(); j++)
                    if (G.edge(i,j)) count++;
                if (count > max) max = count;
                count = 0;
            }
        return max;
    }

bool isBipartite(Graph &G)
{
	int startColor = BLACK;
	int paintColor = WHITE;
	vector <int> vertices(G.V());
	vector <bool> done(G.V());
	int i = 0;
	while (i != QUIT)
		{
			
			vertices[i] = startColor;
			done[i] = true;
				
			Graph::adjIterator A(G,i);
			for (int w = A.beg(); !A.end(); w = A.nxt())
			{					
				
				if (vertices[w] == startColor) return false;
				vertices[w] = paintColor;
				
			}
			i = QUIT;
			for (int w = A.beg(); !A.end(); w = A.nxt())
			{
				if (!done[w]) i = w;
			}	
			paintColor = startColor;
			if (startColor == WHITE) startColor = BLACK; else startColor = WHITE;
			
		}
	return true;
}

void blank(Graph &G)
{
	vector <Edge> edg = edges(G);
	for (int i = 0; i < G.E(); i++)
	{
		G.remove(edg[i]);
	}
}

Record record(Graph &G)
{
	return Record(G.E(), minDegree(G), maxDegree(G));
}

bool indepEdges(Graph &G, Edge e, Edge f)
{
	if (G.edge(e.v, f.w)||G.edge(e.v, f.v)||G.edge(e.w, f.w)||G.edge(e.w, f.v)) return false;
	else return true;
}

bool C4(Graph &G, int v1, int v2, int v3, int v4)
{
	if (G.edge(v1,v2) && G.edge(v2,v3) && G.edge(v3,v4) && G.edge(v4,v1) && (!G.edge(v1,v3)) && (!G.edge(v2,v4))) return true;
	if (G.edge(v1,v2) && G.edge(v2,v4) && G.edge(v4,v3) && G.edge(v3,v1) && (!G.edge(v1,v4)) && (!G.edge(v2,v3))) return true;
	if (G.edge(v1,v4) && G.edge(v4,v2) && G.edge(v2,v3) && G.edge(v3,v1) && (!G.edge(v1,v2)) && (!G.edge(v3,v4))) return true;
	
}
int countC4(Graph &G)
{
	int count = 0;
	for (int v1 = 0; v1 < G.V() - 1; v1++ )
	{
		for (int v2 = 0; v2 < G.V() - 1; v2++ )
		{
			for (int v3 = 0; v3 < G.V() - 1; v3++ )
			{
				for (int v4 = 0; v4 < G.V() - 1; v4++ )
					if (C4(G,v1,v2,v3,v4)) count++;
			}
		}
	}
	return count/24;
}
