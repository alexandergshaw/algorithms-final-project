//This file contains the function for executing the Floyd-Warshall algorithm and filling in the d and pred matrices
#include <limits>
#include <cstdlib>
using namespace std;

//Calculates the length of the shortest path between each possible 
//  pair of vertices in both the directed and undirected version of a graph.
//
//Requires a Graph object which has already had info regarding 
//  vertices, edges, and weights read into it.
//
//Updates the distance matrices for a directed (d[]) and undirected (Ud[]) graph,
//  in addition to updating the matrices used to retrieve the shortest path from
//  the directed (pred[]) and undirected (Upred[]) graphs.

void FloydWarshall(Graph& g);

void FloydWarshall(Graph& g)
{
  //Initializing the matrices
	for(int i = 0; i < g.numVertices; i++)
	{
    for(int j = 0; j < g.numVertices; j++)
		{
      if(i==j)
      {
        g.d[i][j]=0;
        g.Ud[i][j]=0;
        g.pred[i][j]=-1;
        g.Upred[i][j]=-1;
      }
      else
      {
        if(g.edge_matrix[i][j] > -1)
        {
          g.d[i][j] = 1; 	  //Initialize all path lengths
          g.pred[i][j] = i; //Initialize all midpoint indexes
        }
        else
        {
          g.d[i][j] = -1;
          g.pred[i][j] = -1;
        }

        //Undirected Graph
        
        if(g.undir_edge_matrix[i][j] > -1)
        {
          g.Ud[i][j] = 1; 	    //Initialize all path lengths
          g.Upred[i][j] = i;    //Initialize all midpoint indexes
        }
        else
        {
          g.Ud[i][j] = -1;
          g.Upred[i][j] = -1;
        }				
      }
		}
	}
  
  //Iterating and updating the matrices
	for(int k = 0; k < g.numVertices; k++)
	{
		for(int i = 0; i < g.numVertices; i++)
		{
			for(int j = 0; j < g.numVertices; j++)
			{
        if(i!=j)
        {
          if(g.d[i][k] > -1 && g.d[k][j] > -1 )
          {
            if(g.d[i][j] == -1 || g.d[i][k] + g.d[k][j] < g.d[i][j])
            {
              g.d[i][j] = g.d[i][k] + g.d[k][j];
              g.pred[i][j] = g.pred[k][j]; 				//Store index of vertex that served as midpoint
            }
          }
          
          if(g.Ud[i][k] > -1 && g.Ud[k][j] > -1 )
          {
            if(g.Ud[i][j] == -1 || g.Ud[i][k] + g.Ud[k][j] < g.Ud[i][j])
            {
              g.Ud[i][j] = g.Ud[i][k] + g.Ud[k][j];
              g.Upred[i][j] = g.Upred[k][j]; 				//Store index of vertex that served as midpoint
            }
          }
          
        }
			}
		}
	}
 
	return;
}
