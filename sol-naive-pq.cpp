#include <bits/stdc++.h>
using namespace std;

int V,E,R,C,X;
int v[10004];
int t[1003];
vector<pair<int,int>> adj[1003];
vector<pair<int,int>> rdj[1003];
int rv[1000006];
int re[1000006];
int rn[1000006];

priority_queue<tuple<double, int, int, int>> w;
int sz[1003];
vector<int> sol[1003];
set<pair<int,int>> u;

double weigh(int vid, int epLat, int cLat, int num){
	return 1.0 * num * (epLat - cLat) * (X-v[vid]) / X;
}

int main(){
	cin>>V>>E>>R>>C>>X;
	for(int i=0; i<V; ++i){
		cin>>v[i];
	}
	for(int i=0; i<E; ++i){
		int K;
		cin>>t[i]>>K;
		for(int j=0; j<K; ++j){
			int x,l;
			cin>>x>>l;
			adj[i].push_back({x,l});
			rdj[x].push_back({i,l});
		}
	}
	for(int i=0; i<R; ++i){
		cin>>rv[i]>>re[i]>>rn[i];
	}

	for(int i=0; i<R; ++i){
		int e = re[i];
		for(auto p : adj[e]){
			int c = p.first;
			int l = p.second;
			double ww = weigh(rv[i], t[re[i]], p.second, rn[i]);
			w.push( make_tuple(ww, rv[i], re[i], c) );
		}
	}
	while(!w.empty()){
		double imp;
		int vv, ee, cc;
		tie(imp, vv, ee, cc) = w.top();
		w.pop();
		if( sz[ee] + v[vv] <= X && !u.count({ee,vv}) ){
			sz[ee] += v[vv];
			sol[ee].push_back(vv);
			u.insert({ee,vv});
		}
	}
	cout<<C<<"\n";
	for(int i=0; i<C; ++i){
		cout<<i;
		for(auto x:sol[i]){
			cout<<" "<<x;
		}
		cout<<"\n";
	}
	return 0;
}
