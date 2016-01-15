//This file contains the functions to store all of the information needed from
//the input into a Graph and get everything ready for use in later functions
using namespace std;

void input(Graph& Graph);

void input(Graph& Graph)
{
  //Graph Graph;        //Declaring Graph object
  ifstream fin;       //Declaring object to write from the file
  ofstream fout;      //Declaring object to write to a file
  
  Vertex tempVert1,tempVert2;     //Declaring temporary objects
  Edge tempEdge;
  
  bool empty=true;      //Object used to determine if the Graph is empty
  bool found1,found2;     //Objects used to determine if a vertex already exists in the vector
  fin.open("graph.txt");      //opening the file
 
  
  while(!(fin.eof()))
  {
    
    found1=false;     //initializing the found values
    found2=false;
    
    fin.ignore(500,'\n');     //Used to ignore the first line of the file and every "new line" character
    getline(fin,tempVert1.name,',');      //stores the first name of the line into tempVert1
    getline(fin,tempVert2.name,',');      //stores the second name into tempVert2
    fin>>tempEdge.weight;     //stores the integer at the end of the line into a temporary edge
    
    Graph.Edges.push_back(tempEdge);      //adds an edge with the weight of tempEdge into each of the edge vectors
    Graph.Edges_Undirected.push_back(tempEdge); 
    Graph.Edges_Undirected.push_back(tempEdge);     //this one is duplicated to create the two opposite edges for an undirected graph
    
    if(empty)     //this only executes at the very beginning
    {
      Graph.Vertices.push_back(tempVert1);
      Graph.Vertices[0].OutDegree++;
      Graph.Vertices[0].w_OutDegree+=tempEdge.weight;
      Graph.Vertices.push_back(tempVert2);
      Graph.Vertices[1].InDegree++;
      Graph.Vertices[1].w_InDegree+=tempEdge.weight;
      Graph.Edges[0].source=0;
      Graph.Edges[0].target=1;
      Graph.Edges_Undirected[0].source=0;
      Graph.Edges_Undirected[0].target=1;
      Graph.Edges_Undirected[1].source=1;
      Graph.Edges_Undirected[1].target=0;
      empty=false;
    }
    else      //this executes for the remaining cases
    {
      for(int i=0; i<(int)Graph.Vertices.size(); i++)     //searching through every index of the Vertices vector
      {
        if(tempVert1.name==Graph.Vertices[i].name)      //if the name previously exists in the vector...
        {
          Graph.Vertices[i].OutDegree++;      //increment the source vertex's out degree
          Graph.Vertices[i].w_OutDegree+=tempEdge.weight;
          found1=true;
          Graph.Edges.back().source=i;      //stores the index of the vertex into the most recent edge's source variable
          Graph.Edges_Undirected[(int)Graph.Edges_Undirected.size()-2].source=i;
          Graph.Edges_Undirected.back().target=i;     //this and the line above doing the same thing but for the undirected graph
        }
        if(tempVert2.name==Graph.Vertices[i].name)      //same thing as above but now for the target vertex
        {  
          Graph.Vertices[i].InDegree++;
          Graph.Vertices[i].w_InDegree+=tempEdge.weight;
          found2=true;
          Graph.Edges.back().target=i;
          Graph.Edges_Undirected[(int)Graph.Edges_Undirected.size()-2].target=i;
          Graph.Edges_Undirected.back().source=i;      
        }
      }
      if(!found1)     //if the source vertex was not found in the vector...
      {
        Graph.Vertices.push_back(tempVert1);      //add the vertex to the vetctor and increment its out degree
        Graph.Vertices.back().OutDegree++;
        Graph.Vertices.back().w_OutDegree+=tempEdge.weight;
        Graph.Edges.back().source=(Graph.Vertices.size()-1);      //update the most recent edge for directed and undirected
        Graph.Edges_Undirected[(int)Graph.Edges_Undirected.size()-2].source=(Graph.Vertices.size()-1);
        Graph.Edges_Undirected.back().target=(Graph.Vertices.size()-1);
      }
      if(!found2)     //same as above but for the target vertex
      {
        Graph.Vertices.push_back(tempVert2);
        Graph.Vertices.back().InDegree++;
        Graph.Vertices.back().w_InDegree+=tempEdge.weight;
        Graph.Edges.back().target=(Graph.Vertices.size()-1);
        Graph.Edges_Undirected[(int)Graph.Edges_Undirected.size()-2].target=(Graph.Vertices.size()-1);
        Graph.Edges_Undirected.back().source=(Graph.Vertices.size()-1);
      }  
    }
  }
  fin.close();    //no longer need the input file
  
  //Assigning values to the to the size variables in the graph now that the input is complete
  Graph.numVertices=(int)Graph.Vertices.size();
  Graph.numUndirEdges=(int)Graph.Edges_Undirected.size();
  Graph.numDirEdges=(int)Graph.Edges.size();
  
  //Altering the undirected vector for duplicate edges and summing their weights
  for(int x=0; x<(int)Graph.Edges_Undirected.size(); x++)
  {
    for(int y=(x+1); y<Graph.numUndirEdges; y++)
    {
      if(Graph.Edges_Undirected[y].source==Graph.Edges_Undirected[x].source&&Graph.Edges_Undirected[y].target==Graph.Edges_Undirected[x].target)
      {
        Graph.Edges_Undirected[x].weight+=Graph.Edges_Undirected[y].weight;
        Graph.Edges_Undirected[x+1].weight=Graph.Edges_Undirected[x].weight;
        Graph.Edges_Undirected.erase(Graph.Edges_Undirected.begin()+y);
        Graph.Edges_Undirected.erase(Graph.Edges_Undirected.begin()+(y-1));
        Graph.numUndirEdges=Graph.Edges_Undirected.size();
      }
    }
  }
  //Creating all of the 2D arrays
  Graph.d=new int* [Graph.numVertices];
  Graph.Ud=new int* [Graph.numVertices];
  Graph.pred=new int* [Graph.numVertices];
  Graph.Upred=new int* [Graph.numVertices];
  
  Graph.edge_matrix=new int* [Graph.numVertices];
  Graph.undir_edge_matrix=new int* [Graph.numVertices];
  for(int l=0; l<Graph.numVertices; l++)
  {
    Graph.d[l]=new int [Graph.numVertices];
    Graph.Ud[l]=new int [Graph.numVertices];
    Graph.pred[l]=new int [Graph.numVertices];
    Graph.Upred[l]=new int [Graph.numVertices];
    
    Graph.edge_matrix[l]=new int [Graph.numVertices];
    Graph.undir_edge_matrix[l]=new int [Graph.numVertices];
  }
  
//Creating edge matrix for directed graph
  for(int i=0; i<Graph.numVertices; i++)
  {
    for(int j=0; j<Graph.numVertices; j++)
    {
      found1=false;
      for(int k=0; k<Graph.numDirEdges; k++)
      {
        if(Graph.Edges[k].source==i&&Graph.Edges[k].target==j)
        {
          Graph.edge_matrix[i][j]=k;
          found1=true;
          break;
        }
      }
      if(!found1)
        Graph.edge_matrix[i][j]=-1;
    }
  }
  
//Creating edge matrix for undirected graph
  for(int i=0; i<Graph.numVertices; i++)
    {
      for(int j=0; j<Graph.numVertices; j++)
      {
        found1=false;
        for(int k=0; k<Graph.numUndirEdges; k++)
        {
          if(Graph.Edges_Undirected[k].source==i&&Graph.Edges_Undirected[k].target==j)
          {
            Graph.undir_edge_matrix[i][j]=k;
            found1=true;
            break;
          }
        }
        if(!found1)
          Graph.undir_edge_matrix[i][j]=-1;
      }
    }  
  
  //Outputting edge matrix (first 10)
  cout<<"\n-Displaying the first 10 rows and columns of the Edge Matrix-\n";
  cout<<"-------------------------------------------------------------"<<endl;
  cout<<"      ";
  for(int x=0; x<10; x++)
    cout<<x<<"        ";
  cout<<endl;
  for(int z=0; z<10; z++)
  {
    cout<<z;
    for(int y=0; y<10; y++)
    {
      
      cout<<"  [ ";
      if(Graph.edge_matrix[z][y]!=-1)
      {
        if(Graph.edge_matrix[z][y]/100!=0)
        {}
        else if(Graph.edge_matrix[z][y]/10==0)
        {
          cout<<"  ";
        }
        else
        {
          cout<<" ";
        }
      }
      else
      {
        cout<<" ";
      }
      cout<<Graph.edge_matrix[z][y]<<" ]";
    }
    cout<<endl;
  }    
  return;
}

