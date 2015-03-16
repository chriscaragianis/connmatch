// Connected matching polytope methods
#define EDGES_CONNECTED (G.edge(edgeList[i].w, edgeList[j].w) || G.edge(edgeList[i].w, edgeList[j].v) || G.edge(edgeList[i].v, edgeList[j].w) || G.edge(edgeList[i].v, edgeList[j].v))
#define EDGES_INTERSECT (edgeList[i].v == edgeList[j].v || edgeList[i].v == edgeList[j].w || edgeList[i].w == edgeList[j].v || edgeList[i].w == edgeList[j].w)

#define EDGE_PAIR_INEQUALITY "{" << edgeList[i].v << "," << edgeList[i].w << "} + {" << edgeList[j].v << "," << edgeList[j].w << "} <= 1" << endl;


#define EDGE_PAIR_INEQUALITY_GLP "ia[" << lineCount << "] = " << rowCount << ",\t ja[" << lineCount << "] = " << i+1 << ",\t ar[" << lineCount<< "] = 1;\nia[" << lineCount + 1 << "] = " << rowCount << ",\t ja[" << lineCount + 1 << "] = " << j+1 << ",\t ar[" << lineCount +1 << "] = 1;\n"
#define VERTEX_CONDITION_GLP "ia[" << lineCount << "] = " << rowCount << ",\t ja[" << lineCount << "] = " << i+1 << ",\t ar[" << lineCount << "] = 1;\n"

#define BAD_EDGE_PAIR "{" << edgeList[i].v << ", " << edgeList[i].w << "}, {" << edgeList[j].v << ", " << edgeList[j].w << "}\n"


template <class Graph>
class Polytope
	{ 	private:
			bool isBadPair(Edge e, Edge f, const Graph &);
			//vector <Edge> getEdgeList(const Graph &);
		public:
			static void printVertexCondition(const Graph &);
			static void printEdgePairCondition(const Graph &);
			static void printGLPConditions(const Graph &G);
			static void printEdgeList(const Graph &G);

	};


template <class Graph>
void Polytope<Graph>::printGLPConditions(const Graph &G)
	{
		vector <Edge> edgeList = edges(G);
        int lineCount = 1;  // Counts non-zero entries in constraint matrix
		int rowCount = 1; //Counts conditions
		cout << "\n//***Edge Pair Conditions***\n";
		for (int i = 0; i < edgeList.size(); i++)
			{
				for (int j = i + 1; j < edgeList.size(); j++)
					{
						if (!EDGES_CONNECTED && !EDGES_INTERSECT)
							{
								cout <<  EDGE_PAIR_INEQUALITY_GLP;
								lineCount +=2 ;
								rowCount++;
							}

					}
			}

		//vector <int> adjList;
		cout << "\n//***Vertex Conditions***\n";
		int vertexCount = 1;
		bool nonEmpty = false;
		for (int vertex = 0; vertex < G.V(); vertex++)
			{
				for (int i = 0; i < edgeList.size(); i++)
					{
						if (edgeList[i].v == vertex || edgeList[i].w == vertex)
							{
								nonEmpty = true;
								vertexCount++;
								cout << VERTEX_CONDITION_GLP;
								lineCount++;
							}
					}
				if (nonEmpty) rowCount++;
				nonEmpty = false;

			}

	}

template <class Graph>
void Polytope<Graph>::printEdgeList(const Graph &G)
	{
		vector <Edge> edgeList;

 		for (int s = 0; s < G.V(); s++)
			{
				typename Graph::adjIterator B(G, s);
				for (int t = B.beg(); !B.end(); t = B.nxt())
					{if (t > s) edgeList.push_back(Edge(s,t));}

			}
		for (int t = 0; t < edgeList.size(); t++)
			{
				cout << "{" << edgeList[t].v << "," << edgeList[t].w << "}, ";
			}
}


