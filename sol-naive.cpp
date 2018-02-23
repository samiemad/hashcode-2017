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

double weigh(int vid, int epLat, int cLat, int num){
	return 1.0 * num * (epLat - cLat) * (X-v[vid]) / X;
}

vector<vector<int>> solve(){
    vector<tuple<double, int, int, int>> w;
	for(int i=0; i<R; ++i){
		int e = re[i];
		for(auto p : adj[e]){
			int c = p.first;
			int l = p.second;
			double ww = weigh(rv[i], t[re[i]], p.second, rn[i]);
			w.push_back( make_tuple(ww, rv[i], re[i], c) );
		}
	}
	sort(w.begin(), w.end());
	reverse(w.begin(), w.end());

    int sz[1003] = {0};
    set<pair<int,int>> u;
    vector<vector<int>> sol(C);

	for(auto x:w){
		double imp;
		int vv, ee, cc;
		tie(imp, vv, ee, cc) = x;
		if( sz[cc] + v[vv] <= X && !u.count({ee,vv}) ){
			sz[cc] += v[vv];
			sol[cc].push_back(vv);
			u.insert({ee,vv});
		}
	}
	return sol;
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

	auto sol = solve();

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
