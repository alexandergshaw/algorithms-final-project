//This file contains all of the functions related to BetweennessCentrality
//including the general output one and the one specific to Community Detection
using namespace std;

//Determines either the vertices and edges involved in the
//  largest number of shortest paths (for unweighted graphs)
//  or the edges involved in the largest number of shortest
//  paths (for weighted graphs).
//
//Requires a Graph object which has already had info regarding
//  vertices, edges, and weights read into it, has had the lengths
//  of the shortest paths between each combination of vertices calculated
//  using the Floyd Warshall algorithm, and has had the BetweennessCentrality 
//  value of each vertex and edge calculated using ShortestPath(). Also
//  requires boolean variables stating whether the graph is directed and/or weighted. 
//
//Displays edge(s) and/or vertex (vertices) to screen with highest betweenness
//  centrality values. Outputs data regarding each edge and/or vertex and its
//  betweenness centrality value to a text file.




//This function is used for the output of the various Betweenness Centrality values 
void BetweennessCentrality(Graph& g, bool DIRECTED, bool WEIGHTED);

//This function will only be used in the Community Detection segment
vector<int> BetweennessCentrality(Graph& g, bool DIRECTED);

void BetweennessCentrality(Graph& g, bool DIRECTED, bool WEIGHTED)	//Input is the graph and whether or not it is directed or weighted
{
  int maxDirected = 0;
  int maxUnDirected = 0;
  
  vector<Vertex> directedVertices;
  vector<Vertex> unDirectedVertices;
  vector<Edge> directedEdges;
  vector<Edge> unDirectedEdges;
  vector<Output> outDirected;
  vector<Output> outUnDirected;

  
  if (!WEIGHTED)
  {
    for (int i=0; i < g.numVertices; i++)
    {
      if(DIRECTED)
      {
        //-----DIRECTED-----//
        OutputCheck(outDirected,g.Vertices[i].DirectedBetweenness);
        //Check to see if current Betweenness Centrality is greater than the stored max value
        if (g.Vertices[i].DirectedBetweenness > maxDirected)
        {
          directedVertices.clear();    //Set of vertices with the highest in-degree : empty directedVertices
          directedVertices.push_back(g.Vertices[i]);  //add i to directedVertices               
          maxDirected = g.Vertices[i].DirectedBetweenness;
        }
        else if (g.Vertices[i].DirectedBetweenness == maxDirected)
        {
          directedVertices.push_back(g.Vertices[i]);//add i to directedVertices
        }
      }
      else
      {
        //-----UNDIRECTED-----//
        OutputCheck(outUnDirected,g.Vertices[i].UndirectedBetweenness);
        //Check to see if current Betweenness Centrality is greater than the stored max value
        if (g.Vertices[i].UndirectedBetweenness > maxUnDirected)
        {
          unDirectedVertices.clear();  //Set of the vertices with the highest out-degree: empty unDirectedVertices
          unDirectedVertices.push_back(g.Vertices[i]);  //add i to unDirectedVertices
          maxUnDirected = g.Vertices[i].UndirectedBetweenness;
        }
        else if (g.Vertices[i].UndirectedBetweenness == maxUnDirected)
        {
          directedVertices.push_back(g.Vertices[i]); //add i to unDirectedVertices
        }
      }
    }
    if(DIRECTED)
    {
      //Output Highest Values
      cout<<"Highest Directed Betweenness Centrality for Vertices = "<<maxDirected<<endl;
      cout<<"Vertex with Highest Directed Betweenness Centrality: ";
      for(int z=0; z<(int)directedVertices.size(); z++)
      {
        cout<<directedVertices[z].name;
      }
      cout<<endl<<endl;
      
      PrintOutput(outDirected, "DirectedBetweennessVertex.txt","Directed Betweenness Centrality","# of Vertices");
    }
    else//if undirected
    {
      //Output Highest Values    
      cout<<"Highest Undirected Betweenness Centrality for Vertices = "<<maxUnDirected<<endl;
      cout<<"Vertex with Highest Undirected Betweenness Centrality: ";
      for(int r=0; r<(int)unDirectedVertices.size(); r++)
      {
        cout<<unDirectedVertices[r].name;
      }
      cout<<endl<<endl;
      
      PrintOutput(outUnDirected, "UndirectedBetweennessVertex.txt","Undirected Betweenness Centrality","# of Vertices");
    }
    
    //Clear output vectors and max values before using with edges
    outDirected.clear();
    outUnDirected.clear();
    maxDirected=0;
    maxUnDirected=0;
    
    /*------------------------------ UNWEIGHTED BETWEENNESS CENTRALITY OF EDGE E -------------------------------------------------*/
    if(DIRECTED)
    {
      //-----DIRECTED-----//
      for (int i=0; i < g.numDirEdges; i++)
      {
        OutputCheck(outDirected,g.Edges[i].DirectedBetweenness);
        //Check to see if current Betweenness Centrality is greater than the stored max value
        if (g.Edges[i].DirectedBetweenness > maxDirected)
        {
          directedEdges.clear();    //Set of edges with the highest betweenness centrality : empty directedEdges
          directedEdges.push_back(g.Edges[i]);  //add i to directedVertices Edges
          maxDirected=g.Edges[i].DirectedBetweenness;
        }
        else if (g.Edges[i].DirectedBetweenness == maxDirected)
        {
          directedEdges.push_back(g.Edges[i]);   //add i to directedEdges
        }
      }
    }
    else//if undirected
    {
      //-----UNDIRECTED-----//
      for (int i=0; i < g.numUndirEdges; i+=2) //i += 2 because every other in index is made to mirror for directed
      {  
        OutputCheck(outUnDirected,g.Edges_Undirected[i].UndirectedBetweenness);
        //Check to see if current Betweenness Centrality is greater than the stored max value
        if (g.Edges_Undirected[i].UndirectedBetweenness > maxUnDirected)
        {
          unDirectedEdges.clear();  //Set of the edges with the highest unDirected Edges: empty unDirectedEdges
          unDirectedEdges.push_back(g.Edges_Undirected[i]);  //add i to unDirectedEdges
          maxUnDirected = g.Edges_Undirected[i].UndirectedBetweenness;
        }
        else if (g.Edges_Undirected[i].UndirectedBetweenness == maxUnDirected)
        {
          directedEdges.push_back(g.Edges_Undirected[i]); //add i to unDirectedEdges
        }
      }
    }
    
    if(DIRECTED)
    {
      //Output Highest Values
      cout<<"Highest Directed Betweenness Centrality for Edges = "<<maxDirected<<endl;
      cout<<"Edge with Highest Directed Betweenness Centrality:"<<endl;
      for(int z=0; z<(int)directedEdges.size(); z++)
      {
        cout<<"( "<<g.Vertices[directedEdges[z].source].name<<", "<<g.Vertices[directedEdges[z].target].name<<" )"<<endl;
      }
      cout<<endl;
      
      PrintOutput(outDirected, "DirectedBetweennessEdge.txt","Directed Betweenness Centrality","# of Edges");
    }
    else//if undirected
    {
      //Output Highest Values
      cout<<"Highest Undirected Betweenness Centrality for Edges = "<<maxUnDirected<<endl;
      cout<<"Edge with Highest Undirected Betweenness Centrality:"<<endl;
      for(int r=0; r<(int)unDirectedEdges.size(); r+=2)
      {
        cout<<"( "<<g.Vertices[unDirectedEdges[r].source].name<<", "<<g.Vertices[unDirectedEdges[r].target].name<<" )"<<endl;
      }
      cout<<endl;
      
      PrintOutput(outUnDirected, "UndirectedBetweennessEdge.txt","UnDirected Betweenness Centrality","# of Edges");
    }
    //Clear output vectors and max values before using with weighted values
    outDirected.clear();
    outUnDirected.clear();
    maxDirected=0;
    maxUnDirected=0;
  }
  else//if weighted
  {
    /*------------------------------ WEIGHTED BETWEENNESS CENTRALITY OF EDGE E -------------------------------------------------*/
    if(DIRECTED)
    {
      for (int i=0; i < g.numDirEdges; i++)
      {    
        OutputCheck(outDirected, (g.Edges[i].DirectedBetweenness / g.Edges[i].weight));
        
        //-----WEIGHTED DIRECTED-----//
        //Check to see if current directed edge is greater than the stored max value
        if ((g.Edges[i].DirectedBetweenness / g.Edges[i].weight) > maxDirected)
        {
          directedEdges.clear();    //Set of edges with the highest in-degree : empty DirectedEdges
          directedEdges.push_back(g.Edges[i]);  //add i to directedEdges               
          maxDirected = (g.Edges[i].DirectedBetweenness / g.Edges[i].weight);
        }
        else if ((g.Edges[i].DirectedBetweenness / g.Edges[i].weight) == maxDirected)
        {
          directedEdges.push_back(g.Edges[i]);//add i to directedEdges
        }
      }
    }
    else//if undirected
    {
      for (int i=0; i < g.numUndirEdges; i+=2)
      {
        OutputCheck(outUnDirected,(g.Edges_Undirected[i].UndirectedBetweenness / g.Edges_Undirected[i].weight));
        //-----WEIGHTED UNDIRECTED-----//
        //Check to see if current undirected edge is greater than the stored max value
        if ((g.Edges_Undirected[i].UndirectedBetweenness / g.Edges_Undirected[i].weight) > maxUnDirected)
        {
          unDirectedEdges.clear();  //Set of the edges with the highest undirected edges: empty unDirectedEdges
          unDirectedEdges.push_back(g.Edges_Undirected[i]);  //add i to unDirectedEdges
          maxUnDirected = (g.Edges_Undirected[i].UndirectedBetweenness / g.Edges_Undirected[i].weight);
        }
        else if ((g.Edges_Undirected[i].UndirectedBetweenness / g.Edges_Undirected[i].weight) == maxUnDirected)
        {
          unDirectedEdges.push_back(g.Edges_Undirected[i]); //add i to unDirectedEdges
        }
      }
    }
    
    if(DIRECTED)
    {
      //Output Highest Values
      cout<<"Highest Weighted Betweenness Centrality for Directed Edges = "<<maxDirected<<endl;
      cout<<"Directed Edge with Highest Weighted Betweenness Centrality:"<<endl;
      for(int z=0; z<(int)directedEdges.size(); z++)
      {
        cout<<"( "<<g.Vertices[directedEdges[z].source].name<<", "<<g.Vertices[directedEdges[z].target].name<<" )"<<endl;
      }
      cout<<endl;
      
      PrintOutput(outDirected, "WeightedBetweennessDirectedEdge.txt","Weighted Directed Betweenness Centrality","# of Edges");
    }
    else//if undirected
    {
      //Output Highest Values
      cout<<"Highest Weighted Betweenness Centrality for Undirected Edges = "<<maxUnDirected<<endl;
      cout<<"Undirected Edge with Highest Weighted Betweenness Centrality:"<<endl;
      for(int r=0; r<(int)unDirectedEdges.size(); r+=2)
      {
        cout<<"( "<<g.Vertices[unDirectedEdges[r].source].name<<", "<<g.Vertices[unDirectedEdges[r].target].name<<" )"<<endl;
      }
      cout<<endl;
      
      PrintOutput(outUnDirected, "WeightedBetweennessUndirectedEdge.txt","Weighted Undirected Betweenness Centrality","# of Edges");
    }
  }
  return;
}

