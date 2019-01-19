#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include<stdio.h>
int n;
using namespace std;
 
class Euler
{
  int V;    
  list<int> *adj;    
public:
  Euler(int V)  { this->V = V;  adj = new list<int>[V];  }
  ~Euler()      { delete [] adj;  }
 
  void addEdge(int u, int v) {  adj[u].push_back(v); adj[v].push_back(u); }
  void rmvEdge(int u, int v);
  void printEulerTour();
  void printEulerUtil(int s);
  int DFSCount(int v, bool visited[]);
  bool isValidNextEdge(int u, int v);
  int iseuler(int[]);
};

void Euler::printEulerTour()
{
  int u = 0;
  for (int i = 0; i < V; i++)
      if (adj[i].size() & 1)
        {   u = i; break;  }
  printEulerUtil(u);
  cout << endl;
}
 
void Euler::printEulerUtil(int u)
{
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
  {
      int v = *i;
      if (v != -1 && isValidNextEdge(u, v))
      {
          cout << u << "-" << v << " ";
          rmvEdge(u, v);
          printEulerUtil(v);
      }
  }
}

bool Euler::isValidNextEdge(int u, int v)
{
  int count = 0;  	
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
     if (*i != -1)
        count++;
  if (count == 1)
    return true;
    
  bool visited[V];
  memset(visited, false, V);
  int count1 = DFSCount(u, visited);
  
  rmvEdge(u, v);
  memset(visited, false, V);
  int count2 = DFSCount(u, visited);
 
  addEdge(u, v);
 
  return (count1 > count2)? false: true;
}
 
void Euler::rmvEdge(int u, int v)
{
  list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
  *iv = -1;
 
  list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
  *iu = -1;
}
 
int Euler::DFSCount(int v, bool visited[])
{
  visited[v] = true;
  int count = 1;
 
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
      if (*i != -1 && !visited[*i])
          count += DFSCount(*i, visited);
 
  return count;
}

int Euler::iseuler(int a[])
{
	int count = 0;
	for(int i=0;i<n;i++){
		if(a[i] % 2 != 0)
			count++;
	}
	if(count == 0){
		cout<<"Euler's circuit exists:\n";
		return 1;
	}
	else if(count == 2){
		cout<<"Euler's path exists:\n";
		return 1;
	}
	else{
		cout<<"No euler's path or circuit exist:'\n\n";
		return -1;
	}
}
 
class Hamiltonian
{
	int *path,v,x;
	public:
		Hamiltonian(int n){ v = 0; x = 0; path = new int[n]; }
		bool isSafe(bool graph[][10], int pos);
		bool hamCycleUtil(bool graph[][10], int pos, int i);
		bool hamCycle(bool graph[][10]);
		void printSolution();
};

bool Hamiltonian::isSafe(bool graph[][10], int pos)
{
    if (graph [ path[pos-1] ][ v ] == 0)
        return false;
 
     for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
 
    return true;
}
 
bool Hamiltonian::hamCycleUtil(bool graph[][10], int pos, int i)
{
    if (pos == n)
    {
        if ( graph[ path[pos-1] ][ path[0] ] == 1 )
        {
        	cout<<"Hamiltonian cycle exists\n";
        	x = 1;
    	}
        else
        	cout<<"Hamiltonian path exists\n";
        return true;
    }
 
    for (v = 0; v < n; v++)
    {
    	if(v == i)
    		continue;
        if (isSafe(graph, pos))
        {
            path[pos] = v;
 
            if (hamCycleUtil (graph, pos+1, i) == true)
                return true;
 
            path[pos] = -1;
        }
    }
 
    return false;
}
 
bool Hamiltonian::hamCycle(bool graph[][10])
{
    for (int i = 0; i < n; i++)
        path[i] = -1;

    for(int i=0;i < n; i++)
    {
	path[0] = i;
    if ( hamCycleUtil(graph, 1,i) == true )
    {
		printSolution();
    	return true;
    }
	}
    cout<<"\nNo Hamiltonian path or cycle exist";
    return false; 

}
 
void Hamiltonian::printSolution()
{
    for (int i = 0; i < n - 1; i++)
        cout << path[i] << "-" << path[i + 1] << " ";
        
 	if(x == 1)
    	cout << path[n - 1] << "-" << path[0];
    cout<<"\n";
}


int main()
{
	int i,j,v1,v2,Edges;
    cout<<"\n Enter the number of vertices of graph: ";
 	cin>>n;
 	Euler g1(n);
 	Hamiltonian g2(n);
 	int a[n] = {0};
 	bool graph1[10][10];
	for(i=1;i<=n;i++)
  		for(j=1;j<=n;j++)
   			graph1[i][j]=0;
 	cout<<"\n Enter the total number of edges: ";
 	cin>>Edges;
	for(i=1;i<=Edges;i++)
 	{
  		cout<<"\n Enter the edge: ";
  		cin>>v1>>v2;
  		graph1[v1][v2]=1;
  		graph1[v2][v1]=1;
  		g1.addEdge(v1, v2);
  		a[v1]++;	
		a[v2]++;
 	}
 	cout<<"\n";
 	g2.hamCycle(graph1);
 	cout<<"\n";
 	if(g1.iseuler(a) == 1)
 		g1.printEulerTour();
  return 0;
}
