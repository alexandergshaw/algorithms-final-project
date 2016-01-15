//This file contains the function ShortestPath which will assign
//the BetweennessCentrality values for every Vertex and Edge
using namespace std;

//Calculates the betweenness centrality values for each vertex
//  and edge of the given graph.

//Requires a Graph object which has already had info regarding
//  vertices, edges, and weights read into it, has had the lengths
//  of the shortest paths between each combination of vertices
//  calculated using the Floyd Warshall algorithm.

//Updates the member variables of the Edge and Vertex objects meant
//  to hold the betweenness centrality values.

void ShortestPath(Graph& g);

void ShortestPath(Graph& g)
{
  bool directed = true;
  int midpoint = -1;
	int target = -1; 
	int edgeIndex = -1;
  
  for(int v = 0; v < g.numVertices; v++)
  {
    g.Vertices[v].DirectedBetweenness=0;
    g.Vertices[v].UndirectedBetweenness=0;
  }
  for(int de = 0; de < g.numDirEdges; de++)
  {
    g.Edges[de].DirectedBetweenness=0;
    g.Edges[de].UndirectedBetweenness=0;  //Not necessary but there anyway
  }
  for(int ue = 0; ue < g.numUndirEdges; ue++)
  {
    g.Edges_Undirected[ue].UndirectedBetweenness=0;
    g.Edges_Undirected[ue].DirectedBetweenness=0; //Not necessary but there anyway
  }
  
  for(int x = 0; x < 2; x++)
  {
    for(int i = 0; i < g.numVertices; ++i)
    {
      for(int j = 0; j < g.numVertices; ++j)
      {
        target = j;
        if(directed)
        {
          midpoint = g.pred[i][j];
          if(midpoint != -1)
          {
            edgeIndex = g.edge_matrix[midpoint][target];
            g.Edges[edgeIndex].DirectedBetweenness++;
            while(midpoint != i)
            {
              g.Vertices[midpoint].DirectedBetweenness++;
              target = midpoint;
              midpoint = g.pred[i][target];
              edgeIndex = g.edge_matrix[midpoint][target];
              g.Edges[edgeIndex].DirectedBetweenness++;
            }
          }
        }
        else//if undirected
        {
          midpoint = g.Upred[i][j];
          if(midpoint != -1)
          {
            edgeIndex = g.undir_edge_matrix[midpoint][target];
            g.Edges_Undirected[edgeIndex].UndirectedBetweenness++;
          while(midpoint != i)
          {
            g.Vertices[midpoint].UndirectedBetweenness++;
            target = midpoint;
            midpoint = g.Upred[i][target];
            edgeIndex = g.undir_edge_matrix[midpoint][target];
            g.Edges_Undirected[edgeIndex].UndirectedBetweenness++;
          }
        }
			}
		}
	}
  directed = false;
  }
  //Make every UndirectedEdge be the sum of (s,t) and its (t,s) counterpart
  //eg. UndirectedEdge(s,t).BetweennessCentrality==UndirectedEdge(t,s).BetweennessCentrality
  for(int h=0; h<(int)g.Edges_Undirected.size(); h+=2)
  {
    g.Edges_Undirected[h].UndirectedBetweenness=g.Edges_Undirected[h].UndirectedBetweenness+g.Edges_Undirected[h+1].UndirectedBetweenness;
    g.Edges_Undirected[h+1].UndirectedBetweenness=g.Edges_Undirected[h].UndirectedBetweenness;
  }
  return;
}