/**********************************************
template <class Graph>
void Polytope<Graph>::printVertexCondition(const Graph &G)
	{
		vector <int> adjList;
		cout << "\n***Vertex Conditions***\n";
		for (int s = 0; s < G.V(); s++)
			{
				typename Graph::adjIterator A(G, s);
				for (int t = A.beg(); !A.end(); t = A.nxt())
					{	if (t > s) adjList.push_back(t);}
				for (int w = 0; w < adjList.size(); w++)
					{
						cout << "{" << s << "," << adjList[w] << "}";
						if (w < adjList.size() - 1) cout << " + ";
					}

				if (!adjList.empty())cout << " <= 1" << endl;
				adjList.clear();
			}

	}



template <class Graph>
void Polytope<Graph>::printEdgePairCondition(const Graph &G)
	{ TEMPORARILY BROKEN

		//int lineCount = 0;  // Counts non-zero entries in constraint matrix
		cout << "\n***Edge Pair Conditions***\n";
		vector <Edge> edgeList;

 		for (int s = 0; s < G.V(); s++)
			{
				typename Graph::adjIterator B(G, s);
				for (int t = B.beg(); !B.end(); t = B.nxt())
					{if (t > s) edgeList.push_back(Edge(s,t));}

			}
		for (int i = 0; i < edgeList.size(); i++)
			{
				for (int j = i + 1; j < edgeList.size(); j++)
					{
						if (!CONNECTED_CONDITION)
							{
								//lineCount++;
								cout << EDGE_PAIR_INEQUALITY_GLP;
							}

					}
			}
	}*/



template <class Graph>
vector <double> solve_GLPK(const Graph &G)
	{

		vector <Edge> edgeList = edges(G);
		glp_prob *lp;
		int ia[100000], ja[100000];
		double ar[100000], z;
		vector <double> solution;

		int lineCount = 1;  // Counts non-zero entries in constraint matrix
		int rowCount = 1; //Counts conditions
		//cout << "\n//***Edge Pair Conditions***\n";
		for (int i = 0; i < edgeList.size(); i++)
			{
				for (int j = i + 1; j < edgeList.size(); j++)
					{
						if (!EDGES_CONNECTED && !EDGES_INTERSECT)
							{
								ia[lineCount] = rowCount, ja[lineCount] = i+1, ar[lineCount] = 1; //cout << i + 1 << ",";
								ia[lineCount + 1] = rowCount, ja[lineCount + 1] = j+1, ar[lineCount +1] = 1;//cout << j+1 << endl;
								lineCount +=2 ;
								rowCount++;
							}

					}
			}
		//cout << "\n//***Vertex Conditions***\n";
		bool nonEmpty = false;
		for (int vertex = 0; vertex < G.V(); vertex++)
			{
				for (int i = 0; i < edgeList.size(); i++)
					{
						if (edgeList[i].v == vertex || edgeList[i].w == vertex)
							{
								nonEmpty = true;

								ia[lineCount] = rowCount, ja[lineCount] = i+1, ar[lineCount] = 1;//cout << i+1 << ",";
								lineCount++;
							}
					}
				if (nonEmpty) rowCount++; //cout << endl;
				nonEmpty = false;

			}
		//cout << "lineCount\t" << lineCount << endl;
		lp = glp_create_prob();
		glp_set_prob_name(lp, "sample");
		glp_set_obj_dir(lp, GLP_MAX);
		glp_add_rows(lp,lineCount);
		glp_add_cols(lp,edgeList.size());
		for (int i = 1; i <= rowCount-1; i++)
			{
				glp_set_row_bnds(lp, i, GLP_UP, 0.0, 1.0);
			}
		for (int i = 1; i <= edgeList.size(); i++)
			{
				glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0);
				glp_set_obj_coef(lp, i, 1);
			}
		glp_load_matrix(lp, lineCount-1, ia, ja, ar);
		glp_write_lp(lp, NULL, "output.txt");
		glp_simplex(lp,NULL);
		z = glp_get_obj_val(lp);

		for (int i = 1; i <= edgeList.size(); i++)
			{
				solution.push_back(glp_get_col_prim(lp, i));
			}
		glp_delete_prob(lp);
		return solution;

	}
