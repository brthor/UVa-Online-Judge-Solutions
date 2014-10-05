/* UVa 558
 *
 * Wormholes
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=499
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii > vii;

#define REP(i,a,b) \
	for(int i = int(a); i<=int(b); i++)

#define TRVii(it, v)\
	for(vii::iterator it = v.begin(); it != v.end(); ++it)

#define INF 2000000000


int dist[1000 + 5];
vector<ii > adj[1000 + 5]; // cost, destNode

void init(int size){
	memset(dist, INF, sizeof(dist));

	REP(i,0,size-1)
		adj[i].clear();
}

bool negCycleExists(int N){

	dist[0] = 0;

	//Bellman Ford
	REP(v,0,N-1){ // Relax N-1 times
		REP(u, 0, N-1){ // Each edge
			TRVii(it, adj[u]){
				dist[it->second] = min(dist[it->second], dist[u] + it->first);
			}
		}
	}

	//Check for a negative cycle
	REP(v,0,N-1){
		TRVii(it, adj[v]){
			if(dist[it->second] > (dist[v] + it->first)) return true;
		}
	}
	return false;
}

int main(){
	//freopen("input.txt", "r", stdin);
	int T(0), N(0), M(0), x(0), y(0), t(0);

	scanf("%d", &T);

	while(T--){
		scanf("%d %d", &N, &M);

		init(N);

		while(M--){
			scanf("%d %d %d", &x, &y, &t);
			adj[x].push_back(ii(t, y));
		}
		printf(negCycleExists(N) ? "possible\n" : "not possible\n");
	}

	return 0;
}