//This file includes all of the class definitions and class functions
using namespace std;

class Vertex
{
  public:
    string name;                //String for the name of the vertex
    int DirectedBetweenness;    //Integer for the number of shortest paths the vertex is involved in (betweenness centrality)
    int UndirectedBetweenness;  //Integer for the number of shortest paths the vertex is involved in (betweenness centrality)
    int InDegree;               //Integer for the number of incoming edges for the vertex
    int OutDegree;              //Integer for the number of outgoing edges for the vertex
    int w_InDegree;             //Integer for the sum of the weights of incoming edges for the vertex
    int w_OutDegree;            //Integer for the sum of the weights of outgoing edges for the vertex
    Vertex();                   //Overloaded Default Constructor to initialize the values
};

class Edge
{
  public:
    int source;                 //Integer for the index of the source vertex for the edge 
    int target;                 //Integer for the index of the target vertex for the edge
    int weight;                 //Integer for the weight of edge
    int DirectedBetweenness;    //Integer for the number of shortest paths the edge is involved in (unweighted betweenness centrality)
    int UndirectedBetweenness;  //Integer for the number of shortest paths the edge is involved in (weighted betweenness centrality)
    int UNWEIGHTED;             //Constant integer for the value of the edge in an unweighted graph
    Edge();                     //Overloaded Default Constructor to initialize the values
};

class Graph
{
  public:
  vector<Vertex> Vertices;      //Vector of Vertices
  vector<Edge> Edges;           //Vector of Edges
  vector<Edge> Edges_Undirected;//Vector of Edges for an undirected graph
  int** edge_matrix;            //Dynamically allocated 2D array for storing the index of the edge connecting i and j
  int** undir_edge_matrix;      //'' but for an undirected graph
  int** d;                      //2D array for use in the Floyd-Warshall algorithm (stores the shortest path length foe each vertex to every other vertex)
  int** Ud;                     //Undirected d matrix
  int** pred;                   //Used in Floyd-Warshall and ShortPath() to find betweenness values
  int** Upred;                  //Undirected pred matrix
  int numVertices;              //Integer for the number of Vertices in the graph
  int numDirEdges;              //Integer for the number of edges in the directed graph
  int numUndirEdges;            //Integer for the number of edges in the undirected graph
  Graph();                      //Overloaded Default Constructor to initialize values
  Graph(const Graph& g);        //Copy Constructor for Community Detection
  ~Graph();                     //Overloaded Default Destructor to delete all pointers and avoid memory leaks
};

class Output
{
  public:
  float Value;                  //Any value for the x-axis of a graph
  int Tally;                    //(y-axis)Integer to store the number of times Value occurred in a set
  Output():Value(0),Tally(1){}  
  //Default constructor inline'ed to initialize Value to 0 and Tally to 1
  //(Tally is 1 because if there is a need for a new Output object, there
  //  had to be 1 occurrence of that Value)
};

//Class functions (constructors/destructors)

//Default Constructors for Vertex and Edge to initialize values 
Vertex::Vertex()
{
  name="";
  DirectedBetweenness=0;
  UndirectedBetweenness=0;
  InDegree=0;
  OutDegree=0;
  w_InDegree=0;
  w_OutDegree=0;
}

Edge::Edge()
{
  source=0;
  target=0;
  weight=1;
  DirectedBetweenness=0;
  UndirectedBetweenness=0;
  UNWEIGHTED=1;
}

Graph::Graph()
{
  edge_matrix=NULL;
  undir_edge_matrix=NULL;
  d=NULL;
  Ud=NULL;
  pred=NULL;
  Upred=NULL;
  numVertices=0;
  numDirEdges=0;
  numUndirEdges=0;
}

//Conditions: Graph to copy from must have gone through the input function.
//This new graph SHOULD NOT go through the input function 
Graph::Graph(const Graph& g)
{
  //Matrix creation
  edge_matrix = new int* [g.numVertices];
  undir_edge_matrix = new int* [g.numVertices];
  d = new int* [g.numVertices];
  Ud = new int* [g.numVertices];
  pred = new int* [g.numVertices];
  Upred = new int* [g.numVertices];
  for(int i=0; i < g.numVertices; i++)
  {
  edge_matrix[i] = new int[g.numVertices];
  undir_edge_matrix[i] = new int[g.numVertices];
  d[i] = new int[g.numVertices];
  Ud[i] = new int[g.numVertices];
  pred[i] = new int[g.numVertices];
  Upred[i] = new int[g.numVertices];
  }
  //Assigning values to matrices
  for(int i=0; i < g.numVertices; i++)
  {
    for(int j=0; j < g.numVertices; j++)
    {
      edge_matrix[i][j] = g.edge_matrix[i][j];
      undir_edge_matrix[i][j] = g.undir_edge_matrix[i][j];
      d[i][j] = g.d[i][j];
      Ud[i][j] = g.Ud[i][j];
      pred[i][j] = g.pred[i][j];
      Upred[i][j] = g.Upred[i][j];
    }
  }
  //Copying Vectors
  Vertices = g.Vertices;      
  Edges = g.Edges;
  Edges_Undirected = g.Edges_Undirected;
  
  //Copying integers
  numVertices = g.numVertices;
  numDirEdges = g.numDirEdges;
  numUndirEdges = g.numUndirEdges;
}

Graph::~Graph()
{
  for(int i=0; i<numVertices; i++)
	{
		delete [] edge_matrix[i];
		delete [] undir_edge_matrix[i];
		delete [] d[i];
    delete [] pred[i];
	}
  delete [] edge_matrix;
  delete [] d;
  delete [] pred;
  delete [] undir_edge_matrix;
}
