#include<iostream>
#include<string>
#include<cstdlib>
#include <ctime>
#include <malloc.h>

using namespace std;


//Country as a node
struct node{
  int vertex;
  node* next;
  
};

//Adds a node(country) to the linkedList by head insertion
//Returns the address of the head which is newly created node(country)
struct node* addNode(node *curHead,int newV){
    node* newHead = new node();
    newHead->vertex = newV;
    newHead->next= curHead;
    
    return newHead;
};

string continents[6]={"Asia", "North America", "Europe", "Africa", "Australia", "South America"};

string countries[42]={"Argentina", "Brazil", "Peru", "Venezuela",

    "Eastern Australia", "Indonesia", "New Guinea", "Western Australia",

    "Central Africa", "East Africa", "Eqypt", "Madagascar", "North Africa", "South Africa",

    "Great Britain", "Iceland", "Northern Europe", "Scandinavia", "Southern Europe", "Russia", "Western Europe",

    "Alaska", "Alberta", "Central America", "Easten US", "Greenland", "Northwest Territory", "Ontario", "Eastern Canada", "Western US",

    "Afghanistan", "China", "India", "Irkutsk", "Japan", "Kamchatka", "Middle East", "Mongolia", "Southeast Asia", "Siberia", "Ural", "Yakutsk"};
    

class stak
{
    struct node *top;
    public:
        stak();
        void push(int);
        int pop();
        bool isEmpty();
        void display();
};
 
stak::stak()
{
    top = NULL;
}
 
void stak::push(int data)
{
    node *p;
    if((p=(node*)malloc(sizeof(node)))==NULL){
        cout<<"Memory Exhausted";
        exit(0);
    }
    p = new node;
    p->vertex = data;
    p->next = NULL;
    if(top!=NULL)
    {
        p->next = top;
    }
    top = p;
}
 
int stak::pop()
{
    struct node *temp;
    int value;
    if(top==NULL){
        cout<<"\nThe stak is Empty"<<endl;
    }
    else
    {
        temp = top;
        top = top->next;
        value = temp->vertex;
        delete temp;
    }
    return value;
}
 
bool stak::isEmpty()
{
    return (top == NULL);
}
 
void stak::display()
{
    struct node *p = top;
    if(top==NULL){
        cout<<"\nNothing to Display\n";
    }
    else
    {
        cout<<"\n The contents of stak\n";
        while(p!=NULL){
            cout<<p->vertex<<endl;
            p = p->next;
        }
    }
}
 

class Graph
{
    private:
        int n;
        int **A;
    public:
        Graph(int siz = 2);
        ~Graph();
        bool isConnected(int, int);
        void addEdge(int x, int y);
        void DFS(int , int);
};


Graph::Graph(int siz)
{
    int i, j;
    if (siz < 2) n = 2;
    else n = siz;
    A = new int*[n];
    for (i = 0; i < n; ++i)
        A[i] = new int[n];
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            A[i][j] = 0;
}


Graph::~Graph()
{
    for (int i = 0; i < n; ++i)
    delete [] A[i];
    delete [] A;
}


bool Graph::isConnected(int x, int y)
{
    return (A[x-1][y-1] == 1);
}

void Graph::addEdge(int x, int y)
{
    A[x-1][y-1] = A[y-1][x-1] = 1;
}


void Graph::DFS(int x, int required)
{
    stak s;
    bool *visited = new bool[n+1];
    int i;
    for(i = 0; i <= n; i++)
        visited[i] = false;
    s.push(x);
    visited[x] = true;
    if(x == required) return;
    cout << " Depth first Search starting from vertex ";
    cout <<  x << " : " << endl;
    while(!s.isEmpty())
    {
        int k = s.pop();
        if(k == required) break;
        cout<<k<<" ";
        for (i = n; i >= 0 ; --i)
            if (isConnected(k, i) && !visited[i])
            {
                s.push(i);
                visited[i] = true;
            }
    }
    cout<<endl;
    delete [] visited;
}





