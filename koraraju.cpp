#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &adj, vector<int> &vis,int curr, stack<int> &s)
{
	// cout<<curr<<endl;
	vis[curr]=1;
	for(auto x:adj[curr])
	{
		if(!vis[x])
			dfs(adj,vis,x,s);
	}
	s.push(curr);
}

int main()
{
	int n,m,tmp;
	cin>>n>>m;
	vector<vector<int> > edges;
	vector<vector<int>> adj(n+1);
	vector<int> vis(n+1,0);
	for(int i=0;i<m;i++)
	{
		vector<int> v(2);
		cin>>v[0]>>v[1];
		edges.push_back(v);
		adj[v[0]].push_back(v[1]);
	}
	stack<int> s,s2;
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
			dfs(adj,vis,i,s);
	}
	// cout<<s.size()<<endl;
	// while(!s.empty())
	// {
	// 	cout<<s.top()<<" ";
	// 	s.pop();
	// }
	adj.clear();
	adj.resize(n+1);
	for(int i=0;i<m;i++)
	{

		adj[edges[i][1]].push_back(edges[i][0]);
	}
	fill(vis.begin(),vis.end(),0);
	vector<vector<int>> scc;
	while(!s.empty())
	{
		int x=s.top();
		s.pop();
		if(!vis[x])
		{
			dfs(adj,vis,x,s2);
			vector<int> v;
			while(!s2.empty())
			{
				v.push_back(s2.top());
				s2.pop();
			}
			if(v.size()>0)
				scc.push_back(v);
		}
	}
	for(int i=0;i<scc.size();i++)
	{
		for(int j=0;j<scc[i].size();j++)
			cout<<scc[i][j]<<" ";
		cout<<endl;
	}
}
// 7 6
// 1 2
// 1 3
// 3 4
// 5 6
// 6 7
// 7 5