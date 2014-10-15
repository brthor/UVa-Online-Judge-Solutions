/* UVa Problem 10147
 *
 * Highways
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1088
 *
 * Author: Bryan Thornbury
*/

#include <queue>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii > iii;
typedef vector<ii > vii;
typedef vector<iii > viii;

#define REP(i,a,b) for(int i = int(a); i<=int(b); ++i)
#define TRvii(it,v) for(vii::iterator it = v.begin(); it != v.end(); ++it)
#define TRviii(it,v) for(viii::iterator it = v.begin(); it != v.end(); ++it)

vii adj[ 750 + 5 ];
ii coords [750 + 5];

int p[750 + 5];
void initSet(int _size) { REP(i,0,_size-1) p[i] = i; }
int findSet(int i){ return p[i] == i ? i : (p[i] = findSet(p[i])); }
void unionSet(int i, int j){ p[findSet(i)] = findSet(j); }
bool isSameSet(int i , int j) { return findSet(i) == findSet(j); }

int dist2(int i, int j){
	return 
		((coords[i].first - coords[j].first)*(coords[i].first - coords[j].first))
		+
		((coords[i].second - coords[j].second)*(coords[i].second - coords[j].second));
}

int newHighways(int size){
	priority_queue<iii, viii, greater<iii > > q;
	REP(i,0,size-1){
		adj[i].clear();
		REP(j,i+1,size-1){
			if(!isSameSet(i,j)){
				q.push( iii(dist2(i,j), ii(i,j)) );
			}
		}
	}

	iii c;
	ii t;
	int count = 0;
	while(!q.empty()){
		c = q.top(); q.pop();
		t = c.second;
		if(!isSameSet(t.first, t.second)){
			unionSet(t.first, t.second);
			printf("%d %d\n", t.first + 1, t.second + 1);
			count ++;
		}
	}
	return count;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output_test.txt", "w", stdout);

	int T = 0, M= 0, N = 0, x = 0, y = 0, t1 = 0, t2 = 0;
	scanf("%d", &T);
	REP(caseNum,0,T-1){
		if(caseNum > 0) printf("\n");

		scanf("%d", &N);
		initSet(N);

		REP(n,0,N-1){
			scanf("%d %d", &x, &y);
			coords[n] = ii(x,y);
		}

		scanf("%d", &M);
		REP(m, 0, M-1){
			scanf("%d %d", &t1, &t2);
			t1--;t2--;
			unionSet(t1,t2);
		}
		if(newHighways(N) == 0){
			printf("No new highways need\n");
		}
	}
	return 0;
}

