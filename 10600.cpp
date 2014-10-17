/* UVa Problem 10600
 *
 * ACM Contest and Blackout
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1541
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <functional>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii > iii;
typedef vector<int> vi;
typedef vector<ii > vii;
typedef vector<iii > viii;

#define REP(i,a,b) for(int i = int(a); i<=int(b); ++i)
#define TRvi(it, v) for(vi::iterator it = v.begin(); it != v.end(); ++it)
#define TRvii(it, v) for(vii::iterator it = v.begin(); it != v.end(); ++it)
#define TRviii(it, v) for(viii::iterator it = v.begin(); it != v.end(); ++it)
#define INF 2000000000

int pSet[100 + 5];
void initSet(int _size) { REP(i,0,_size-1) pSet[i] = i; }
int findSet(int i) { return pSet[i] == i ? i : (pSet[i] = findSet(pSet[i])); }
void unionSet(int i, int j) { pSet[findSet(i)] = findSet(j); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }



//time copy, ref, and const ref here
void spanningTrees(int size, viii &edges){
	initSet(size);
	sort(edges.begin(), edges.end(), less<iii >());

	int best = 0;
	int second = INF;

	vi mst;
	ii schools;
	int index = 0;

	TRviii(it, edges){
		schools = it->second;
		if(!isSameSet(schools.first, schools.second)){
			best += it->first;
			unionSet(schools.first, schools.second);
			mst.push_back(index);
		}
		index++;
	}

	int temp = 0;
	int cost = 0;
	int d = 0;
	TRvi(vit, mst){

		cost=0;
		d = size;

		temp = edges[*vit].first;
		edges[*vit].first = INF;

		initSet(size);

		TRviii(it, edges){
			schools = it->second;
			if(!isSameSet(schools.first, schools.second) && it->first != INF){
				d--;
				cost += it->first;
				unionSet(schools.first, schools.second);
			}
		}

		second = (cost < second) && d == 1 ? cost : second;
		edges[*vit].first = temp;
	}

	printf("%d %d\n", best, second);
}

int main() {
	//freopen("input.txt", "r", stdin);

	int T = 0, M = 0, N = 0, a = 0, b = 0, c = 0;
	scanf("%d", &T);

	while(T--){
		scanf("%d %d", &N, &M);

		viii edges;

		while(M--){
			scanf("%d %d %d", &a, &b, &c);
			a--;b--;

			edges.push_back(iii(c, ii(a,b)));
		}

		spanningTrees(N, edges);
	}

	return 0;
}