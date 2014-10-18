/* UVa Problem 10842
 *
 * Traffic Flow
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1783
 *
 * Author: Bryan Thornbury
*/

#include <queue>
#include <vector>
#include <stdio.h>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii > iii;
typedef vector<ii > vii;
typedef vector<iii > viii;

#define REP(i,a,b) for(int i = int(a); i<=int(b); ++i)
#define TRvii(it, v) for(vii::iterator it = v.begin(); it != v.end(); ++it)
#define TRviii(it, v) for(viii::iterator it = v.begin(); it != v.end(); ++it)
#define MAX 100

int pSet[MAX + 5];

void initSet(int size){ REP(i,0,size-1) pSet[i] = i;}
int findSet(int i) { return pSet[i] == i ? i : (pSet[i] = findSet(pSet[i])); }
void unionSet(int i , int j) { pSet[findSet(i)] = findSet(j); }
bool isSameSet(int i , int j) { return findSet(i) == findSet(j); }

int minMaxMST(viii &edges, int size){
	//priority_queue<iii, viii, less<iii >() q;
	initSet(size);
	sort(edges.begin(), edges.end(), greater<iii >());

	int min = 0;
	ii c;
	TRviii(it, edges){
		c = it->second;
		if(!isSameSet(c.first, c.second)){
			unionSet(c.first, c.second);
			min = it->first;
		}
	}
	return min;	
}

int main(){
	//freopen("input.txt", "r", stdin);
	int T = 0, N = 0, M = 0, a = 0, b = 0, c = 0;
	scanf("%d", &T);

	REP(caseNum, 1, T){
		scanf("%d %d", &N, &M);

		viii edges;

		REP(i,0,M-1){
			scanf("%d %d %d", &a, &b, &c);
			edges.push_back(iii(c, ii(a,b)));
		}

		printf("Case #%d: %d\n", caseNum, minMaxMST(edges, N));
	}

	//Case #2: 3

	return 0;
}