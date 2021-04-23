#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/
#define NUM_OF_EDGE 40000
#define NUM_OF_VERTEX 20000

struct node{
    int end;
    int next;
};

node edge[NUM_OF_EDGE];
int stack[NUM_OF_VERTEX],head[NUM_OF_VERTEX],cnt = 0,top = 0, dfn=0,count_scc=0;
int DFN[NUM_OF_VERTEX],LOW[NUM_OF_VERTEX];
bool flag[NUM_OF_VERTEX];
bool contain[NUM_OF_VERTEX];

int min(int x, int y){return x<y? x:y;}

void add_edge(int start, int end){
    edge[cnt].next = head[start];
    edge[cnt].end = end;
    head[start] = cnt++;
}

void targan(int start){
    DFN[start] = LOW[start] = ++dfn;
    stack[top++] = start;
    flag[start] = true;
    
    for(int i = head[start];i!=-1;i = edge[i].next){
        if(DFN[edge[i].end] == 0){
            targan(edge[i].end);
            LOW[start] = min(LOW[start],LOW[edge[i].end]);
        }
        else if(flag[edge[i].end]){
            LOW[start] = min(LOW[start],DFN[edge[i].end]);
        }
    }

    if(LOW[start] == DFN[start]){
        for(int i = top-1;i>=0;--i){
            flag[stack[i]] = false;
            if(stack[i]==start){
                top = i;
                break;
            }
        }
        count_scc++;
    }
}

int SCC(int n, vector<pair<int,int>>& edge) {

    memset(head,-1,sizeof(head));
    memset(flag,0,sizeof(flag));
    memset(DFN,0,sizeof(DFN)); 
    memset(LOW,0,sizeof(LOW)); 
    memset(contain,0,sizeof(contain));  

    for(auto p:edge){
        contain[p.first] = true;
        add_edge(p.first,p.second);
    }

    for(int i = 0;i<n;++i){
        if(contain[i]&&DFN[i]==0) targan(i);
    }
    return count_scc;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout<<fin.is_open()<<endl;
    fin>>n>>m;
    cout<<n<<" "<<m<<endl;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
