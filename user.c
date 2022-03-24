#include "graph.h"
/*
* logic is a function that takes 3 arguments: the type of gate,
* the Cval from each of the nodes predecessors, and the number
* of fan-ins for that node. It returns the output of the gate.
* It will recursively call itself in the case of gates more
* complex than AND, OR, BUF, and NOT.
*/
int logic(int Type, int *Fin_values, int Nfi)
{
  int in1, in2, value, i; //in1 and in2 are temporary variables used for XOR and its derivatives
  
  int and_truth[3][3] = {
    {0, 0, 0},
    {0, 1, 2},
    {0, 2, 2}
  };
  int or_truth[3][3] = {
    {0, 1, 2},
    {1, 1, 1},
    {2, 1, 2}
  };
  int not_truth[3] = {1, 0, 2};
  switch (Type)
  {
    case  0: value = 2;
    case  1: value = Fin_values[0];
             break;
    case  2: value = and_truth[Fin_values[0]][Fin_values[1]];
             i = 2;
             while (i < Nfi)
             {
               value = and_truth[value][Fin_values[i]];
               i++;
             }
             break;
    case  3: value = logic(2, Fin_values, Nfi);
             Fin_values[0] = value;
             value = logic(9, Fin_values, Nfi);
             break;
    case  4: if (Nfi < 3) {
               value = or_truth[Fin_values[0]][Fin_values[1]];
             }
             else {
               value = or_truth[Fin_values[0]][Fin_values[1]];
               i = 2;
               while(i < Nfi) {
                 value = or_truth[value][Fin_values[i]];
                 i++;
               }
             }
             break;
    case  5: Fin_values[0] = logic(4, Fin_values, Nfi);
             value = logic(9, Fin_values, 1);
             break;
    case  6: in1 = logic(4, Fin_values, Nfi);
             in2 = logic(3, Fin_values, Nfi);
             Fin_values[0] = in1;
             Fin_values[1] = in2;
             value = logic(2, Fin_values, 2);
             break;
    case  7: Fin_values[0] = logic(6, Fin_values, Nfi);
             value = logic(9, Fin_values, 1);
             break;
    case  8: value = Fin_values[0];
             break;
    case  9: value = not_truth[Fin_values[0]];
             break;
    case 10: value = Fin_values[0];
    
  }
  return value;
}
/*
* simulation is the function that is called to simulate the circuit
* with the provided input. It takes the graph, a single pattern to
* be simulated, a pointer to the results file, and the Max node number
* as arguments. The function returns nothing, but writes the results
* to the file passed in as the 2nd argument on the command line.
*/

void simulation(NODE *graph, PATTERN PIV, FILE *outfile, int Max) {
  int i = 0; //iterators
  int x = 0;
  int input_cnt = 0;
  int y = 0;
  int Fin_values[Min]; //array that will hold all fanin primary outputs
  int Primary_outputs[Mpo];
  while(i <= Max) 
  {
    while(graph[i].Type==0)
    {
      i++;
    }
    x = 0;
    if (graph[i].Type==1) { 
      graph[i].Cval = PIV.piv[input_cnt];
      input_cnt++; 
    }
    else {
      LIST *temp = graph[i].Fin;
      while(temp != NULL)
      {
        Fin_values[x] = graph[temp->id].Cval;
        temp = temp->next;
        x++;
      }
      graph[i].Cval = logic(graph[i].Type, Fin_values, graph[i].Nfi); //sets primary output for current node
      if (graph[i].Po==1) //checks to see if node is a primary output
      {
        Primary_outputs[y] = graph[i].Cval;
        y++;
      }
    }
    i++;
  }
  for (int z=0; z<PIV.length; z++)
  {
    fprintf(outfile, "%d", PIV.piv[z]);
  }
  fprintf(outfile, "\n");
  for (int z=0; z<y; z++)
  {
    fprintf(outfile, "%d", Primary_outputs[z]);
  }  
  fprintf(outfile, "\n");
}

