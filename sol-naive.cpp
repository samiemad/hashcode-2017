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

vector<tuple<double, int, int, int>> w;
int sz[1003];
vector<int> sol[1003];
set<pair<int,int>> u;

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
			double imp = t[e] - l;
			imp *= 1;
			imp *= rn[i] * 1;
			imp /= v[rv[i]] * 1;
			w.push_back( make_tuple(imp, rv[i], re[i], c) );
		}
	}
	sort(w.begin(), w.end());
	reverse(w.begin(), w.end());
	for(auto x:w){
		double imp;
		int vv, ee, cc;
		tie(imp, vv, ee, cc) = x;
		if( sz[ee] + v[vv] <= X && !u.count({ee,vv}) ){
			sz[ee] += v[vv];
			sol[ee].push_back(vv);
			u.insert({ee,vv});
		}
	}
	cout<<C<<"\n";
	for(int i=0; i<C; ++i){
//		if(sol[i].empty()) continue;
		cout<<i;
		for(auto x:sol[i]){
			cout<<" "<<x;
		}
		cout<<"\n";
	}
	return 0;
}
