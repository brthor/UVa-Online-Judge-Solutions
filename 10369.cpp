/* UVa Problem 10369
 * 
 * Arctic Network
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1310
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <stdio.h>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii > iii;
typedef vector<int> vi;
typedef vector<ii > vii;
typedef vector<iii > viii;

#define TRvi(it, v) \
	for(vi::iterator it = v.begin(); it != v.end(); ++it)

#define TRvii(it, v) \
	for(vii::iterator it = v.begin(); it != v.end(); ++it)

#define TRviii(it, v) \
	for(viii::iterator it = v.begin(); it != v.end(); ++it)

#define REP(i,a,b) \
 	for(int i = int(a); i<=int(b); i++)

//Union-Find Disjoint set
vi pSet;
void initSet(int _size) { pSet.resize(_size); REP(i,0,_size-1) pSet[i] = i; }
int findSet(int i) {return pSet[i] == i ? i : (pSet[i] = findSet(pSet[i]));}
void unionSet(int i, int j){ pSet[findSet(i)] = findSet(j); }
bool isSameSet(int i, int j){ return findSet(i) == findSet(j); }

vi adj[500 + 5]; //dest point
void initAdj(int size){
	REP(i,0,size-1)
		adj[i].clear();
}

ii points[500 + 5];

double maxEdge(int size, int connectedComponents){
	initSet(size);

	int cConnected = 0;
	int max = 0;
	int cost(0.0);
	int dx(0), dy(0);

	priority_queue<iii, viii, greater<iii > > q;

	//put edges into heap
	REP(i,0,size-1){
		TRvi(it, adj[i]){

			dx = points[i].first - points[*it].first;
			dy = points[i].second - points[*it].second;
			cost = (dx*dx) + (dy*dy);

			q.push(iii(cost, ii(i, *it)));
		}
	}

	iii c;
	int source;
	int target;
	//perform kruskal's keep track of max added edge
	while(!q.empty() && cConnected < connectedComponents){
		c = q.top(); q.pop();
		source = c.second.first;
		target = c.second.second;

		if(!isSameSet(source, target)){
			if(findSet(source) == source && findSet(target) == target) cConnected ++;
			else if(findSet(source) != findSet(target) && findSet(target) != target && findSet(source) != source) cConnected --;
			unionSet(source,target);
			max = c.first;
		}
	}
	// REP(i,0,size-connectedComponents-1){
	// 	c = q.top(); q.pop();
	// 	source = c.second.first;
	// 	target = c.second.second;

	// 	if(!isSameSet(source, target)){
	// 		unionSet(source,target);
	// 		max = c.first;
	// 	}
	// }
	return sqrt(max);

}

int main(){
	freopen("input.txt", "r", stdin);

	int T(0), S(0), P(0), x(0), y(0);

	scanf("%d", &T);
	while(T--){
		scanf("%d %d", &S, &P);
		initAdj(P);
		REP(i,0,P-1){
			scanf("%d %d", &x, &y);
			points[i] = ii(x,y);
			for(int j = i-1; j >= 0; j--){
				adj[i].push_back(j);
			}
		}

		printf("%.2f\n", maxEdge(P, S));
	}
}