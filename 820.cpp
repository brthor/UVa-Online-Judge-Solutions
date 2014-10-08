/* UVa Problem 820
 *
 * Internet Bandwidth
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=761
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <queue>
#include <stdio.h>
#include <set>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii > iii;
typedef vector<int> vi;
typedef vector<ii > vii;
typedef vector<iii > viii;

#define REP(i,a,b) \
	for(int i = a; i <= int(b); i++)

#define TRvii(it, v) \
	for(vii::iterator it = v.begin(); it != v.end(); ++it)

#define TRvi(it, v) \
	for(vi::iterator it = v.begin(); it != v.end(); ++it)

#define INF 2000000000

int residual[200 + 5][200 + 5];
vi adj[200 + 5]; //capacity, dest
int p[200 + 5];

//Returns the min edge, and properly adjusts the residual path
int augmentPath(int source, int current, int minedge){\
	if(current == source){
		return minedge;
	}else{
		int mine = augmentPath(source, p[current], min(minedge, residual[p[current]][current]));
		residual[p[current]][current] -= mine;
		residual[current][p[current]] += mine;
		return mine;
	}
}

int maxFlow(int graphSize, int source, int sink){
	int totalFlow = 0;

	while(1){
		int f = 0;

		//find an augmented path
		queue<ii> bfs;
		set<int> visited;

		bfs.push(ii(source,source));
		p[source] = source;
		visited.insert(source);

		ii n; //parent node, next node
		int c(0); //current node

		while(!bfs.empty()){
			n = bfs.front();bfs.pop();
			c = n.second;

			p[c] = n.first;

			if(c == sink) break;
			// For each neighbor
			TRvi(it, adj[c]){
				//Make sure we haven't visited it before
				// and that it has capacity remaining in the residual network
				if(visited.find(*it) == visited.end() && residual[c][*it] > 0){
					visited.insert(*it);
					bfs.push(ii(c,*it));
				}
			}
		}

		//If we couldn't find a path break
		if(c != sink) break;
		f = augmentPath(source, sink, INF);
		totalFlow += f;
		if (f == 0) break;
	}

	return totalFlow;
}



void init(int size){
	REP(i,0,size-1){
		adj[i].clear();

		REP(j,0,size-1){
			residual[i][j] = 0;
		}
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	int n(0), s(0), t(0), c(0), n1(0), n2(0), b(0);
	int T = 0;
	while(scanf("%d", &n) == 1 && n != 0){
		scanf("%d %d %d", &s, &t, &c);
		s--; t--; // 0-index

		init(n);

		REP(i,0,c-1){
			scanf("%d %d %d", &n1, &n2, &b);
			n1--;n2--;
			adj[n1].push_back(n2);
			adj[n2].push_back(n1);

			residual[n1][n2] += b;
			residual[n2][n1] += b;
		}
		printf("Network %d\nThe bandwidth is %d.\n\n", ++T, maxFlow(n,s,t));
	}
}


