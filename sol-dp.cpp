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

double weigh(int vid, int epLat, int cLat, int num){
	return 1.0 * num * (epLat - cLat) * (X-v[vid]) / X / 1000;
}

vector<int> solve(map<int,double>& val){
    double dp[X]={0};
    int par[X];
    memset(par, -1, sizeof par);
    for(auto p:val){
        cerr<<"p=("<<p.first<<","<<p.second<<")\n";
        int vid = p.first;
        double weight = p.second;
        for(int x=X-1; x>=0; --x){
            int nx = x + v[vid];
            if( nx < X && dp[nx] < dp[x] + weight ){
                cerr<<"upd "<<x<<"->"<<nx<<":"<<vid<<"\n";
                dp[nx] = dp[x] + weight;
                par[nx] = vid;
            }
        }
    }
    vector<int> sol;
    int p = X-1;
    int n=15;
    for(int i=0; i<X; ++i) cerr<<dp[i]<<","; cerr<<"\n";
    for(int i=0; i<X; ++i) cerr<<par[i]<<","; cerr<<"\n";
    cerr<<"sol =";
    while(par[p]!=-1 && --n){
        sol.push_back(par[p]);
        cerr<<" "<<par[p];
        p -= v[par[p]];
    }
    cerr<<".\n";
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

    map<int,double> val[1003];
	for(int i=0; i<R; ++i){
		for(auto c:adj[re[i]]){
			double w = weigh(rv[i], t[re[i]], c.second, rn[i]);
            val[c.first][rv[i]] = max(val[c.first][rv[i]], w);
		}
	}

	for(int i=0; i<1; ++i){
	    sol[i] = solve(val[i]);
	}

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
		cout<<i;
		for(auto x:sol[i]){
			cout<<" "<<x;
		}
		cout<<"\n";
	}
	return 0;
}
