// Program 17.4



#include "graph.h"
#include <vector>
#include <fstream>
#include <iostream>
#define DATAFILE "data.dat"
#define DOTFILE "new.dot"

using namespace std;

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

void printDotFile_cm(Graph &G, vector <double> edgeVals)
    {
        //Print dot file with edge labels
        ofstream dotfile;
        dotfile.open ("new.dot", ios::trunc);
        vector <Edge> edgeList = edges(G);
        dotfile << "graph G {\n\t node [shape = \"point\"]\n ";

        for (int i = 0; i < edgeList.size(); i++)
            {
                dotfile << edgeList[i].v << " -- " << edgeList[i].w << "[color = \"";
                if (edgeVals[i+2] == 0) {dotfile << "grey\"];\n"; continue;}
                if (edgeVals[i+2] == 1) {dotfile << "red\"];\n"; continue;}
                if (edgeVals[i+2] > 0.0 && edgeVals[i] < 1.0) {dotfile <<"pink\"];\n";continue;}
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
//template <class Graph>
void printDotFile(Graph &G)
	{
		cout << "Wrting dot file... \n";
		ofstream dotfile;
        dotfile.open ("./new.dot", ios::trunc);
        vector <Edge> edgeList = edges(G);
        dotfile << "graph G {\n\t node [shape = \"point\"]\n ";

		for (int i = 0; i < edgeList.size(); i++)
            {
                dotfile << edgeList[i].v << " -- " << edgeList[i].w << ";\n\t";
			}
			dotfile << "}\n";

	}

void showAM(const Graph &G)
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

void writeRecord(Graph &G)
{
	ofstream datafile;
	datafile.open ("data.dat", ios::app);
	Record r = record(G);
	datafile << "\n" << r.edges << "\t" << r.min_d << "\t" << r.max_d ; 
	cout << "\n" << r.edges << "\t" << r.min_d << "\t" << r.max_d ; 	
	datafile.close(); 
}

vector <bool> read_g6_line(char line[], int bytes)
{
	vector <bool> matrix;
	//int length = sizeof(line);
	int num = -1;
	for (int i=1; i < bytes; i++)
		{
			num = (int) line[bytes - i] - 63;
			for (int j = 0; j < 6; j++) 
				{
					matrix.push_back(num % 2);
					num = (num - (num % 2))/2;
				}
			
		}
	return matrix;
}

vector <Graph> readList(ifstream &infile)
{
	vector <Graph> Glist;
	vector <bool> matrix;	
	int test = 0;
	int count = 0;	
	char line[256];
	int vertices;
	while(!infile.eof())
	{
		count = 0;
		infile.getline(line, 256);
			//cout << line;
		if (line[0] < 63) break;
		while (line[count] >= 63 && line[count] <= 126) {count++;}			
		test = 0;		
		vertices = line[0] - 63;
		Glist.push_back(Graph(vertices, false));
		matrix = read_g6_line(line, count);
		//kill padding
		//for (int k = 0; k < (6 - vertices*(vertices-1)/2 % 6); k++) {matrix.pop_back();} cout << (6 - vertices*(vertices-1)/2 % 6);
		for (int i = 1; i <= vertices - 1; i++)
		{
			for (int j = 0; j <= i - 1; j++)
			{
								
				if (matrix.back()) Glist[Glist.size()-1].insert(Edge(i,j));
				
				matrix.pop_back(); 
			}
		}
	}
	return Glist;
	
}