int main(){
  
  //Example1:
  
  Graph g(8);
    g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(1, 4);
    g.addEdge(2, 5); g.addEdge(2, 6); g.addEdge(4, 7);
    g.addEdge(4, 8);
    g.DFS(1, 4);
    
  
  
  
  //Example2:
  //vertices=42 and edges=156
  int vertices, edges, i, v1, v2;
  printf("Enter the Number of Vertices -\n");
    scanf("%d", &vertices);

    printf("\nEnter the Number of Edges -\n");
    scanf("%d", &edges);
    
    struct node* adjList[vertices];
    
    for (i = 0; i <= vertices; ++i) {
        adjList[i] = NULL;
    }
    
    for (i = 1; i <= edges; ++i) {
        scanf("%d%d", &v1, &v2);

        // Adding edge v1 --> v2
        adjList[v1] = addNode(adjList[v1], v2);

		// Adding edge v2 --> v1
		// Remove this if you want a Directed Graph
     //  adjList[v2] = addNode(adjList[v2], v1);
    }
    //Adding nodes 
    
    //Contient South America
    
    adjList[0]=addNode(adjList[0], 1);
    adjList[0]=addNode(adjList[0], 2);
    
    adjList[1]=addNode(adjList[1], 0);
    adjList[1]=addNode(adjList[1], 2);
    adjList[1]=addNode(adjList[1], 3);
    adjList[1]=addNode(adjList[1], 12);
    
    adjList[2]=addNode(adjList[2], 0);
    adjList[2]=addNode(adjList[2], 1);
    adjList[2]=addNode(adjList[2], 3);
    
    adjList[3]=addNode(adjList[3], 1);
    adjList[3]=addNode(adjList[3], 2);
    adjList[3]=addNode(adjList[3], 23);
    
    //Continent Australia
    adjList[4]=addNode(adjList[4], 6);
    adjList[4]=addNode(adjList[4], 7);
    
    adjList[5]=addNode(adjList[5], 6);
    adjList[5]=addNode(adjList[5], 7);
    adjList[5]=addNode(adjList[5], 38);
    
    adjList[6]=addNode(adjList[6], 4);
    adjList[6]=addNode(adjList[6], 5);
    
    adjList[7]=addNode(adjList[7], 4);
    adjList[7]=addNode(adjList[7], 5);
    
    //Continent Africa
    adjList[8]=addNode(adjList[8], 9);
    adjList[8]=addNode(adjList[8], 12);
    adjList[8]=addNode(adjList[8], 13);
    
    adjList[9]=addNode(adjList[9], 10);
    adjList[9]=addNode(adjList[9], 11);
    adjList[9]=addNode(adjList[9], 36);
    
    adjList[10]=addNode(adjList[10], 9);
    adjList[10]=addNode(adjList[10], 12);
    adjList[10]=addNode(adjList[10], 18);
    adjList[10]=addNode(adjList[10], 36);
   /* 
    adjList[11]=addNode(adjList[11], 9);
    adjList[11]=addNode(adjList[11], 13);
    
    adjList[12]=addNode(adjList[12], 1);
    adjList[12]=addNode(adjList[12], 8);
    adjList[12]=addNode(adjList[12], 9);
    adjList[12]=addNode(adjList[12], 10);
    adjList[12]=addNode(adjList[12], 18);
    adjList[12]=addNode(adjList[12], 20);
    adjList[12]=addNode(adjList[12], 8);
    
    adjList[13]=addNode(adjList[13], 8);
    adjList[13]=addNode(adjList[13], 9);
    adjList[13]=addNode(adjList[13], 11);
    
    adjList[14]=addNode(adjList[14], 15);
    adjList[14]=addNode(adjList[14], 20);
    
    adjList[15]=addNode(adjList[15], 14);
    adjList[15]=addNode(adjList[15], 17);
    adjList[15]=addNode(adjList[15], 25);
    
    adjList[16]=addNode(adjList[16], 17);
    adjList[16]=addNode(adjList[16], 18);
    adjList[16]=addNode(adjList[16], 19);
    adjList[16]=addNode(adjList[16], 20);
    
    adjList[17]=addNode(adjList[17], 14);
    adjList[17]=addNode(adjList[17], 15);
    adjList[17]=addNode(adjList[17], 16);
    adjList[17]=addNode(adjList[17], 19);
    
    adjList[18]=addNode(adjList[18], 10);
    adjList[18]=addNode(adjList[18], 12);
    adjList[18]=addNode(adjList[18], 16);
    adjList[18]=addNode(adjList[18], 19);
    adjList[18]=addNode(adjList[18], 20);
    adjList[18]=addNode(adjList[18], 36);
    
    adjList[19]=addNode(adjList[19], 16);
    adjList[19]=addNode(adjList[19], 17);
    adjList[19]=addNode(adjList[19], 18);
    adjList[19]=addNode(adjList[19], 30);
    adjList[19]=addNode(adjList[19], 36);
    adjList[19]=addNode(adjList[19], 40);
    
    adjList[20]=addNode(adjList[20], 12);
    adjList[20]=addNode(adjList[20], 14);
    adjList[20]=addNode(adjList[20], 16);
    adjList[20]=addNode(adjList[20], 18);
    
    adjList[21]=addNode(adjList[21], 22);
    adjList[21]=addNode(adjList[21], 26);
    
    adjList[22]=addNode(adjList[22], 21);
    adjList[22]=addNode(adjList[22], 26);
    adjList[22]=addNode(adjList[22], 27);
    adjList[22]=addNode(adjList[22], 29);
    
    adjList[23]=addNode(adjList[23], 3);
    adjList[23]=addNode(adjList[23], 24);
    adjList[23]=addNode(adjList[23], 29);
    
    adjList[24]=addNode(adjList[24], 23);
    adjList[24]=addNode(adjList[24], 27);
    adjList[24]=addNode(adjList[24], 28);
    adjList[24]=addNode(adjList[24], 29);
    
    adjList[25]=addNode(adjList[25], 15);
    adjList[25]=addNode(adjList[25], 26);
    adjList[25]=addNode(adjList[25], 27);
    adjList[25]=addNode(adjList[25], 28);
    
    adjList[26]=addNode(adjList[26], 21);
    adjList[26]=addNode(adjList[26], 22);
    adjList[26]=addNode(adjList[26], 25);
    adjList[26]=addNode(adjList[26], 27);
    
    adjList[27]=addNode(adjList[27], 22);
    adjList[27]=addNode(adjList[27], 24);
    adjList[27]=addNode(adjList[27], 25);
    adjList[27]=addNode(adjList[27], 26);
    adjList[27]=addNode(adjList[27], 28);
    adjList[27]=addNode(adjList[27], 29);
    
    adjList[28]=addNode(adjList[28], 24);
    adjList[28]=addNode(adjList[28], 25);
    adjList[28]=addNode(adjList[28], 27);
    
    
    adjList[29]=addNode(adjList[29], 22);
    adjList[29]=addNode(adjList[29], 23);
    adjList[29]=addNode(adjList[29], 24);
    adjList[29]=addNode(adjList[29], 27);
    
    adjList[30]=addNode(adjList[30], 19);
    adjList[30]=addNode(adjList[30], 31);
    adjList[30]=addNode(adjList[30], 32);
    adjList[30]=addNode(adjList[30], 36);
    adjList[30]=addNode(adjList[30], 40);
    
    adjList[31]=addNode(adjList[31], 30);
    adjList[31]=addNode(adjList[31], 32);
    adjList[31]=addNode(adjList[31], 37);
    adjList[31]=addNode(adjList[31], 38);
    adjList[31]=addNode(adjList[31], 39);
    adjList[31]=addNode(adjList[31], 40);
    
    adjList[32]=addNode(adjList[32], 30);
    adjList[32]=addNode(adjList[32], 31);
    adjList[32]=addNode(adjList[32], 36);
    adjList[32]=addNode(adjList[32], 38);
    
    adjList[33]=addNode(adjList[33], 35);
    adjList[33]=addNode(adjList[33], 37);
    adjList[33]=addNode(adjList[33], 39);
    adjList[33]=addNode(adjList[33], 41);
    
    adjList[34]=addNode(adjList[34], 35);
    adjList[34]=addNode(adjList[34], 37);
    
    adjList[35]=addNode(adjList[35], 21);
    adjList[35]=addNode(adjList[35], 33);
    adjList[35]=addNode(adjList[35], 34);
    adjList[35]=addNode(adjList[35], 37);
    adjList[35]=addNode(adjList[35], 41);
    
    adjList[36]=addNode(adjList[36], 9);
    adjList[36]=addNode(adjList[36], 10);
    adjList[36]=addNode(adjList[36], 18);
    adjList[36]=addNode(adjList[36], 19);
    adjList[36]=addNode(adjList[36], 30);
    adjList[36]=addNode(adjList[36], 32);
    
    
    adjList[37]=addNode(adjList[37], 31);
    adjList[37]=addNode(adjList[37], 33);
    adjList[37]=addNode(adjList[37], 34);
    adjList[37]=addNode(adjList[37], 35);
    adjList[37]=addNode(adjList[37], 39);
    
    
    adjList[38]=addNode(adjList[38], 5);
    adjList[38]=addNode(adjList[38], 31);
    adjList[38]=addNode(adjList[38], 32);
    
    adjList[39]=addNode(adjList[39], 31);
    adjList[39]=addNode(adjList[39], 33);
    adjList[39]=addNode(adjList[39], 37);
    adjList[39]=addNode(adjList[39], 40);
    adjList[39]=addNode(adjList[39], 41);
    
    adjList[40]=addNode(adjList[40], 19);
    adjList[40]=addNode(adjList[40], 30);
    adjList[40]=addNode(adjList[40], 31);
    adjList[40]=addNode(adjList[40], 39);
    
    adjList[41]=addNode(adjList[41], 33);
    adjList[41]=addNode(adjList[41], 35);
    adjList[41]=addNode(adjList[41], 39);*/
    
    
    // Printing Adjacency List
    printf("\nAdjacency List -\n\n");
    for (i = 1; i <= vertices; ++i) {
        printf("adjList[%d] -> ", i);

        struct node * traverse = adjList[i];

        while (traverse != NULL) {
            //printf("%d -> ", traverse->vertex);
            cout <<"-> " <<countries[i];
            traverse = traverse->next;
        }

        printf("->NULL\n");
    }

    return 0;
  
}
