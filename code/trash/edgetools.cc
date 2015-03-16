//Return the graph's edges in a vector.  Program 17.2
template <class Graph>
vector <Edge> edges(Graph &G)
	{ 	int E = 0;
		vector <Edge> a(G.E());
		for (int v = 0; v < G.V(); v++)
			{
				typename Graph::adjIterator A(G,v);
				for (int w = A.beg(); !A.end(); w = A.nxt())
					if (G.directed() || v < w)
						a[E++] = Edge(v,w);
			}
		return a;
	}

//Replaces a graph with its complement
template <class Graph>
static void complement(Graph &G)
    {
        for (int i = 0; i < G.V(); i++)
            for (int j = i + 1; j < G.V(); j++)
                if (G.edge(i,j)) {G.remove(Edge(i,j));}
                    else {G.insert(Edge(i,j));}
    }

	template <class Graph>
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

