// Program 17.4


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
void printDotFile_cm(const Graph &G, vector <double> edgeVals)
    {
        //Print dot file with edge labels
        ofstream dotfile;
        dotfile.open ("new.dot", ios::trunc);
        vector <Edge> edgeList = edges(G);
        dotfile << "graph G {\n\t node [shape = \"point\"]\n ";

        for (int i = 0; i < edgeList.size(); i++)
            {
                dotfile << edgeList[i].v << " -- " << edgeList[i].w << "[color = \"";
                if (edgeVals[i] == 0) {dotfile << "grey\"];\n"; continue;}
                if (edgeVals[i] == 1) {dotfile << "red\"];\n"; continue;}
                if (edgeVals[i] > 0.0 && edgeVals[i] < 1.0) {dotfile <<"pink\"];\n";continue;}
                dotfile << "grey\"];\n";
            }
        dotfile << "}\n";
    }
template <class Graph>
void printDotFile_mc(const Graph &G, vector <double> nodeVals)
    {
        //Print dot file with edge labels
        ofstream dotfile;
        dotfile.open ("new.dot", ios::trunc);
        dotfile << "graph G {\n\t node [shape = \"point\"]\n ";

        for (int i = 0; i < G.V(); i++)
            {
                for (int j = i+1; j < G.V(); j++)
                    {
                        if (G.edge(i,j))
                            {
                                dotfile << i << " -- " << j << "[color = \"";
                                if (nodeVals[i] == 0 || nodeVals[j] == 0) {dotfile << "grey\"];\n"; continue;}
                                else {dotfile << "red\"];\n"; continue;}
                            }
                    }
                //if (edgeVals[i] > 0.0 && edgeVals[i] < 1.0) {dotfile <<"pink\"];\n";continue;}
                //dotfile << "grey\"];\n";
            }
        dotfile << "}\n";
    }
template <class Graph>
void printDotFile(const Graph &G)
	{
		ofstream dotfile;
        dotfile.open ("new.dot", ios::trunc);
        vector <Edge> edgeList = edges(G);
        dotfile << "graph G {\n\t node [shape = \"point\"]\n ";

		for (int i = 0; i < edgeList.size(); i++)
            {
                dotfile << edgeList[i].v << " -- " << edgeList[i].w << "\n\t";
			}
			dotfile << "}\n";

	}




