#include <iostream>
#include <vector>
#include <fstream>
#include "classes.h"
#include "input_funct.h"
#include "output_functs.h"
#include "floydwarshall_funct.h"
#include "shortest_path_funct.h"
#include "betweenness_functs.h"
#include "closenesscentrality_funct.h"
#include "deg_dist_funct.h"
#include "diameter_funct.h"
#include "communitydetection_funct.h"

using namespace std;

int main()
{
	bool weighted = true;
	bool directed = true;
  bool community = false;
	Graph g;

	cout << "\n-------------------------- WELCOME! -------------------------" << endl;
	cout << "\n--------------------- READING IN GRAPH ----------------------" << endl;
	input(g);

	cout << "\n\nXXXXXXXXXXXXXXXXXX RUNNING FLOYD-WARSHALL XXXXXXXXXXXXXXXXXXX" << endl;
	FloydWarshall(g);
	ShortestPath(g);

	cout << "\n\nXXXXXXXXXXXXXX DIRECTED DEGREE DISTRIBUTION XXXXXXXXXXXXXXXXX" << endl;
	cout << "\n-------------- Unweighted Degree Distribution ---------------\n" << endl;
	DegreeDistribution(g, !weighted);
	
	cout << "\n-------------- Weighted Degree Distribution -----------------" << endl;
	DegreeDistribution(g, weighted);

	cout << "\n\nXXXXXXXXXXXXXXXX UNWEIGHTED GRAPH DIAMETER XXXXXXXXXXXXXXXXXX" << endl;

	cout << "\n---------------- Undirected Graph Diameter ------------------\n" << endl;
	GraphDiameter(g, !directed, community);

	cout << "\n----------------- Directed Graph Diameter -------------------\n" << endl;
	GraphDiameter(g, directed, community);

	cout << "\n\nXXXXXXXXXXXXXX UNWEIGHTED CLOSENESS CENTRALITY XXXXXXXXXXXXXX\n" << endl;
	cout << "-------------- Undirected Closeness Centrality --------------\n" << endl;
	ClosenessCentrality(g, !directed);

	cout << "\n\n--------------- Directed Closeness Centrality ---------------\n" << endl;
	ClosenessCentrality(g, directed);

	cout << "\n\n\nXXXXXXXXXXXX BETWEENNESS CENTRALITY DISTRIBUTION XXXXXXXXXXXX" << endl;

	cout << "\n------------- Unweighted Betweenness Centrality -------------" << endl;
	cout << "\n               ------Undirected Graph------                " << endl;
	BetweennessCentrality(g, !directed, !weighted);
	
	cout << "\n               -------Directed Graph-------                " << endl;
	BetweennessCentrality(g, directed, !weighted);

	cout << "\n-------------- Weighted Betweenness Centrality --------------" << endl;
	cout << "\n               ------Undirected Graph------                  \n" << endl;
	BetweennessCentrality(g, !directed, weighted);
	
	cout << "\n               -------Directed Graph-------                  \n" << endl;
	BetweennessCentrality(g, directed, weighted);

	cout << "\n\nXXXXXXXXXXXXXXXXXXX COMMUNITY DETECTION XXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "\n               ------Undirected Graph------                  \n" << endl;
  CommunityDetection(g, !directed);
	cout << "\n\n               -------Directed Graph-------                  \n" << endl;
	CommunityDetection(g, directed);
  
  cout<<"\n\n--------------------- Program Complete ----------------------"
      <<"\n--------------------- Have a nice day! ----------------------\n\n"<<endl;

	return 0;
}