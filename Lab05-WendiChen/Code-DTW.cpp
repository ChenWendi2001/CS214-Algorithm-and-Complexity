#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
/*
The process to calculate the dynamic can be divided into four steps:
1.Create an empty cost matrix DTW with X and Y labels as amplitudes of the two series to be compared.
2.Use the given state transition function to fill in the cost matrix.
3.Identify the warping path starting from top right corner of the matrix and traversing to bottom left. The traversal path is identified based on the neighbor with minimum value.
i.e., When we reach the point (i, j) in the matrix, the next position is to choose the point with the smallest cost among (i-1,j-1), (i,j-1), and (i-1,j),
For the sake of simplicity, when the cost is equal, the priority of the selection is (i-1,j-1), (i,j-1), and (i-1,j) in order.
4.Calculate th time normalized distance. We define it as the average cost of the selected points.
*/
using namespace std;

int max(int a,int b){return a>b? a:b;}
int min(int a,int b){return a<b? a:b;}

double distance(vector<int> x, vector<int> y,int w) {
    int n = x.size();
    int m = y.size();
    vector<vector<int>> DTW;
    //Use the given state transition function to fill in the cost matrix.
    /*
    Please write your code here.
    */
    for(int i = 0;i<n;i++){
        DTW.push_back(vector<int>(m,0));
    }
    DTW[0][0] = abs(x[0]-y[0]);
    for(int j = 1;j<m&&abs(0-j)<=w;j++){
        DTW[0][j] = DTW[0][j-1]+ abs(x[0]-y[j]);
    }
    for(int i = 1;i<n&&abs(i-0)<=w;i++){
        DTW[i][0] = DTW[i-1][0]+ abs(x[i]-y[0]);
    }
    for(int i = 1;i<n;i++){
        for(int j = max(1,i-w);j<=min(m-1,i+w);j++){
            int local_min = DTW[i-1][j-1];
            if(abs(i-j+1)<=w && local_min>DTW[i][j-1]){
                local_min = DTW[i][j-1];
            }
            if(abs(i-j-1)<=w && local_min>DTW[i-1][j]){
                local_min = DTW[i-1][j];
            }
            DTW[i][j] = local_min+abs(x[i]-y[j]);
        }
    }

    // for(int i = 0;i<n;i++){
    //     for(int j = 0;j<m;j++){
    //         cout<<DTW[i][j]<<'\t';
    //     }
    //     cout<<endl;
    // }

    vector<int> d;
    //Identify the warping path.
    /*
    Please write your code here.
    */
    int i = n-1, j = m-1;
    d.push_back(DTW[i][j]);
    
    while(i>0 || j>0){
        if(i==0){
            d.push_back(DTW[i][j-1]);
            j = j-1;
        }
        else if(j==0){
            d.push_back(DTW[i-1][j]);
            i = i-1;
        }
        else {
            int local_min = DTW[i-1][j-1],local_i = i-1,local_j = j-1;
            if(abs(i-j+1)<=w && local_min>DTW[i][j-1]){
                local_min = DTW[i][j-1];
                local_i = i;
            }
            if(abs(i-j-1)<=w && local_min>DTW[i-1][j]){
                local_min = DTW[i-1][j];
                local_j = j;
            }
            i = local_i;
            j = local_j;
            d.push_back(local_min);
        }
    }

    // for(int k = 0;k<d.size();k++){
    //     cout<<d[k]<<' ';
    // }

    double ans = 0;
    //Calculate th time normalized distance
    /*
    Please write your code here.
    */
    for(int k = 0;k<d.size();k++){
        ans+=d[k];
    }
    ans/=d.size();
    return ans;
}

int main(){
	vector<int> X,Y;
    
	//test case 1
	X = {37,37,38,42,25,21,22,33,27,19,31,21,44,46,28};
	Y = {37,38,42,25,21,22,33,27,19,31,21,44,46,28,28};
    int w = 1;
    cout<<"w = "<<w<<endl;
	cout<<distance(X,Y,w)<<endl;
	//test case 2
	X = {11,14,15,20,19,13,12,16,18,14};
	Y = {11,17,13,14,11,20,15,14,17,14};
	cout<<distance(X,Y,w)<<endl;
	//Remark: when you modify the code to add the window constraint, the distance function has thus three inputs: X, Y, and the size of window w.
	return 0;
}
