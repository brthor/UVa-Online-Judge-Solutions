/* UVa 11377
 *
 * Airport Setup
 * http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2372
 *
 * Author: Bryan Thornbury
*/

#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii > vii;

#define REP(i,a,b) \
	for(int i = int(a); i<=int(b); i++)

#define TRvii(it, v) \
	for(vii::iterator it = v.begin(); it!=v.end(); ++it)

bool airport[2005];
int dist[2005];

vii adj[2005];

void init(int size){
	REP(i,0,size-1){
		adj[i].clear();
		airport[i] = false;
	}
}

void initPath(int size){
	REP(i,0,size-1){
		dist[i] = -1;
	}
}

int minNum(int start, int target){
	if(start == target) return 0;
	priority_queue<ii, vii, greater<ii> > q;

	dist[start] = airport[start] ? 0 : 1;

	q.push(ii(dist[start], start));
	int c;
	while(!q.empty()){
		ii p = q.top(); q.pop();
		c = p.second;

		//printf("TR %d Cost: %d\n", c, p.first);

		if(c == target) break;

		//only process latest update
		if(p.first == dist[c]){
			TRvii(it, adj[c]){
				if(dist[it->second] > (dist[c] + it->first) || dist[it->second] == -1){
					dist[it->second] = (dist[c] + it->first);
					q.push(ii(dist[it->second], it->second));
				}
			}
		}
	}

	return c == target ? dist[c] : -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	int T = 0;
	scanf("%d", &T);

	REP(caseNum, 1, T){
		printf("Case #%d:\n", caseNum);

		int N(0), M(0), K(0), Q(0);
		scanf("%d %d %d", &N, &M, &K);
		init(N);

		int c = 0;

		REP(i,0,K-1){
			scanf("%d", &c);
			airport[c-1] = true;
		}

		int c1(0),  c2(0);
		REP(i,0,M-1){
			scanf("%d %d", &c1, &c2);

			adj[c1-1].push_back(ii(airport[c2-1] ? 0 : 1, c2-1));
			adj[c2-1].push_back(ii(airport[c1-1] ? 0 : 1, c1-1));
		}

		scanf("%d", &Q);

		REP(i, 0, Q-1){
			initPath(N);
			scanf("%d %d", &c1, &c2);

			printf("%d\n", minNum(c1-1, c2-1));
		}
		printf("\n");
	}
}