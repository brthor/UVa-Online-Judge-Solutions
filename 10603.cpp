/* UVa Problem 10603
 *
 * Fill
 * http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1544	
 *
 * Author: Bryan Thornbury
*/

#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii > iii;
typedef pair<int, iii > iiii;
typedef vector<int> vi;
typedef vector<ii > vii;
typedef vector<iii > viii;
typedef vector<iiii > viiii;

#define TRvi(it, v) \
	for(vi::iterator it = v.begin(); it != v.end(); ++it)

#define TRvii(it, v) \
	for(vii::iterator it = v.begin(); it != v.end(); ++it)

#define TRviii(it, v) \
	for(viii::iterator it = v.begin(); it != v.end(); ++it)

#define TRviiii(it, v) \
	for(viiii::iterator it = v.begin(); it != v.end(); ++it)

#define REP(i,a,b) \
 	for(int i = int(a); i<=int(b); i++)

#define INF 2000000000

bool visited[205][205][205];

struct Node{
	int capacity[3];
	int state[3];

	int cost;

	Node() { }

	Node(int ac, int bc, int cc, int a, int b, int c, int delta){
		capacity[0] = ac;
		capacity[1] = bc;
		capacity[2] = cc;

		state[0] = a;
		state[1] = b;
		state[2] = c;

		cost = delta;
	}

	bool isEnd(int d){
		return state[0] == d || state[1] == d || state[2] == d;
	}

	int dprime(int d, int dp){
		REP(i,0,2){
			if(state[i] < d && state[i] > dp){
				dp = state[i];
			}
		}

		return dp;
	}

	bool operator<(const Node & x) const{
		return cost > x.cost;
	}

	vector<Node> nextStates(){
		int dj(0);
		int di(0);
		int nState[3];
		vector<Node> next;
		REP(i,0,2){
			REP(j,0,2){
				if(i==j) continue;
				if(state[j] == capacity[j]) continue;

				dj = capacity[j] - state[j];

				if(dj >= state[i]){
					di = state[i];
					dj = state[i];
				}else{
					di = dj;
				}

				REP(z,0,2){
					if(i == z){
						nState[z] = state[z] - di;
					}
					else if(j == z){
						nState[z] = state[z] + dj;
					}
					else{
						nState[z] = state[z];
					}
				}

				next.push_back(Node(capacity[0], capacity[1], capacity[2], nState[0], nState[1], nState[2], cost + di));
			}
		}
		return next;
	}
};


void distToD(const int ac, const int bc, const int cc, const int d){
	priority_queue<Node> q;

	REP(i,0,ac)
		REP(j,0,bc)
			REP(z,0,cc)
				visited[i][j][z] = false;

	q.push(Node(ac,bc,cc,0,0,cc,0));

	Node temp;
	int dp(0), tdp(0); Node delem;
	while(!q.empty()){
		temp = q.top(); q.pop();

		visited[temp.state[0]][temp.state[1]][temp.state[2]] = true;

		if(temp.isEnd(d)){
			break;
		}else{
			tdp = temp.dprime(d,dp);
			if(tdp != dp){
				dp = tdp;
				delem = temp;
			}
		}
		vector<Node> next = temp.nextStates();
		for(vector<Node>::iterator it = next.begin(); it != next.end(); ++it){
			if(!visited[(*it).state[0]][(*it).state[1]][(*it).state[2]]){
				q.push(*it);
			}
		}
	}

	//did we get d?
	if(temp.isEnd(d)){
		printf("%d %d\n", temp.cost, d);
	}else{
		printf("%d %d\n", (dp == 0 || dp == INF ? 0 : delem.cost), (dp == INF ? 0 : dp) );
	}
}

int main(){
	//freopen("input.txt","r", stdin);
	int T = 0, a = 0, b = 0, c = 0, d = 0;

	scanf("%d", &T);

	while(T--){
		scanf("%d %d %d %d", &a, &b, &c, &d);

		distToD(a,b,c,d);
	}
	
	return 0;
}