//This file and included functions were made to make creating the graphics easier
//The text file created by the Output() function cal be opened in Excel with each cell independent
//With this, the graphs can just be made within Excel using the created tables
using namespace std;

//Function to check the Output vector to see if x exists
//    if so, increment Tally
//    if not, add x to the vector
void OutputCheck(vector<Output>& O, float x);

//Function to output the Output vector in fancy form
void PrintOutput(vector<Output> output_vector, string filename, string Xaxis, string Yaxis);

void OutputCheck(vector<Output>& O, float x)
{
  Output temp;
  bool found=false;
  
  temp.Value=x;
  //if the vector is empty, x does not exist therefore, add it
  if ((int)O.size()==0)
  {
    O.push_back(temp);
  }
  else
  {
    for(int i=0; i<(int)O.size(); i++)
    {
      if(O[i].Value==x)   //if x exists, increment Tally (the number of occurrences for that value)
      {
        O[i].Tally++;
        found=true;
        break;
      }
    }
    if(!found)            //if x does not exist in the vector, add it
    {
      O.push_back(temp);
    }
  }
  return;
}


void PrintOutput(vector<Output> output_vector, string filename, string Xaxis, string Yaxis)
{
  //integer created to reduce the function calls to size() in the for loop
  int size=(int)output_vector.size();
  
  ofstream fout;
  fout.open(filename.c_str());//opening file filename
  
  fout<<Xaxis<<"\t"<<Yaxis<<endl; //Output the X axis label and the Y axis label
  for(int i=0; i<size; i++)
  {
    //Output the values into the columns
    fout<<output_vector[i].Value<<"\t"<<output_vector[i].Tally<<endl;
  }
  fout.close();
  
  //Generated output is as follows:
  //  Xaxis   Yaxis
  //  x1      y1
  //  x2      y2
  //  x3      y3
  //  ...     ...
}