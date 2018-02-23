#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
  int N;
  VVL cap, flow, cost;
  VI found;
  VL dist, pi, width;
  VPII dad;

  MinCostMaxFlow(int N) :
    N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)),
    found(N), dist(N), pi(N), width(N), dad(N) {}

  void AddEdge(int from, int to, L cap, L cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
  }

  void Relax(int s, int k, L cap, L cost, int dir) {
    L val = dist[s] + pi[s] - pi[k] + cost;
    if (cap && val < dist[k]) {
      dist[k] = val;
      dad[k] = make_pair(s, dir);
      width[k] = min(cap, width[s]);
    }
  }

  L Dijkstra(int s, int t) {
    fill(found.begin(), found.end(), false);
    fill(dist.begin(), dist.end(), INF);
    fill(width.begin(), width.end(), 0);
    dist[s] = 0;
    width[s] = INF;

    while (s != -1) {
      int best = -1;
      found[s] = true;
      for (int k = 0; k < N; k++) {
        if (found[k]) continue;
        Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
        Relax(s, k, flow[k][s], -cost[k][s], -1);
        if (best == -1 || dist[k] < dist[best]) best = k;
      }
      s = best;
    }

    for (int k = 0; k < N; k++)
      pi[k] = min(pi[k] + dist[k], INF);
    return width[t];
  }

  pair<L, L> GetMaxFlow(int s, int t) {
    L totflow = 0, totcost = 0;
    while (L amt = Dijkstra(s, t)) {
      totflow += amt;
      for (int x = t; x != s; x = dad[x].first) {
        if (dad[x].second == 1) {
          flow[dad[x].first][x] += amt;
          totcost += amt * cost[dad[x].first][x];
        } else {
          flow[x][dad[x].first] -= amt;
          totcost -= amt * cost[x][dad[x].first];
        }
      }
    }
    return make_pair(totflow, totcost);
  }
};

int V,E,R,C,X;
int v[10004];
int t[1003];
vector<pair<int,int>> adj[1003];
vector<pair<int,int>> rdj[1003];
int rv[1000006];
int re[1000006];
int rn[1000006];

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
	MinCostMaxFlow mcmf(R+C+2);
	for(int i=0; i<R; ++i){
		cin>>rv[i]>>re[i]>>rn[i];
		mcmf.AddEdge(0, i+1, v[rv[i]], 0);
		mcmf.AddEdge(i+1, R+C+1, v[rv[i]], t[re[i]]*rn[i]);
	}
	for(int i=0; i<R; ++i){
		for(auto c:adj[re[i]]){
		    if(v[rv[i]] > X)    continue;
            mcmf.AddEdge(i+1, c.first+R+1, v[rv[i]], c.second*rn[i]);
//            mcmf.AddEdge(c.first+R+1, i+1, v[rv[i]], c.second*rn[i]);
		}
	}
	for(int i=0; i<C; ++i){
	    mcmf.AddEdge(i+R+1, C+R+1, X, 0);
	}
	auto res = mcmf.GetMaxFlow(0, C+R+1);
	cerr<<"\nres=("<<res.first<<","<<res.second<<")\n";

	cout<<C<<"\n";
	for(int i=0; i<C; ++i){
		cout<<i;
		int t=0;
		for(int j=0; j<R; ++j){
		    int f = mcmf.flow[j+1][i+R+1] - mcmf.flow[i+R+1][j+1];
	        if(f==v[rv[j]]){
    			cout<<" "<<rv[j];
    			t += v[rv[j]];
			}
		}
		cout<<"\n";
	    cerr<<i<<": "<<t<<"/"<<mcmf.flow[i+R+1][C+R+1]<<"\n";
	}
	return 0;
}
