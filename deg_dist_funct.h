//This file contains the function to find the in/out degrees for all vertices and edges
using namespace std;

//Calculates the vertex (vertices) with the highest in-/out-degree
//  for both the weighted and unweighted graphs in both the directed
//  and undirected graphs, outputs 
//
//Requires a Graph object which has already had been initialized
//  and had all information regarding its vertices and edges 
//  (including in-degree and out-degree) calculated and stored inside
//  of it. Also requires a boolean variable stating whether the graph
//  which the calculations are to be run on, is weighted.

//Generates files with vertices’ names and corresponding in-/out-degree
//  Displays vertices with highest in-/out-degrees for weighted and 
//  unweighted graphs to screen, for directed and undirected graphs.

void DegreeDistribution(Graph& g, bool WEIGHTED);

void DegreeDistribution(Graph& g, bool WEIGHTED)	//Input is the list of vertices of the graph
{
  int max_in = 0;
  int max_out = 0;
  
  vector<Vertex> vertices_in;
  vector<Vertex> vertices_out;
  vector<Output> outInDegree;
  vector<Output> outOutDegree;
  
  if (!WEIGHTED)
  {
    for (int i=0; i < g.numVertices; i++)
    {
      OutputCheck(outInDegree,g.Vertices[i].InDegree);
      OutputCheck(outOutDegree,g.Vertices[i].OutDegree);
      //-----IN-DEGREE-----//
      //Check to see if current in-degree is greater than the stored max value
      if (g.Vertices[i].InDegree > max_in)
      {
        vertices_in.clear();    //Set of vertices with the highest in-degree : empty vertices_in
        vertices_in.push_back(g.Vertices[i]);  //add i to vertices_in               
        max_in = g.Vertices[i].InDegree;
      }
      else if (g.Vertices[i].InDegree == max_in)
      {
        vertices_in.push_back(g.Vertices[i]);//add i to vertices_in
      }
      //-----OUT-DEGREE-----//
      //Check to see if current out-degree is greater than the stored max value
      if (g.Vertices[i].OutDegree > max_out)
      {
        vertices_out.clear();  //Set of the vertices with the highest out-degree: empty vertices_out
        vertices_out.push_back(g.Vertices[i]);  //add i to vertices_out
        max_out = g.Vertices[i].OutDegree;
      }
      else if (g.Vertices[i].OutDegree == max_out)
      {
        vertices_out.push_back(g.Vertices[i]); //add i to vertices_out
      }
    }
    
    cout<<"Highest Unweighted In-Degree = "<<max_in<<endl;
    cout<<"Vertices with Highest Unweighted In-Degree: ";
    for(int z=0; z<(int)vertices_in.size(); z++)
    {
      cout<<vertices_in[z].name;
      // cout<<endl;
    }
    cout<<endl<<endl;
    
    PrintOutput(outInDegree, "UnweightedInDegree.txt","Unweighted In-Degree","# of Vertices");
    
    cout<<"Highest Unweighted Out-Degree = "<<max_out<<endl;
    cout<<"Vertices with Highest Unweighted Out-Degree: ";
    for(int r=0; r<(int)vertices_out.size(); r++)
    {
      cout<<vertices_out[r].name;
      // cout<<endl;
    }
    cout<<endl<<endl;
    
    PrintOutput(outOutDegree, "UnweightedOutDegree.txt","Unweighted Out-Degree","# of Vertices");
  }
  else if(WEIGHTED)
  {
    for (int i=0; i < g.numVertices; i++)
    {    
      OutputCheck(outInDegree,g.Vertices[i].w_InDegree);
      OutputCheck(outOutDegree,g.Vertices[i].w_OutDegree);
      //-----WEIGHTED IN-DEGREE-----//
      //Check to see if current in-degree is greater than the stored max value
      if (g.Vertices[i].w_InDegree > max_in)
      {
        vertices_in.clear();    //Set of vertices with the highest in-degree : empty vertices_in
        vertices_in.push_back(g.Vertices[i]);  //add i to vertices_in               
        max_in = g.Vertices[i].w_InDegree;
      }
      else if (g.Vertices[i].w_InDegree == max_in)
      {
        vertices_in.push_back(g.Vertices[i]);//add i to vertices_in
      }
      //-----WEIGHTED OUT-DEGREE-----//
      //Check to see if current out-degree is greater than the stored max value
      if (g.Vertices[i].w_OutDegree > max_out)
      {
        vertices_out.clear();  //Set of the vertices with the highest out-degree: empty vertices_out
        vertices_out.push_back(g.Vertices[i]);  //add i to vertices_out
        max_out = g.Vertices[i].w_OutDegree;
      }
      else if (g.Vertices[i].w_OutDegree == max_out)
      {
        vertices_out.push_back(g.Vertices[i]); //add i to vertices_out
      }
    }
    
    cout<<"Highest Weighted In-Degree = "<<max_in<<endl;
    cout<<"Vertices with Highest Weighted In-Degree: ";
    for(int z=0; z<(int)vertices_in.size(); z++)
    {
      cout<<vertices_in[z].name;
    }
    cout<<endl<<endl;
    
    PrintOutput(outInDegree, "WeightedInDegree.txt","Weighted In-Degree","# of Vertices");
    
    cout<<"Highest Weighted Out-Degree = "<<max_out<<endl;
    cout<<"Vertices with Highest Weighted Out-Degree: ";
    for(int r=0; r<(int)vertices_out.size(); r++)
    {
      cout<<vertices_out[r].name;
    }
    cout<<endl<<endl;
    
    PrintOutput(outOutDegree, "WeightedOutDegree.txt","Weighted Out-Degree","# of Vertices");
  }
  return;
}
