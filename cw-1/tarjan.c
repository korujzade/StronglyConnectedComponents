/* *****Tarjan algorithm to find  Strongly Connected Components *******
 * Graph was initialised using graph.h and graph_functions.c
 * 
 * Algorithm reads graph credentials from graph.gx file
 * The number of nodes, a name of each node and edges are declared
 * in graph.gx
 * 
 * I have used official stack library provided by Berkeley university. 
 * You can find detailed information about the stack here: 
 * https://www.cs.bu.edu/teaching/c/stack/array/
 * 
 * In my case, all single nodes are declared as strongly connected components.
 * In the example given at graph.gx, node 5 is single node which is not 
 * connected any node, not itself either. Node 6 is single-node cycle which 
 * means there is cycle from node 6 to itself only. Both of them are represented
 * as strongly connected components.
 */



#include "graph.h"
#include "stack.h"
#define min(a, b) (((a) < (b)) ? (a) : (b))

// Declaretation of funtions
void SCC(Graph* mygraph, int u, int indexArr[], int lowlink[], stackT stack, 
                                                                int inStack[]);
void DFS(Graph* mygraph);

// globally defined stack
stackT stackGl;

int main(int argc,char *argv[]) 
{
  // define graph  
  Graph mygraph;

  // read graph from command line argument
  read_graph(&mygraph,argv[1]);
  
  //print_graph(&mygraph);
 
  // send graph to dfs function
  DFS(&mygraph);
  
  return(0);
}

// counter for indexing nodes
static int counter = 0;

// strongly connected components
// function takes graph, current node, index array, lowlink array, stack and 
// boolean for nodes in stack
void SCC(Graph* mygraph, int u, int index[], int lowlink[], stackT stack, 
                                                                int inStack[])
{   
    // assign current stack to global stack variable
    stackGl = stack;
    counter = counter + 1;
    index[u] = lowlink[u] = counter;
    
    // add current node to stack
    StackPush(&stackGl, u);
    
    // change current node to true 
    inStack[u] = 1;
    
    // create adjacency list
    // it is outlist of current node
    List* adj = (List*)malloc(sizeof(List));
    adj = mygraph->table[u].outlist;   
    
    // while there is a node outlist of current node
    // update lowlink of current node
    while(adj != NULL)
    {
        // adjacent node of the current node
        int v = adj->index;
        
        // if adjacent node has not discovered yet
        // send node to strongly connected component function
        // update the lowlink of the current node
        if (index[v] == -1)
        {
            SCC(mygraph, v, index, lowlink, stackGl, inStack);        
            lowlink[u] = min(lowlink[u],lowlink[v]);       
        }
        // if adjacent node is already discovered 
        // update lowlink number of the current node anyway
        else if(inStack[v] == 1)
        {
            lowlink[u] = min(lowlink[u], index[v]);
        }

        // pass to next node
        adj = adj->next;
    }
    
    int tmp;
    
    // if lowlink number of current node is equal to the index number of same
    // node, print the node
    if(lowlink[u] == index[u])
    {
        // if current node is in not in the top the stack
        // find the node and print out
        while (stackGl.contents[stackGl.top] != u)
        {
            tmp = stackGl.contents[stackGl.top];
            printf("%d ", tmp);
            inStack[tmp] = 0;
            StackPop(&stackGl);
            
        }
        // print it
        tmp = stackGl.contents[stackGl.top];
        printf(" %d\n ", tmp);
        inStack[tmp] = 0;
        
        // remove nodes from stack
        StackPop(&stackGl);
    }
    
}

// Depth First Search 
void DFS(Graph* mygraph)
{
    // initialize arrays
    // inStack array keeps information about nodes whether they are in stack
    int index[mygraph->MaxSize];
    int lowlink[mygraph->MaxSize];
    int inStack[mygraph->MaxSize];
    stackT stack;
    
    // initialize stack
    StackInit(&stack, mygraph->MaxSize);

    // for each node in the graph
    for (int i = 1; i < mygraph->MaxSize; i++)
    {
       index[i] = -1;
       lowlink[i] = -1;
       inStack[i] = 0; // 0 - false
    }
    
    // for each node if it it not visited yet
    // send note to strongly connected components function
    for (int i = 1; i < mygraph->MaxSize; i++)
    {
        if (index[i] == -1)
        {
            SCC(mygraph, i, index, lowlink, stack, inStack);
        }    
    }        
}