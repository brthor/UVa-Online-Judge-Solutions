/* UVa Problem 929
 *
 * Number Maze
 * http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=870
 * 
 * Author: Bryan Thornbury
*/

#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

#define REP(i,a,b) \
	for(int i = int(a); i<=int(b); i++)

typedef pair<int, int> ii;
typedef pair<int, ii > iii;

int grid[999 + 5][999 + 5];

int dist[999 + 5][999 + 5];

class iiiCompare {
public:
	bool operator() (iii a, iii b) {
		return a.first > b.first;
	}
};

void init(int N, int M){
	REP(r, 0, N-1){
		REP(c, 0, M-1){
			dist[r][c] = -1;
		}
	}
}

int shortest(int tN, int tM){
	priority_queue<iii, vector<iii >, iiiCompare > q;

	dist[0][0] = grid[0][0];
	q.push(iii(dist[0][0], ii(0,0)));

	iii elem;
	ii coords;

	while(!q.empty()){
		elem = q.top(); q.pop();
		coords = elem.second;
		//printf("Cost: %d  Coords: %d %d\n", elem.first, coords.first, coords.second);

		if(coords.first == tN && coords.second == tM) break;

		//only process latest enqueuing (avoids auxiliary set)
		if(dist[coords.first][coords.second] == elem.first){
			//up down
			REP(dr,-1,1){
				if(dr == 0) continue;
				if((coords.first + dr) < 0 || (coords.first + dr) > tN) continue;

				//printf("y no\n");
				//triangle inequality
				if((dist[coords.first + dr][coords.second] > (dist[coords.first][coords.second] + grid[coords.first + dr][coords.second])) 
					|| dist[coords.first + dr][coords.second] == -1){
					dist[coords.first + dr][coords.second] = dist[coords.first][coords.second] + grid[coords.first + dr][coords.second];
					q.push(iii(dist[coords.first + dr][coords.second], ii(coords.first + dr, coords.second)));
					//printf("pushing\n");
				}
			}

			//left-right
			REP(dc,-1,1){
				if(dc == 0) continue;
				if((coords.second + dc) < 0 || (coords.second + dc) > tM) continue;
				//triangle inequality
				if((dist[coords.first][coords.second + dc] > (dist[coords.first][coords.second] + grid[coords.first][coords.second + dc])) 
					|| dist[coords.first][coords.second + dc] == -1){
					dist[coords.first][coords.second + dc] = dist[coords.first][coords.second] + grid[coords.first][coords.second + dc];
					q.push(iii(dist[coords.first][coords.second + dc], ii(coords.first, coords.second + dc)));
				}
			}
		}
	}

	return (coords.first == tN && coords.second == tM) ? dist[tN][tM] : -1;
}

int main() {
	//freopen("input.txt", "r", stdin);
	int T(0), N (0), M(0), v(0);

	scanf("%d", &T);

	while(T--){
		scanf("%d %d", &N, &M);
		init(N, M);

		REP(r, 0, N-1){
			REP(c, 0, M-1){
				scanf("%d", &v);
				grid[r][c] = v;
			}
		}
		printf("%d\n", shortest(N-1, M-1));
	}
	return 0;
}