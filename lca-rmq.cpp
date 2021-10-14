#include<bits/stdc++.h>
using namespace std;

//logic is to create a euler tour of the graph( say it is 2*n-1)
//get corresponding heights of vertices.. make a segment tree on the heights vector(also 2*n-1)
//get also the firstoccurance of each vertice in the eule r tour
//for each query l,r (lca) , we find the firstoccurance(l) and firstoccurance(r) and get the 
//indice of the minimum height in that range..that value correspondong to euler tour at
// that indice is the lca


 void euler_tour(int start,vector<int> &euler,vector<vector<int>> &adj,vector<int> &height,int currheight,vector<int> &firstoccurance)
 {
 	if(firstoccurance[start]==-1)
	{
		firstoccurance[start]=euler.size();

	}
 	for(auto i:adj[start])
 	{
 		
 		euler.push_back(start);
 		height.push_back(currheight);

 		
 		euler_tour(i,euler,adj,height,currheight+1,firstoccurance);
 	}

 	euler.push_back(start);
 	height.push_back(currheight);
 }
vector<int> build_seg(vector<int> &height)
{
	int n=height.size();
	vector<int> seg(2*n);
	for(int i=n;i<2*n;i++)
		seg[i]=i-n;
	for(int i=n-1;i>=1;i--)
	{
		seg[i]= (height[seg[2*i]]>height[seg[2*i+1]])?seg[2*i+1]:seg[2*i];
	}
	return seg;
}
int rmq_lca(vector<int> &seg, vector<int> &height,vector<int> &euler,vector<int> &firstoccurance,int l,int r)
{
	int ind1=firstoccurance[l];
	int ind2=firstoccurance[r];
	int n=seg.size()/2;
	int ans=INT_MAX,ansind=-1;
	if(ind1>ind2)
		swap(ind1,ind2);
	ind1+=n;
	ind2+=n+1; //making in exclusive
	while(ind1<ind2)
	{
		if(ind1&1)
		{
			if(ans>height[seg[ind1]])
			{
				ans=height[seg[ind1]];
				ansind=seg[ind1];
			}
			ind1++;
		}
		if(ind2&1)
		{
			ind2--;
			if(ans>height[seg[ind2]])
			{
				ans=height[seg[ind2]];
				ansind=seg[ind2];
			}
		}
		ind1/=2;
		ind2/=2;
	}
	return euler[ansind];
}
int main()
{

	int n,m,tmp1,tmp2;
	cin>>n>>m;
	vector<vector<int> > adj(n+1);
	for(int i=0;i<m;i++)
	{
		cin>>tmp1>>tmp2;
		adj[tmp1].push_back(tmp2);
	}
	vector<int> euler,height,firstoccurance(n+1,-1);
	euler_tour(1,euler,adj,height,0,firstoccurance);
	// for(int i=0;i<euler.size();i++)
	// 	cout<<euler[i]<<" "<<height[i]<<" "<<firstoccurance[euler[i]]<<endl;
	vector<int> seg= build_seg(height);
	cout<<rmq_lca(seg,height,euler,firstoccurance,6,7);

}
// 12 11
// 1 2
// 1 3
// 2 4
// 2 5
// 4 8
// 8 10
// 8 11
// 8 9
// 9 12
// 3 6
// 6 7