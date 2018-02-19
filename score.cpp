#include <bits/stdc++.h>
using namespace std;

int V,E,R,C,X;
int v[10004];
int t[1003];
vector<pair<int,int>> adj[1003];
int rv[1000006];
int re[1000006];
int rn[1000006];

vector<tuple<double, int, int, int>> w;
int sz[1003];
vector<int> sol[1003];
set<pair<int,int>> u;

int main(int argc, char** argv){
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
		}
	}
	for(int i=0; i<R; ++i){
		cin>>rv[i]>>re[i]>>rn[i];
	}

	ifstream sin = ifstream(argv[1]);
	int n;
	sin>>n;
	sin.ignore();
	set<int> sol[1003];
	for(int i=0; i<n; ++i){
		string s;
		getline(sin, s);
		stringstream ss(s);
		int c;
		ss>>c;
		int x;
		while(ss>>x)	sol[c].insert(x);
//		cout<<c<<" "<<sol[c].size()<<"\n";
		long long sum = 0;
		for(auto x:sol[c]){
			sum += v[x];
		}
		if( sum > X ){
			cerr<<"INVALID\n";
			cerr<<"sum = "<<sum<<" for c = "<<c<<"\n";
			return 1;
		}	
	}
	long long sc = 0, nn = 0;
	for(int i=0; i<R; ++i){
		int l = t[re[i]];
		for(auto p:adj[re[i]]){
			if(sol[p.first].count(rv[i]))
				l = min(l, p.second);
		}
		sc += rn[i] * (t[re[i]] - l);
		nn += rn[i];
	}
	double score = 1000.0 * sc / nn;
	cout<<score;

	return 0;
}
