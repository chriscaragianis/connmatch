// Program 17.4
//using namespace std;

template <class Graph>
class IO
	{
		public:
			static void show(const Graph &);
			static void scanEZ(Graph &);
			static void scan(Graph &);
			static void showAdjMat(const Graph &);
	};


// Program 17.3
template <class Graph>
void IO<Graph>::show(const Graph &G)
	{
		cout << "\n***Adjacency List***\n";
		for (int s = 0; s < G.V(); s++)
			{
				cout.width(2); cout << s << ":";
				typename Graph::adjIterator A(G, s);
				for (int t = A.beg(); !A.end(); t = A.nxt())
					{	cout.width(2); cout << t << " ";}
				cout << endl;
			}
	}

template <class Graph>
void IO<Graph>::showAdjMat(const Graph &G)
	{
		cout << "\n***Adjacency Matrix (with size)***\n";
		cout << G.V() << endl;
		for (int s = 0; s < G.V(); s++)
			{
				for (int t = 0; t < G.V(); t++)
					{
						if (G.edge(s,t)) cout << "1";
							else cout << "0";
					}
				cout << endl;
			}
	}
void printEdge(Edge e)
	{
		cout << "{" << e.v << "," << e.w << "}";
	}

template <class Graph>
void printDotFile(const Graph &G, vector <double> edgeVals)
    {
        //Print dot file with edge labels
        vector <Edge> edgeList = edges(G);
        cout << "graph G { << endl;
        for (int i = 0; i < edgeList.size(); i++)
            {
                cout << edgeList[i].v << " -- " << edgeList[i].w << "[label = \"" << edgeVals[i] << "\"]";
            }
    }





