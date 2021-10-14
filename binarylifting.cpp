#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
int kthanc(int n,int k,vector<vector<int>> &dp)
{
	int currnode=n;
	int len=dp[0].size();
	for(int i=0;i<len;i++)
	{
		if(k & (1<<i))
		{
			currnode=dp[currnode][i];
			if(currnode==-1)
				break;
		}
	}
	return currnode;
}
int lca(int n1,int n2,vector<int> &levels,vector<vector<int>> &dp)
{
	if(levels[n1]<levels[n2])
		swap(n1,n2);
	int k=levels[n1]-levels[n2];
	// cout<<k<<endl;
	for(int i=0;i<dp[0].size();i++)
	{
		if((1<<i)&k)
		{
			// cout<<n1<<" "<<i<<endl;
			n1=dp[n1][i];
		}
	}
	//now n1 and n2 are in same level
	cout<<n1<<" "<<n2<<endl;
	if(n1==n2)
		return n2;
	for(int i=dp[0].size()-1;i>=0;i--)
	{
		if(dp[n1][i]!=dp[n2][i])
		{
			n1=dp[n1][i];
			n2=dp[n2][i];
		}
	}
	return dp[n1][0];
}
int main()
{
	//binary lifting//
	// dp[i][0] stores the parent of i,
	// dp[i][1] stores the grandparent of i.
	// dp[i][2] stores the grandparent of grandparent of i
	// in general 
	// dp[i][j] = dp[dp[i][j-1]][j-1] //
	// remember this by that example
	//     5
	//    /...
	//   3
	//  /...
	// 2  so, dp[2][j] =3 for some j, and dp[3][j]=5 for the same j,
	// so dp[2][j+1]= 5=dp[dp[2][j]][j];
	// this is recursive formula
	int n,m,tmp1,tmp2;
	cin>>n>>m;
	int len=log2(n);
	vector<vector<int>> adj(n+1),dp(n+1,vector<int>(len+1,-1));
	for(int i=0;i<m;i++)
	{
		cin>>tmp1>>tmp2;
		adj[tmp1].push_back(tmp2);
		dp[tmp2][0]=tmp1;
	}
	for(int j=1;j<=len;j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(dp[i][j-1]!=-1)
				dp[i][j]=dp[dp[i][j-1]][j-1];
		}
	}
	vector<int> levels(n+1,-1);
	levels[1]=0;
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(auto i: adj[x])
		{
			levels[i]=levels[x]+1;
			q.push(i);
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<i<<": ";
		for(int j=0;j<=len;j++)
			cout<<dp[i][j]<<" ";
		cout<<endl;
	}
	cout<<kthanc(5,4,dp)<<endl;
	for(int i=1;i<=n;i++)
		cout<<levels[i]<<" ";
	cout<<endl;
	cout<<lca(5,9,levels,dp)<<endl;


}
// 9 8
// 1 2
// 3 4
// 6 5
// 2 3
// 2 6
// 6 7
// 7 8
// 7 9

