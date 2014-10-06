/* UVa 908
 *
 * Re-connecting Computer Sites
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=849
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;


typedef pair<int, int> ii;
typedef pair<int, ii > iii;

#define REP(i,a,b) \
 	for(int i = int(a); i<=int(b); i++)

#define TRvii(it, v) \
 	for(vector<ii >::iterator it = v.begin(); it != v.end(); ++it)

vector<int> p;
vector<ii > adj[1000000 + 5]; //cost, dest

void initSet(int _size){
	p.resize(_size);
	REP(i, 0,_size-1)
		p[i] = i;
}

int findSet(int i){
	return (p[i] != i) ? (p[i] = findSet(p[i])) : i;
}

void unionSet(int s, int t){
	p[findSet(s)] = findSet(t);
}

bool isSameSet(int i, int j){
	return findSet(i) == findSet(j);
}



int mst(int size){
	initSet(size);

	priority_queue<iii, vector<iii >, greater<iii> > q;

	REP(i,0,size-1)
		TRvii(it,adj[i])
			q.push(iii(it->first, ii(i, it->second)));

	iii c;
	ii coords;
	int total = 0;
	while(!q.empty()){
		c = q.top(); q.pop();
		coords = c.second;
		if(!isSameSet(coords.first, coords.second)){
			unionSet(coords.first, coords.second);
			total += c.first;
		}
	}

	return total;
}

int main() {
	//freopen("input.txt", "r", stdin);
	int N(0), K(0), M(0), s(0), t(0), c(0);
	int caseNum = 0;
	while(scanf("%d", &N) == 1){
		if(caseNum ++ > 0){
			printf("\n");
			REP(i,0,N-1)
				adj[i].clear();
		}

		int pTotal = 0;
		//N-1 times
		REP(i,0,N-2){
			scanf("%d %d %d", &s, &t, &c);
			pTotal += c;
		}

		scanf("%d", &K);

		REP(i,0,K-1){
			scanf("%d %d %d", &s, &t, &c);
			s--;t--;
			adj[s].push_back(ii(c,t));
			adj[t].push_back(ii(c,s));
		}

		scanf("%d", &M);

		REP(i,0,M-1){
			scanf("%d %d %d", &s, &t, &c);
			s--;t--;
			adj[s].push_back(ii(c,t));
			adj[t].push_back(ii(c,s));
		}

		printf("%d\n", pTotal);
		printf("%d\n", mst(N));
		//printf("\n");
	}
	return 0;
}