vector<int> BetweennessCentrality(Graph& g, bool DIRECTED)
{
  int maxDirected = 0;
  int maxUnDirected = 0;
  
  vector<int> directedEdges;    //Will contain the indices of the directed edges with the highest value
  vector<int> unDirectedEdges;  //Will contain the indices of the undirected edges with the highest value

  for (int i=0; i < g.numVertices; i++)
  {
    /*------------------------------ UNWEIGHTED BETWEENNESS CENTRALITY OF EDGE E -------------------------------------------------*/
    if(DIRECTED)
    {
      //-----DIRECTED-----//
      for (int i=0; i < g.numDirEdges; i++)
      {
        //Check to see if current Betweenness Centrality is greater than the stored max value
        if (g.Edges[i].DirectedBetweenness > maxDirected)
        {
          directedEdges.clear();    //Set of edges with the highest betweenness centrality : empty directedEdges
          directedEdges.push_back(i);  //add i to directedVertices Edges
          maxDirected=g.Edges[i].DirectedBetweenness;
        }
        else if (g.Edges[i].DirectedBetweenness == maxDirected)
        {
          directedEdges.push_back(i);   //add i to directedEdges
        }
      }
    }
    else//if undirected
    {
      //-----UNDIRECTED-----//
      for (int i=0; i < g.numUndirEdges; i+=2) //i += 2 because every other in index is made to mirror for directed
      {  
        //Check to see if current Betweenness Centrality is greater than the stored max value
        if (g.Edges_Undirected[i].UndirectedBetweenness > maxUnDirected)
        {
          unDirectedEdges.clear();  //Set of the edges with the highest unDirected Edges: empty unDirectedEdges
          unDirectedEdges.push_back(i);  //add i to unDirectedEdges
          unDirectedEdges.push_back(i+1);
          maxUnDirected = g.Edges_Undirected[i].UndirectedBetweenness;
        }
        else if (g.Edges_Undirected[i].UndirectedBetweenness == maxUnDirected)
        {
          unDirectedEdges.push_back(i); //add i to unDirectedEdges
          unDirectedEdges.push_back(i+1);
        }
      }
    }
    //OUTPUT
    if(DIRECTED)
    {
      //Output Highest Values
      cout<<"Highest Directed Betweenness Centrality = "<<maxDirected<<endl;
      cout<<"Directed Edge with Highest Betweenness Centrality:"<<endl;
      for(int z=0; z<(int)directedEdges.size(); z++)
      {
        cout<<"( "<<g.Vertices[g.Edges[directedEdges[z]].source].name<<", "<<g.Vertices[g.Edges[directedEdges[z]].target].name<<" )"<<endl;
      }
      cout<<endl;
      return directedEdges;
    }
    else//if undirected
    {
      //Output Highest Values
      cout<<"Highest Undirected Betweenness Centrality = "<<maxUnDirected<<endl;
      cout<<"Undirected Edge with Highest Betweenness Centrality:"<<endl;
      for(int r=0; r<(int)unDirectedEdges.size(); r+=2)
      {
        cout<<"( "<<g.Vertices[g.Edges_Undirected[unDirectedEdges[r]].source].name<<", "<<g.Vertices[g.Edges_Undirected[unDirectedEdges[r]].target].name<<" )"<<endl;
      }
      cout<<endl;
      return unDirectedEdges;
    }
  }
  return directedEdges;
}