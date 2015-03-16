struct Edge
	{ 	int v, w;
		Edge(int v = -1, int w = -1) : v(v), w(w) {}
	};
class RandomGRAPH
	{	private:
			//Implementaion dependent code
		public:
			GRAPH(int, bool);
			~GRAPH();
			int V() const;
			int E() const;
			bool directed() const;
			//int insert(Edge);
			//int remove(Edge);
			void reroll();
			bool edge(int, int);
			class adjIterator
				{
					public:
						adjIterator(const GRAPH &, int);
						int beg();
						int nxt();
						bool end();
				};
	};
