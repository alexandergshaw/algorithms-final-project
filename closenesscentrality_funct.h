//This file contains the closeness centrality function
using namespace std;

//For each vertex, determines the average shortest path length from that vertex to all other vertices.
//
//Requires a Graph object which has already had info regarding vertices, edges, and weights read into it,
//  and has had the lengths of the shortest paths between each combination of vertices calculated using 
//  the Floyd Warshall algorithm. Also requires a boolean variable stating whether the graph is directed.
//
//Displays vertices to the screen with the highest unweighted closeness centrality value to the screen
//  for the given graph. Outputs data regarding each vertex and its corresponding closeness centrality
//  values to a text file.

void ClosenessCentrality(Graph& g, bool directed);

void ClosenessCentrality(Graph& g, bool directed)  
{
  float sum = 0;
  float highestValue = 0;       //Max value found on this iteration
  vector<Output> outCC;         //Holds closeness centrality values for all vertices 
  vector<Vertex> CCVertices;    //Holds vertices with max closeness centrality values
  int numPaths = 0;             //number of valid paths initialized to zero for each vertex
  float ccv = 0;
  for (int i = 0; i < g.numVertices; ++i)
  {
    sum = 0;
    numPaths = 0;

    for (int j = 0; j < g.numVertices; ++j)
    {
      if(directed)
      {
        if(g.d[i][j] > 0)
        {
          numPaths++;             
          sum += g.d[i][j];
        }
      }
      else//if undirected
      {
        if(g.Ud[i][j] > 0)
        {
          numPaths++;             
          sum += g.Ud[i][j];
        } 
      }
    }
    
    ccv = 0;
    
    if(numPaths > 0)      //Prevent dividing by zero
    {
      ccv = sum / numPaths;
    }

    OutputCheck(outCC, ccv);

    if(ccv > highestValue)  
    {
      CCVertices.clear();  
      CCVertices.push_back(g.Vertices[i]); 
      highestValue = ccv;
    }
    else if(ccv == highestValue)
    {
      CCVertices.push_back(g.Vertices[i]); 
    }
  } 
  
  //Print the closeness centrality values for all vertices
  PrintOutput(outCC,(directed ? "DirectedClosenessCentrality.txt" : "UndirectedClosenessCentrality.txt"),"Closeness-Centrality","# of Vertices");

  //Print the vertices with the max closeness centrality values
  int numMaxVertices = CCVertices.size();
  //String used to reduce the amount of typing. Terniary operator to assign directed or undirected
  string title= (directed ? "Directed Closeness-Centrality":"Undirected Closeness-Centrality");
  
  cout<<"Highest "<<title<<" = "<<highestValue;
  cout<<"\nVertex with Highest "<<title<<": ";
  for(int i = 0; i < numMaxVertices; i++)
  { 
    cout << CCVertices[i].name<<(i==numMaxVertices-1 ? "" : ", ");//Terniary operator to put a comma after every vertex but the last
  }
  cout<<endl;
  
  return;
}