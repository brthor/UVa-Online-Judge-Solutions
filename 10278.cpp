/* UVa Problem 278
 *
 * Fire Station
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1219
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <queue>
#include <stdio.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii > vii;

#define INF 2000000000
#define REP(i,a,b) for(int i = int(a); i<=int(b); ++i)
#define TRvii(it, v) for(vii::iterator it = v.begin(); it != v.end(); ++it)
#define TRvi(it, v) for(vi::iterator it = v.begin(); it != v.end(); ++it)


bool station[500+5];
vii adj[500 + 5];
int dist[500 + 5];

void initPath(int _size){
	REP(i,0,_size-1){
		dist[i] = INF;
	}
}

void init(int _size){
	REP(i,0,_size-1){
		station[i] = false;
		adj[i].clear();
	}
}

int augmentedSourceMaxDist(vi &sources, int augSource){
	priority_queue<ii, vii, greater<ii > > q;

	q.push(ii(0,augSource));
	dist[augSource] = 0;

	TRvi(it, sources){
		q.push(ii(0,*it));
		dist[*it] = 0;
	}

	int max = 0;

	while(!q.empty()){
		ii c = q.top(); q.pop();

		if(dist[c.second] > max)
			max = dist[c.second];

		//only process latest (least)
		if(dist[c.second] == c.first){
			TRvii(it, adj[c.second]){
				//relax each edge if necessary
				if(dist[it->second] > (dist[c.second] + it->first)){
					dist[it->second] = (dist[c.second] + it->first);
					q.push(ii(dist[it->second], it->second));
				}
			}
		}
	}
	return max;
}

int main() {
	//freopen("input.txt", "r", stdin);
	int caseNum = 0;
	int T = 0, f = 0, ic = 0, fi = 0, s = 0, d = 0, w = 0;
	char line[256];
	scanf("%d", &T);
	while(T--){
		//blank line
		if(caseNum++ > 0) printf("\n");
		scanf("%d %d", &f, &ic);
		init(ic);

		vi sources;
		while(f--){
			scanf("%d", &fi);
			fi--;
			sources.push_back(fi);
			station[fi] = true;
		}
		gets(line);
		int lcount = 0;
		while(true){
			gets(line);
			if(sscanf(line, "%d %d %d", &s, &d, &w) < 3) break;
			s--;d--;
			adj[s].push_back(ii(w,d));
			adj[d].push_back(ii(w,s));
			lcount ++;
			if(feof(stdin)) break;
		}

		int min = INF;
		int minIndex = -1;

		//Test all possible sources because two fire stations can be on the same intersection
		REP(i,0,ic-1){
			initPath(ic);
			int minMax = augmentedSourceMaxDist(sources, i);
			if(minMax < min){
				min = minMax;
				minIndex = i;
			}
		}
		printf("%d\n", minIndex + 1);

	}

	return 0;
}