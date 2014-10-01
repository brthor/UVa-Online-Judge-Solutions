/* UVa Problem 10986
 * 
 * Sending Email
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1927
 * 
 * Author: Bryan Thornbury
*/

#include <queue>
#include <vector>
#include <stdio.h>

using namespace std;

typedef pair<int, int> ii;

#define REP(i,a,b) \
    for(int i = int(a); i<=int(b);i++)

#define TRvii(it, v) \
    for(vector<ii>::iterator it = v.begin(); it != v.end(); ++it)




int dist[20005];
vector<ii> adj[20005]; // cost, node

void initialize(int size){
	REP(i,0,size-1){ dist[i] = -1; adj[i].clear(); }
}

int shortest(int start, int end){
	dist[start] = 0;

	priority_queue<ii, vector<ii>, greater<ii> > q;

	q.push(ii(dist[start], start));
	int c = 0;
	ii p;
	while(!q.empty()){
		p = q.top(); q.pop();
		c = p.second;
		if(c == end) break;
		TRvii(it, adj[c]){
			if(dist[it->second] > (dist[c] + it->first) || dist[it->second] == -1){
				dist[it->second] = dist[c] + it->first;
				q.push(ii(dist[it->second], it->second));
			}
		}
	}

	if( c == end ) return dist[c];
	return -1;
}

int main() {
	//freopen("input.txt", "r", stdin);
	int test = 0;
	scanf("%d", &test);

	REP(caseNum, 1, test){
		int nodeCount(0), edgeCount(0), init(0), target(0);
		scanf("%d %d %d %d", &nodeCount, &edgeCount, &init, &target);

		initialize(nodeCount);

		int n1(0), n2(0), w(0);
		REP(i, 0, edgeCount -1){
			scanf("%d %d %d", &n1, &n2, &w);
			adj[n1].push_back(ii(w,n2));
			adj[n2].push_back(ii(w,n1));
		}

		int r = shortest(init, target);

		printf("Case #%d: ", caseNum);
		if(r == -1){
			printf("unreachable\n");
		}else{
			printf("%d\n", r);
		}
	}
	return 0;
}

