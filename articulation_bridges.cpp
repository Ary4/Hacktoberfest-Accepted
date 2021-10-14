#include <bits/stdc++.h>
 
using namespace std;
int tim=0;
//TARJAN ALGO
//does both articulation and bridges VVI
void dfsA(vector<vector<int>> &adj, vector<int> &low, vector<int> &vis, vector<int> &disc,int curr,int par, vector<int> &art, vector<pair<int,int>> &bridges) //dfs for articulation point or maybe return a vector calculation of art points?
{
//adj low, vis, disc, curr art, brid
	vis[curr]=1;
	disc[curr]=(++tim);
	low[curr]=tim;
	int child=0;
	for(int i=0;i<adj[curr].size();i++)
	{
		if(!vis[adj[curr][i]])
		{
			child++;
			dfsA(adj,low,vis,disc,adj[curr][i],curr,art,bridges);
			low[curr]=min(low[curr],low[adj[curr][i]]);
			
			if(par!=-1 && low[adj[curr][i]]>=disc[curr]) //critical error here done before
			{
				art[curr]=1;
			}
			if(low[adj[curr][i]]>disc[curr])
			{
				bridges.push_back({curr,adj[curr][i]});
			}

		}
		else if(par!=adj[curr][i])
		{
			low[curr]=min(low[curr],disc[adj[curr][i]]);
		}
	}
	if(par==-1 && child>1)
		art[curr]=1;
	
}

int main()
{
    //given a graph adj list, number of vertex 
    int n,m;
    cin>>n>>m;
    int edges[m][2];
    vector<vector<int> > adj(n); //0 indiced
    for(int i=0;i<m;i++)
    {
    	cin>>edges[i][0]>>edges[i][1];
    	adj[edges[i][0]].push_back(edges[i][1]);
    	adj[edges[i][1]].push_back(edges[i][0]);
    }
    vector<int> vis(n,0),low(n,0),disc(n,0),art(n,0);
    vector<pair<int,int> > bridges;
    for(int i=0;i<n;i++)
    {
    	// cout<<i<<endl;
    	if(!vis[i])
    		dfsA(adj,low,vis,disc,i,-1,art,bridges);
    }
    int cnt=0;
    for(int i=0;i<art.size();i++)
    {
    	cnt+=art[i];
    }
    cout<<cnt<<endl;
    for(int i=0;i<art.size();i++)
    {
    	if(art[i])
    		cout<<i<<" ";
    }
    cout<<endl;
    cout<<bridges.size()<<endl;
    sort(bridges.begin(),bridges.end());
    for(auto it: bridges)
    {
    	cout<<it.first<<" "<<it.second<<endl;
    }
    return 0;
}