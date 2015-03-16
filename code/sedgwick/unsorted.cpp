// Program 17.3



	
// Program 17.5
template <class Graph>
class CC
	{
		private:
			//implementation dependent code
		public:
			CC(const Graph &);
			int count;
			bool connect(int, int);
	};
	
// Program 17.6
#include <iostream.h>
#include <stdlib.h>
#include "GRAPH.cc"
#include "IO.cc"
#include "CC.cc"
main(int argc, char *argv[])
{	int V = atoi(argv[1]);
	GRAPH G(V);
	IO<GRAPH>::scan(G);
	if (V < 20) IO<GRAPH>::show(G);
	cout << G.E() << " edges ";
	CC<GRAPH> Gcc(G);
	cout << Gcc.count() << " components" << endl;
}


 	
		
