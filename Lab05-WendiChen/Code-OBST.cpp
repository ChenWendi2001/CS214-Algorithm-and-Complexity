#include <iostream>

using namespace std;

#define MAX 10000

const int n = 7;
double p[n + 1] = {0,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
double q[n + 1] = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};

int r[n + 1][n + 1];//Record the root node of the optimal subtree
double e[n + 2][n + 2];//Record the expected cost of the subtree
double w[n + 2][n + 2];//Record the probability sum of the subtree

void optimal_binary_search_tree(double *p,double *q,int n)
{
//The result is stored in e.
/*

Please write your code here.
*/
    for(int i = 0;i<n+1;++i){
        for(int j = 0;j<n+1;++j)
            r[i][j] = 0;
    }
    for(int i = 0;i<n+2;++i){
        for(int j = 0;j<n+2;++j){
            e[i][j] = 0;
            w[i][j] = 0;
        }
    }
    for(int i = 1;i<n+2;++i){
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
    for(int len = 1;len<=n;++len){
        for(int i = 1;i<=n-len+1;++i){
            int j = i+len-1;
            w[i][j] = w[i][j-1]+p[j]+q[j];
            e[i][j] = 0xFFFFFFF;
            for(int root = i;root<=j;++root){
                double temp = w[i][j]+e[i][root-1]+e[root+1][j];
                if(temp-e[i][j]<1e-6){
                    e[i][j] = temp;
                    r[i][j] = root;
                }
            }
        }
    }
}

/*
You can print the structure of the optimal binary search tree based on root[][]
The format of printing is as follows:
k2 is the root
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
k3 is the left child of k4
d2 is the left child of k3
d3 is the right child of k3
d4 is the right child of k4
d5 is the right child of k5
*/
void construct_optimal_bst(int i,int j,int k,bool flag)
{
//You can adjust the number of input parameters
/*
Please write your code here.
*/

    if(k==0){
        cout<<"k"<<r[i][j]<<" is the root"<<endl;
    }
    else{
        if(flag)
            cout<<"k"<<r[i][j]<<" is the right child of k"<<k<<endl;
        else
            cout<<"k"<<r[i][j]<<" is the left child of k"<<k<<endl;
    }
    if(i == r[i][j]){
        cout<<"d"<<i-1<<" is the left child of k"<<i<<endl;
    }
    else{
        construct_optimal_bst(i,r[i][j]-1,r[i][j],0);    
    }
    if(j == r[i][j]){
        cout<<"d"<<j<<" is the right child of k"<<j<<endl;
    }
    else{
        construct_optimal_bst(r[i][j]+1,j,r[i][j],1);    
    } 
}

int main()
{
    optimal_binary_search_tree(p,q,n);
    cout<<"The cost of the optimal binary search tree is: "<<e[1][n]<<endl;
    cout << "The structure of the optimal binary search tree is: " << endl;
    construct_optimal_bst(1,n,0,0);
}
