#include <bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> 
//m1 is to use orderedset..skipping that
//m2 is to use merge sort..skipping that
//m3 segment tree, we can count how many numbers are between x+1 to y, using rmq
void update(vector<int> &seg,int ind, int val)
{
	int n=seg.size()/2;
	ind+=n;
	seg[ind]+=val; //its not a clean code..but we can just inc by 1..so doesnt matter
	ind/=2;
	while(ind)
	{
		seg[ind]=seg[2*ind]+seg[2*ind+1];
		ind/=2;
	}
}
int rmq(vector<int> &seg, int l, int r)
{
	int n=seg.size()/2;
	l+=n;
	r+=n+1;
	int ans=0;
	while(l<r)
	{
		if(l&1)
		{
			ans+=seg[l];
			l++;
		}
		if(r&1)
		{
			r--;
			ans+=seg[r];
		}
		l/=2;
		r/=2;
	}
	return ans;
}
void preprocess(vector<int> &v)
{
	int n=v.size();
	vector<int> ret=v;
	sort(ret.begin(),ret.end());
	for(int i=0;i<n;i++)
	{
		auto it=lower_bound(ret.begin(),ret.end(),v[i]);
		int ind= it-ret.begin();
		v[i]=ind;
	}

}
int main()
{
	int n;
	cin>>n;
	vector<int> v(n);
	for(int i=0;i<n;i++)
		cin>>v[i];
	vector<int> seg(2*n,0); //no need to build..init all zero
	preprocess(v);
	int ans=0;
	for(int i=0;i<n;i++)
	{

		ans+= rmq(seg,v[i]+1,n-1);
		update(seg,v[i],1);
	}
	cout<<ans<<endl;
	// for(int i=0;i<n;i++)
	// 	cout<<v[i]<<" ";
}