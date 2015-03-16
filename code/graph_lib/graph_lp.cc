#ifndef EDGES_CONNECTED
#define EDGES_CONNECTED (G.edge(edgeList[i].w, edgeList[j].w) || G.edge(edgeList[i].w, edgeList[j].v) || G.edge(edgeList[i].v, edgeList[j].w) || G.edge(edgeList[i].v, edgeList[j].v))
#endif

#ifndef EDGES_INTERSECT
#define EDGES_INTERSECT (edgeList[i].v == edgeList[j].v || edgeList[i].v == edgeList[j].w || edgeList[i].w == edgeList[j].v || edgeList[i].w == edgeList[j].w)
#endif


#define CONN_MATCH 0
#define MAX_CLIQUE 1
#define CM_DUAL 2

#include <vector>

#include "graph.h"
#include "graph_lp.h"
#include "graph_IO.h"
#include <glpk.h>
#include <vector>

template <class Graph>
class MCM_Solution {
    private:
        int int_sol;
        double linear_sol;
        vector <bool> int_edges;
        vector <double> linear_edges;
        Graph input;
        //double int_gap;
    public:
        MCM_Solution(const Graph &G);
        ~MCM_Solution();
        int I_obj() {return int_sol;};
        double L_obj() {return linear_sol;};
        vector <bool> I_edges() {return int_edges;};
        vector <double> L_edges() {return linear_edges;};
        static void print_dotfile(ofstream &OUTPUT);
};

//Solves either the integer or linear version of the
//connected matching problem.  Returns either a G.E()
//vector of edge assignments or a 1-vector containing
//the objective value.

vector <double> solve_lp(Graph &G, int problem, bool integer, bool silent)
	{
	    	glp_smcp lp_params;
        	glp_init_smcp(&lp_params);
        	glp_iocp ip_params;
	        glp_init_iocp(&ip_params);
        	if (silent)
        	    {
        	        //Turn GLPK messages off
        	        lp_params.msg_lev = GLP_MSG_OFF;
        	        ip_params.msg_lev = GLP_MSG_OFF;
			glp_term_out(GLP_OFF);
        	    }

		vector <Edge> edgeList = edges(G);
		glp_prob *lp;
		int ia[100000], ja[100000];
		double ar[100000], z;
		vector <double> solution;   //Will hold the return value

		int lineCount = 1;          // Counts non-zero entries in constraint matrix
		int rowCount = 1;           //Counts conditions
	        bool isolated = true;
		switch (problem)
		{
		    case CONN_MATCH:
	          	//Calculate edge pair conditions
	           	for (int i = 0; i < edgeList.size(); i++)
	            {
                   	for (int j = i + 1; j < edgeList.size(); j++)
                    {
                       	if (!EDGES_CONNECTED && !EDGES_INTERSECT) //...then sum is less <= 1
                      	{
                       	 	ia[lineCount] = rowCount, ja[lineCount] = i+1, ar[lineCount] = 1;
                           	ia[lineCount + 1] = rowCount, ja[lineCount + 1] = j+1, ar[lineCount +1] = 1;
                           	lineCount +=2 ;
                       		rowCount++;
                       	}
                   	}
               	}

              	//Calculate vertex conditions
               	for (int vertex = 0; vertex < G.V(); vertex++)
                {
            		for (int i = 0; i < edgeList.size(); i++)
                    {
            			if (edgeList[i].v == vertex || edgeList[i].w == vertex)
                        {
            				isolated = false;
                            //Add a non-zero entry for each edge incident to vertex
                            ia[lineCount] = rowCount, ja[lineCount] = i+1, ar[lineCount] = 1;
                            lineCount++;
                        }
                     }
                     if (!isolated) rowCount++; //Exclude isolated vertices
            	   		isolated = true;
            	}
               	lp = glp_create_prob();
               	glp_add_cols(lp,edgeList.size());
               	for (int i = 1; i <= edgeList.size(); i++)
                {
            		glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0);
            	    glp_set_obj_coef(lp, i, 1);
                    glp_set_col_kind(lp, i, GLP_IV);
                }
        	break;

           	case MAX_CLIQUE:
                
				//Calculate vertex pair conditions
               	for (int i = 0; i < G.V(); i++)
                {
        			for (int j = i + 1; j < G.V(); j++)
                    {
                     	if (!G.edge(i,j)) 
						{
							ia[lineCount] = rowCount, ja[lineCount] = i + 1, ar[lineCount] = 1;
                            ia[lineCount+1] = rowCount, ja[lineCount+1] = j + 1, ar[lineCount+1] = 1;
                            lineCount += 2, rowCount++;
						}
                    }
				}
               	lp = glp_create_prob();
               	glp_add_cols(lp,G.V());
               	for (int i = 1; i <= G.V(); i++)
                {
        	        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0);
                    glp_set_obj_coef(lp, i, 1);
                    glp_set_col_kind(lp, i, GLP_IV);
                }
			break;
            
			case CM_DUAL:
				//	
			break;		
			default:
            break;
		}
		//Create problem

		glp_set_prob_name(lp, "sample");
		glp_set_obj_dir(lp, GLP_MAX);
		glp_add_rows(lp,lineCount);

		for (int i = 1; i <= rowCount-1; i++)
			{
				glp_set_row_bnds(lp, i, GLP_UP, 0.0, 1.0);
			}

		glp_load_matrix(lp, lineCount-1, ia, ja, ar);
		//glp_write_lp(lp, NULL, "output.txt"); // Uncomment to write problem to human-readable file

		//Solve linear (relaxation)
		glp_simplex(lp, &lp_params);
		z = glp_get_obj_val(lp);
        solution.push_back(z);
		//Solve integer version
		if (integer) {glp_intopt(lp,&ip_params); z = glp_mip_obj_val(lp);}

        //solution[0] is obj_val
        solution.push_back(z);
        switch (problem)
        {
            case CONN_MATCH:
                for (int i = 1; i <= edgeList.size(); i++)
                    {
                        if (integer)
                            solution.push_back(glp_mip_col_val(lp, i));
                        else
                            solution.push_back(glp_get_col_prim(lp, i));
                    }
                break;
            case MAX_CLIQUE:
                for (int i = 1; i <= G.V(); i++)
                    {
                        if (integer)
                            solution.push_back(glp_mip_col_val(lp, i));
                        else
                            solution.push_back(glp_get_col_prim(lp, i));
                    }
                break;
        }
		//Finished
		glp_delete_prob(lp);
		return solution;
	}




int conn_match_num(Graph &G)
    {
        vector <double> sols = solve_lp(G, CONN_MATCH, true, true);
        return sols[1];

    }


vector <double> max_clique(Graph &G)
    {
        vector <double >sols = solve_lp(G, MAX_CLIQUE, true, false);
        sols.erase(sols.begin(),sols.begin()+1);
        return sols;
    }

double clique_num(Graph &G)
    {
        vector <double> sols = solve_lp(G, MAX_CLIQUE, true, false);
        return sols[1];
    }

double frac_clique_num(Graph &G)
    {
        vector <double> sols = solve_lp(G, MAX_CLIQUE, true, false);
        return sols[0];
    }
/*//Test a solution vector for integrality DOESNT WORK APPARENTLY
bool isIntegral(vector <double> sols)
    {
        for (int i = 0; i < sols.size(); i++)
            {
                if (sols[i] > 0.0 && sols[i] < 1.0) return false;
            }
        return true;
    }


template <class Graph>
vector <double> max_clique(const Graph &G){};
template <class Graph>
int clique_number(const Graph &G){};
template <class Graph>
double frac_clique_number(const Graph &G );
*/
